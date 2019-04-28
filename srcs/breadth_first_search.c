/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breadth_first_search.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:42:42 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/28 11:52:44 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_algorithm.h>

static uint8_t		ft_directed_edges(t_graph *g, t_edges *node, uint32_t key)
{
	t_edges			*lst;
	uint8_t			pushed;

	pushed = 0;
	while (node != NULL)
	{
		if (node->way == OPEN && g->visited[node->key] != 1)
		{
			lst = g->map->hashtab[node->key]->adjc;
			while (lst != NULL)
			{
				if (lst->key == key && lst->way == CLOSED)
				{
					pushed = 1;
					g->visited[node->key] = 1;
					g->map->hashtab[node->key]->prev = g->map->hashtab[key];
					ft_queue_append(g->queue, node->key);
				}
				lst = lst->next;
			}
		}
		node = node->next;
	}
	return (pushed > 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}

static void			ft_regular_edges(t_graph *g, t_edges *node, uint32_t key)
{
	while (node != NULL)
	{
		if (node->way == OPEN && g->visited[node->key] != 1)
		{
			g->visited[node->key] = 1;
			g->map->hashtab[node->key]->prev = g->map->hashtab[key];
			ft_queue_append(g->queue, node->key);
		}
		node = node->next;
	}
}

uint8_t				ft_breadth_first_search(t_map *map, uint8_t *vstd)
{
	uint32_t		key;
	t_graph			graph;
	t_edges			*node;
	t_queue			*queue;

	queue = NULL;
	vstd[map->start_index] = 1;
	graph.map = map;
	graph.queue = &queue;
	graph.visited = vstd;
	ft_queue_push(&queue, map->start_index);
	while (queue != NULL)
	{
		key = queue->key;
		if (key == map->end_index)
			return (ft_drain_queue(&queue));
		queue = ft_queue_pop(&queue);
		node = map->hashtab[key]->adjc;
		if (ft_directed_edges(&graph, node, key) == EXIT_FAILURE)
			ft_regular_edges(&graph, node, key);
	}
	return (EXIT_FAILURE);
}
