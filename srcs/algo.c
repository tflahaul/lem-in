/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 20:51:34 by abrunet           #+#    #+#             */
/*   Updated: 2019/04/17 23:12:16 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_bug.h>
#include <lem_in_queue.h>

static uint8_t		ft_update_graph(t_map *map, t_vertices *ptr, t_queue **q)
{
	uint32_t		key;
	t_edges			*node;
	t_queue			*stacks = NULL;

	stacks = ft_create_new_stack(stacks);
	key = ptr->key;
	ft_queue_push(&stacks, key);
	while ((ptr = ptr->prev) != NULL)
	{
		ft_queue_push(&stacks, ptr->key);
		node = map->hashtab[ptr->key]->adjc;
		while (node != NULL)
		{
			if (node->key == key)
				node->way = WRONGWAY;
			node = node->next;
		}
		key = ptr->key;
	}
	ft_drain_queue(q);
	return (EXIT_SUCCESS);
}

uint8_t				ft_breadth_first_search(t_map *map, uint8_t *visited)
{
	uint32_t		key;
	t_edges			*node;
	t_queue			*queue;

	queue = NULL;
	visited[map->start_index] = 1;
	ft_queue_append(&queue, map->start_index);
	while (queue != NULL)
	{
		key = queue->key;
		if (key == map->end_index)
			return (ft_update_graph(map, map->hashtab[map->end_index], &queue));
		queue = ft_queue_pop(&queue);
		node = map->hashtab[key]->adjc;
		while (node != NULL)
		{
			if (node->way == RIGHTWAY)
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
	return (ft_update_graph(map, map->hashtab[map->end_index], &queue));
}
