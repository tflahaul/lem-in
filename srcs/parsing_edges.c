/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_edges.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 20:46:10 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/14 15:40:29 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_bug.h>
#include <lem_in_compiler.h>

uint8_t					get_connections(char const *buffer, char *ptr, t_map *map)
{
	char *room_1;
	char *room_2;

	if (!(ptr + 1))
		return (EXIT_FAILURE);
	room_2 = ptr + 1;
	ptr = '\0';
	room1 = buffer;

		
}

uint8_t					ft_parse_edges(__UNUSED t_map *map, char const *buffer)
{
	uint16_t			index;
	char 				*ptr;
//	uint16_t			hashkey;

	index = 0;
//	while (ft_isblank(buffer[index]) == 0)
//		index++;
	if (LIKELY((ptr = strchr(buffer, '-'))))
	{
		get_connections(buffer, ptr, map);
	}
	else
		return (ft_puterror(buffer, UNKCOMM));
	ft_putstr_endl(buffer);
	return (EXIT_SUCCESS);
}
