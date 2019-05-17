/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breadth_first_search.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:42:42 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/17 21:02:05 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>

static void			ft_regular_edges(t_graph *g, t_edges *node, uint32_t key)
{
	while (node != NULL)
	{
		if (node->way == OPEN && g->visited[node->key] == unvisited_node)
		{
			g->visited[node->key] = visited_node;
			g->map->hashtab[node->key]->prev = g->map->hashtab[key];
			ft_queue_append(g->queue, node->key);
		}
		node = node->next;
	}
}

/*
** Looks at the adjacency list of the 'node' item then goes through 
** all respective adjacency lists of each element within that list. 
** This is done to find directed edges. If found, those are added to the queue. 
** Else, (head == g->queue) -> EXIT_FAILURE
*/

static uint8_t		ft_directed_edges(t_graph *g, t_edges *node, uint32_t key)
{
	t_edges			*list;
	t_queue			*head;

	head = *(g->queue);
	while (node != NULL)
	{
		if (node->way == OPEN && g->visited[node->key] == unvisited_node)
		{
			list = g->map->hashtab[node->key]->adjc;
			while (list != NULL)
			{
				if (list->key == key && list->way == CLOSED)
				{
					g->visited[node->key] = visited_node;
					g->map->hashtab[node->key]->prev = g->map->hashtab[key];
					ft_queue_append(g->queue, node->key);
				}
				list = list->next;
			}
		}
		node = node->next;
	}
	return (head != *(g->queue) ? EXIT_SUCCESS : EXIT_FAILURE);
}

/*
** Finds the shortest path while prioritizing fully directed edges. If a directed edge is found
** we go through that path no matter what (unless vertex has already been 'visited')
*/

uint8_t				ft_breadth_first_search(t_map *map, uint8_t *vstd)
{
	uint32_t		key;
	t_graph			graph;
	t_edges			*node;
	t_queue			*queue;

	queue = NULL;
	graph.map = map;
	graph.queue = &queue;
	vstd[map->start_index] = visited_node;
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

/*
** Basic BFS algorithm, no prioritizing of vertices to visit.
*/

uint8_t				ft_simple_bfs(t_map *map, uint8_t *visited)
{
	uint32_t		key;
	t_edges			*v;
	t_queue			*queue;

	queue = NULL;
	visited[map->start_index] = visited_node;
	ft_queue_push(&queue, map->start_index);
	while (queue != NULL)
	{
		key = queue->key;
		if (key == map->end_index)
			return (ft_drain_queue(&queue));
		queue = ft_queue_pop(&queue);
		v = map->hashtab[key]->adjc;
		while (v != NULL)
		{
			if (v->way == OPEN && !visited[v->key] && (visited[v->key] = 1))
			{
				map->hashtab[v->key]->prev = map->hashtab[key];
				ft_queue_append(&queue, v->key);
			}
			v = v->next;
		}
	}
	return (EXIT_FAILURE);
}
