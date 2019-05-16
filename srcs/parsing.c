/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:01:27 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/16 14:39:32 by thflahau         ###   ########.fr       */
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

	if (LIKELY((index = ft_word_count(buffer)) > 0))
		return (index - 1);
	return (0);
}

/*
**	Analize la chaine 'buffer' retournée par get_next_line afin de savoir si
**	on a affaire à une définition de salle, de tube ou du nombre de fourmis
**	avant de dispatcher à la fonction correspondante.
*/

static uint8_t			ft_parse_buffer(t_map *map, char const *buffer)
{
	static uint8_t		index;
	uint8_t				(*funptr[3])(t_map *, char const *);

	funptr[0] = &ft_parse_ants;
	funptr[1] = &ft_parse_edges;
	funptr[2] = &ft_parse_vertices;
	if (UNLIKELY(!buffer || !buffer[0]))
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
**	Lecture de l'entrée std. Si le file descriptor 0 correspond à une
**	redirection (isatty == 0) -> vérifie que le fichier redirigé soit bien
**	de type régulier (S_ISREG) ou pipe (S_ISFIFO).
*/

uint8_t					ft_read_std_input(t_map *map)
{
	char				*buffer;
	struct stat			informations;

	if (UNLIKELY(fstat(STDIN_FILENO, &informations) < 0))
		return (EXIT_FAILURE);
	else if (!S_ISREG(informations.st_mode) && !S_ISFIFO(informations.st_mode))
		if (isatty(STDIN_FILENO) == 0)
			return (ft_printf("lem-in: %s\n", INVALIDFMT));
	while (get_next_line_stdin(&buffer) > 0)
	{
		if (ft_parse_buffer(map, buffer) == EXIT_FAILURE)
			return (ft_variadic_memory_freeing(1, (void *)buffer));
		free((void *)buffer);
	}
	free((void *)buffer);
	if (UNLIKELY(map->vertices < 2))
		return (ft_printf("lem-in: %s\n", TOOSMALLFARM));
	map->start_edges = MIN(map->start_edges, map->end_edges);
	return (EXIT_SUCCESS);
}
