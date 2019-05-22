/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breadth_first_search.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:42:42 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/22 19:32:11 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_queue.h>
#include <lem_in_algorithm.h>

/*
**	Basic BFS algorithm, no prioritizing of vertices to visit.
*/

uint8_t						ft_breadth_first_search(t_map *map, int8_t *vstd)
{
	t_queue					queue;
	t_edges					*vert;
	t_listhead				*node;
	register uint32_t		hashkey;

	ft_list_init_head(&queue.list);
	vstd[map->start_index] = visited_node;
	ft_list_add_tail(&(ft_queue_node(map->start_index)->list), &(queue.list));
	node = &(queue.list);
	while (node != node->next)
	{
		hashkey = ((t_queue *)LIST_ENTRY(node->next, t_queue, list))->key;
		if (hashkey == map->end_index)
			return (ft_list_del(&(queue.list)));
		ft_list_pop(node->next);
		vert = map->hashtab[hashkey]->adjc;
		while (vert != NULL)
		{
			if (vert->way == open_way && vstd[vert->key] < visited_node)
			{
				vstd[vert->key] = vstd[vert->key] + 1;
				map->hashtab[vert->key]->prev = map->hashtab[hashkey];
				ft_list_add_tail(&(ft_queue_node(vert->key)->list), &(queue.list));
			}
			vert = vert->next;
		}
	}
	return (EXIT_FAILURE);
}
