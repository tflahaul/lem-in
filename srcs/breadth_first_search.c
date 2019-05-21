/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breadth_first_search.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:42:42 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/21 15:49:31 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_list.h>
#include <lem_in_queue.h>
#include <lem_in_algorithm.h>

/*
**	Basic BFS algorithm, no prioritizing of vertices to visit.
*/

uint8_t						ft_breadth_first_search(t_map *map, uint8_t *visited)
{
	uint32_t				key;
	t_queue					queue;
	t_edges					*vert;
	t_listhead				*node;

	ft_list_head_init(&queue.list);
	visited[map->start_index] = visited_node;
	ft_list_push(&(ft_queue_node(map->start_index)->list), &(queue.list));
	node = queue.list.next;
	while (node != &(queue.list))
	{
		key = ((t_queue *)LIST_ENTRY(node, t_queue, list))->key;
		if (key == map->end_index)
			return (EXIT_SUCCESS);
		ft_list_pop(node);
		vert = map->hashtab[key]->adjc;
		while (vert != NULL)
		{
			if (vert->way == open_way && visited[vert->key] == unvisited_node)
			{
				visited[vert->key] = visited_node;
				map->hashtab[vert->key]->prev = map->hashtab[key];
				ft_list_add_tail(&(ft_queue_node(vert->key)->list), &(queue.list));
			}
			vert = vert->next;
		}
	}
	return (EXIT_FAILURE);
}
