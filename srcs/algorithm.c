/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 09:59:25 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/21 15:50:23 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_bug.h>
#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>

uint8_t					ft_algorithm(t_map *map)
{
	uint8_t				visited[MAX_VERTICES];
	t_vertices			*node;

	ft_fast_bzero(visited, MAX_VERTICES);
	ft_breadth_first_search(map, visited);
	node = map->hashtab[map->end_index];
	ft_putchar(10);
	while (node != NULL)
	{
		ft_printf("[ %s ]\n", map->hashtab[node->key]->name);
		node = node->prev;
	}
	return (EXIT_SUCCESS);
}
