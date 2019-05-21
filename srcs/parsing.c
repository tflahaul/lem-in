/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:01:27 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/21 13:19:59 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_bug.h>
#include <lem_in_compiler.h>
#include <sys/stat.h>
#include <unistd.h>

static void				ft_parse_command_lines(t_map *map, char const *buffer)
{
	if (ft_strcmp(buffer, "##start") == 0)
		map->entry_point = 1;
	else if (ft_strcmp(buffer, "##end") == 0)
		map->entry_point = 2;
	else if (ft_strncmp(buffer, "##color=", 8) == 0)
		if (ft_isdigit(buffer[8]) && buffer[8] - '0' < 8 && buffer[9] == 0)
			map->visual |= ((buffer[8] - '0') << 0x10u);
}

static uint8_t			ft_parse_ants(t_map *map, char const *buffer)
{
	register uint16_t	index;

	index = 0;
	while (buffer[index])
	{
		if (UNLIKELY(map->population >> 0x10u))
			return (ft_puterror(buffer, OUTDOMAIN));
		if (UNLIKELY(ft_isdigit(buffer[index]) == 0))
			return (ft_puterror(buffer, BADINPUT));
		else
			map->population = map->population * 10 + buffer[index] - '0';
		index++;
	}
	if (UNLIKELY(map->population == 0))
		return (ft_puterror(buffer, OUTDOMAIN));
	ft_putstr_endl(buffer);
	return (EXIT_SUCCESS);
}

static inline uint8_t	ft_get_funptr_index(char const *buffer)
{
	uint32_t			index;

	if (LIKELY((index = ft_word_count(buffer)) > 0 && index < 4))
		return (index - 1);
	return (0);
}

/*
** 	Analyzes returned 'buffer' string by get_next_line to find
**	out if we're dealing with a room definition, a tube one
**	or the total amount of ants. It then proceeds to the
** 	corresponding function.
*/

static uint8_t			ft_parse_buffer(t_map *map, char const *buffer)
{
	static uint8_t		index;
	uint8_t				(*funptr[3])(t_map *, char const *);

	funptr[0] = &ft_parse_ants;
	funptr[1] = &ft_parse_edges;
	funptr[2] = &ft_parse_vertices;
	if (UNLIKELY(buffer == NULL || !buffer[0]))
		return (ft_puterror(NULL, EMPTYLINE));
	if (buffer[0] == '#')
	{
		if (buffer[1] == '#')
			ft_parse_command_lines(map, buffer);
		ft_putstr_endl(buffer);
	}
	else if (UNLIKELY(index == 0))
		return ((funptr[index++])(map, buffer));
	else if ((index = ft_get_funptr_index(buffer)) != 0)
	{
		if ((funptr[index])(map, buffer) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	else
		return (ft_puterror(buffer, UNKCOMM));
	return (EXIT_SUCCESS);
}

/*
** 	Reads Standard Input. If file descriptor 0 is redirection (isatty == 0),
**	checks if redirection is towards a regular file (S_ISREG)
**	or of the pipe kind (S_ISFIFO).
*/

uint8_t					ft_read_std_input(t_map *map)
{
	char				*buffer;
	static char			*string;
	struct stat			informations;

	if (UNLIKELY(fstat(STDIN_FILENO, &informations) < 0))
		return (EXIT_FAILURE);
	else if (!S_ISREG(informations.st_mode) && !S_ISFIFO(informations.st_mode))
		if (isatty(STDIN_FILENO) == 0)
			return (ft_printf(C_RED"lem-in: %s"C_NONE, INVALIDFMT));
	while (get_next_line_stdin(&string, &buffer) > 0)
	{
		if (ft_parse_buffer(map, buffer) == EXIT_FAILURE)
			return (ft_variadic_freeing(2, (void *)buffer, (void *)string));
		free((void *)buffer);
	}
	ft_variadic_freeing(2, (void *)buffer, (void *)string);
	if (UNLIKELY(map->vertices < 2))
		return (ft_printf(C_RED"lem-in: %s"C_NONE, TOOSMALLFARM));
	map->start_edges = (uint32_t)ft_min(map->start_edges, map->end_edges);
	return (EXIT_SUCCESS);
}
