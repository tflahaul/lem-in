/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_edges.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 20:46:10 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/14 14:40:32 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_bug.h>
#include <lem_in_compiler.h>

uint8_t					ft_parse_edges(__UNUSED t_map *map, char const *buffer)
{
	uint16_t			index;
//	uint16_t			hashkey;

	index = 0;
	while (ft_isblank(buffer[index]) == 0)
		index++;
	if (UNLIKELY(buffer[index] != '-'))
		return (ft_puterror(buffer, UNKCOMM));
	ft_putstr_endl(buffer);
	return (EXIT_SUCCESS);
}
