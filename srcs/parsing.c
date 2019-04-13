/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:01:27 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/13 18:15:54 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../include/lem_in_bug.h"
#include "../include/lem_in_compiler.h"

uint8_t					ft_parse_edges(__UNUSED t_map *map, char const *buffer)
{
	ft_putstr_endl(buffer);
	return (EXIT_SUCCESS);
}

uint8_t					ft_parse_ants(t_map *map, char const *buffer)
{
	uint16_t			index;

	index = 0;
	while (buffer[index])
	{
		if (ft_isdigit(buffer[index]) == 0 && ft_isblank(buffer[index]) == 0)
			return (ft_puterror(buffer, NONNUM));
		index++;
	}
	map->population = atoi(buffer);
	if (UNLIKELY(map->population > UINT16_MAX || map->population <= 0))
		return (ft_puterror(buffer, OUTDOMAIN));
	else
		ft_putstr_endl(buffer);
	return (EXIT_SUCCESS);
}

void					ft_handle_start_and_end(char const *buffer)
{
	char				*line;

	get_next_line_stdin(&line);
	ft_putstr_endl(buffer);
	free((void *)line);
}




static uint8_t			ft_tokenize_buffer(char const *buffer)
{
	uint32_t			index;

	if ((index = ft_word_count(buffer)) == 3)
		return (2);
	else if (index == 2)
		return (1);
	return (0);
}

/*
**	Analize la chaine 'buffer' retournée par get_next_line afin de savoir si
**	on a affaire à une définition de salle, de tube ou du nombre de fourmis
**	avant de dispatcher à la fonction correspondante.
*/
static uint8_t			ft_parse_buffer(t_map *graph, char const *buffer)
{
	static uint8_t		index;
	uint8_t				(*funptr[3])(t_map *, char const *);

	funptr[0] = &ft_parse_ants;
	funptr[1] = &ft_parse_edges;
	funptr[2] = &ft_parse_verticles;
	if (!buffer || !buffer[0])
		return (ft_puterror(NULL, EMPTYLINE));
	if (buffer[0] == '#')
	{
		if (strcmp(buffer, "##start") == 0 || strcmp(buffer, "##end") == 0)
			ft_handle_start_and_end(buffer);
		else
			ft_putstr_endl(buffer);
	}
	else if (index == 0)
		return ((funptr[index++])(graph, buffer));
	else if ((index = ft_tokenize_buffer(buffer)) != 0)
	{
		if ((funptr[index])(graph, buffer) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
		return (ft_puterror(buffer, UNKCOMM));
	return (EXIT_SUCCESS);
}

/*
**	Fonction de récupération de l'entrée std.
*/
uint8_t					ft_read_std_input(t_map *graph)
{
	char				*buffer;

	buffer = NULL;
	while (get_next_line_stdin(&buffer) > 0)
	{
		if (ft_parse_buffer(graph, buffer) == EXIT_FAILURE)
			return (ft_variadic_memory_freeing(1, (void *)buffer));
		free((void *)buffer);
	}
	free((void *)buffer);
	return (EXIT_SUCCESS);
}
