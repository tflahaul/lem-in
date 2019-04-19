/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 20:51:34 by abrunet           #+#    #+#             */
/*   Updated: 2019/04/19 16:09:29 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_bug.h>
#include <lem_in_queue.h>

uint8_t				check_inverse(uint32_t currnt_key, uint32_t prev_key, t_map *map)
{
	t_edges			*node;

	node = map->hashtab[prev_key]->adjc;
	while (node->key != currnt_key)
		node = node->next;
	if (node->way == CLOSED)
	{
		node->way = REMOVED;
		return (1);
	}
	return (0);
}

static uint8_t		ft_update_graph(t_map *map, t_vertices *ptr)
{
	uint32_t		key;
	t_edges			*node;

	key = ptr->key;
	while ((ptr = ptr->prev) != NULL)
	{
		node = map->hashtab[ptr->key]->adjc;
		while (node != NULL)
		{
			if (node->key == key)
			{
				node->way = CLOSED;
				if (check_inverse(ptr->key, node->key, map))
				{
					node->way = REMOVED;
					map->superposition = 1;
				}
			}
			node = node->next;
		}
		key = ptr->key;
	}
	return (EXIT_SUCCESS);
}

uint8_t				ft_breadth_first_search(t_map *map, uint8_t *visited)
{
	uint64_t		key;
	t_edges			*node;
	t_queue			*queue;

	queue = NULL;
	visited[map->start_index] = 1;
	ft_queue_push(&queue, map->start_index);
	while (queue != NULL)
	{
		key = queue->key;
		if (key == map->end_index)
		{
			ft_drain_queue(&queue);
			return (ft_update_graph(map, map->hashtab[map->end_index]));
		}
		queue = ft_queue_pop(&queue);
		node = map->hashtab[key]->adjc;
		while (node != NULL)
		{
			if (node->way != CLOSED && node->way != REMOVED)
			{
				if (visited[node->key] == 0 && (visited[node->key] = 1))
				{
					map->hashtab[node->key]->prev = map->hashtab[key];
					ft_queue_append(&queue, node->key);
				}
			}
			node = node->next;
		}
	}
	ft_drain_queue(&queue);
	return (EXIT_FAILURE);
}
