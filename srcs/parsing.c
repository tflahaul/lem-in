/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:01:27 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/28 15:03:51 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_bug.h>
#include <lem_in_compiler.h>
#include <sys/stat.h>
#include <unistd.h>

static uint8_t			ft_parse_ants(t_map *map, char const *buffer)
{
	register uint16_t	index;

	index = 0;
	while (buffer[index])
	{
		if (UNLIKELY(map->population >> 16))
			return (ft_puterror(buffer, OUTDOMAIN));
		if (UNLIKELY(ft_isdigit(buffer[index]) == 0))
			return (ft_puterror(buffer, BADINPUT));
		else
			map->population = map->population * 10 + buffer[index] - 48;
		index++;
	}
	if (UNLIKELY(map->population == 0))
		return (ft_puterror(buffer, OUTDOMAIN));
	else
		ft_putstr_endl(buffer);
	return (EXIT_SUCCESS);
}

static uint8_t			ft_tokenize_buffer(char const *buffer)
{
	uint32_t			index;

	if ((index = ft_word_count(buffer)) == 3)
		return (2);
	else if (LIKELY(index == 2))
		return (1);
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
		if (!ft_strcmp(buffer, "##start") || !ft_strcmp(buffer, "##end"))
			map->entry_point = buffer[2] == 's' ? 1 : 2;
		ft_putstr_endl(buffer);
	}
	else if (UNLIKELY(index == 0))
		return ((funptr[index++])(map, buffer));
	else if ((index = ft_tokenize_buffer(buffer)) != 0)
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

	if (isatty(STDIN_FILENO) == 0)
	{
		fstat(STDIN_FILENO, &informations);
		if (!S_ISREG(informations.st_mode) && !S_ISFIFO(informations.st_mode))
			return (printf("lem-in: %s\n", INVALIDFMT));
	}
	while (get_next_line_stdin(&buffer) > 0)
	{
		if (ft_parse_buffer(map, buffer) == EXIT_FAILURE)
			return (ft_variadic_memory_freeing(1, (void *)buffer));
		free((void *)buffer);
	}
	free((void *)buffer);
	if (UNLIKELY(map->vertices < 2))
		return (printf("lem-in: %s\n", TOOSMALLFARM));
	map->start_edges = MIN(map->start_edges, map->end_edges);
	return (EXIT_SUCCESS);
}
