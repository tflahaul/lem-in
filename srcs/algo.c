/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 20:51:34 by abrunet           #+#    #+#             */
/*   Updated: 2019/04/18 00:28:37 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_bug.h>
#include <lem_in_queue.h>

uint8_t				add_end_path(t_vertices *end)
{
	static uint8_t	ind;

	end->end_paths[ind] = *end->prev;
	ind++;
	return (EXIT_SUCCESS);
}

uint8_t				close_connection(uint64_t key2, t_map *map, t_edges *node)
{
	t_edges			*tmp;
	uint8_t			entry;
	uint64_t		key1;
	
	key1 = node->key;
	entry = 0;
	if (key1 == map->start_index || key2 == map->start_index || key1 == map->end_index || key2 == map->end_index)
		entry = 1;
	node->sens = (entry) ? OPEN : REMOVED;
	tmp = map->hashtab[key1]->adjc;
	while (tmp && tmp->key != key2)
		tmp = tmp->next;
	tmp->sens = (entry) ? OPEN : REMOVED;
	return (EXIT_SUCCESS);
}

/*
**	test == 0, first loop pour shortest path
**	test = 1, disappearing overlapping edge;
**	test > 1, find every other non overlapping paths
*/
static uint8_t		ft_update_graph(t_map *map, t_vertices *ptr, t_queue **q)
{
	uint32_t		key;
	t_edges			*node;
	static uint8_t	test;

	key = ptr->key;
	add_end_path(ptr);
	if (test++ == 1)
		return (EXIT_SUCCESS);
	while ((ptr = ptr->prev) != NULL)
	{
		node = map->hashtab[ptr->key]->adjc;
		while (node != NULL)
		{
			if (node->key == key && node->sens)
				node->sens = CLOSED;
			node = node->next;
		}
		key = ptr->key;
	}
	ft_drain_queue(q);
	return (EXIT_SUCCESS);
}

uint8_t				ft_breadth_first_search(t_map *map, uint8_t *visited)
{
	uint64_t		key;
	t_edges			*node;
	t_queue			*queue;
	static uint8_t	test;

	queue = NULL;
	visited[map->start_index] = 1;
	ft_queue_push(&queue, map->start_index);
	while (queue != NULL)
	{
		key = queue->key;
		if (key == map->end_index)
		{
			test++;
			return (ft_update_graph(map, map->hashtab[map->end_index], &queue));
		}
		queue = ft_queue_pop(&queue);
		node = map->hashtab[key]->adjc;
		while (node != NULL)
		{
			if (node->sens != CLOSED && node->sens != REMOVED)
			{
				if (visited[node->key] == 0 && (visited[node->key] = 1))
				{
					map->hashtab[node->key]->prev = map->hashtab[key];
					ft_queue_push(&queue, node->key);
				}
			}
			else if (node->sens == CLOSED && test <= 1)
				close_connection(key, map, node);
			node = node->next;
		}
	}
//	ft_update_graph(map, map->hashtab[map->end_index], &queue);
	return (EXIT_FAILURE);
}
