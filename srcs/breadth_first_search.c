/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breadth_first_search.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:42:42 by thflahau          #+#    #+#             */
/*   Updated: 2019/06/14 23:40:47 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_queue.h>
#include <lem_in_algorithm.h>

/*
**	Basic BFS algorithm, no prioritizing of vertices to visit.
*/

uint8_t						ft_breadth_first_search(t_map *map, int8_t *visited)
{
	t_queue					queue;
	t_listhead				*node;
	t_edges					*vertex;
	register uint32_t		hashkey;

	ft_list_init_head(&queue.list);
	visited[map->start_index] = visited_node;
	ft_list_add_tail(&(ft_queue_node(map->start_index)->list), &(queue.list));
	node = &(queue.list);
	while (node != node->next)
	{
		hashkey = ft_queue_entry(node->next)->key;
		if (hashkey == map->end_index)
			return (ft_list_del(&(queue.list)));
		ft_list_pop(node->next);
		vertex = map->hashtab[hashkey]->adjc;
		while (vertex != NULL)
		{
			if (vertex->way == open_way && visited[vertex->key] == unvisited_node)
			{
				visited[vertex->key] = visited_node;
				map->hashtab[vertex->key]->prev = map->hashtab[hashkey];
				ft_list_add_tail(&(ft_queue_node(vertex->key)->list), &(queue.list));
			}
			vertex = vertex->next;
		}
	}
	return (EXIT_FAILURE);
}
