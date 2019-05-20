/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breadth_first_search.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:42:42 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/20 17:07:34 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>

static void			ft_regular_edges(t_graph *graph, t_edges *ptr, uint32_t key)
{
	while (ptr != NULL)
	{
		if (ptr->way == open_way && graph->visited[ptr->key] != visited_node)
		{
			graph->visited[ptr->key] = visited_node;
			(*graph->map)->hashtab[ptr->key]->prev = (*graph->map)->hashtab[key];
			ft_queue_append(graph->queue, ptr->key);
		}
		ptr = ptr->next;
	}
}

/*
**	Looks at the adjacency list of the 'node' item then goes through
**	all respective adjacency lists of each element within that list.
**	This is done to find directed edges. If found, those are added to the queue.
**	Else, (head == g->queue) -> EXIT_FAILURE
*/

static uint8_t		ft_directed_edges(t_graph *g,
									t_edges *node,
									uint32_t key,
									t_stack *ptr)
{
	t_edges			*list;

	while (node != NULL)
	{
		if (node->way == open_way && g->visited[node->key] != visited_node)
		{
			list = (*g->map)->hashtab[node->key]->adjc;
			while (list != NULL)
			{
				if (list->key == key && list->way == closed_way)
				{
					(*g->map)->hashtab[node->key]->prev = (*g->map)->hashtab[key];
					if (ft_depth_first_search(g, key, node->key, ptr) == EXIT_SUCCESS)
						return (EXIT_SUCCESS);
				}
				list = list->next;
			}
		}
		node = node->next;
	}
	return (EXIT_FAILURE);
}

/*
**	Finds the shortest path while prioritizing fully directed edges.
**	If a directed edge is found we go through that path no matter what
**	(unless vertex has already been 'visited')
*/

uint8_t				ft_breadth_first_search(t_map **map, uint8_t *vstd, void *ptr)
{
	uint32_t		key;
	t_graph			graph;
	t_edges			*node;
	t_queue			*queue;

	queue = NULL;
	vstd[(*map)->start_index] = visited_node;
	graph.map = map;
	graph.queue = &queue;
	graph.visited = vstd;
	ft_queue_push(&queue, (*graph.map)->start_index);
	while (queue != NULL)
	{
		key = queue->key;
		if (key == (*graph.map)->end_index)
			return (ft_drain_queue(&queue));
		queue = ft_queue_pop(&queue);
		node = (*graph.map)->hashtab[key]->adjc;
		if (ft_directed_edges(&graph, node, key, (t_stack *)ptr) == EXIT_SUCCESS)
			return (ft_drain_queue(&queue));
		ft_regular_edges(&graph, node, key);
	}
	return (EXIT_FAILURE);
}

/*
**	Basic BFS algorithm, no prioritizing of vertices to visit.
*/

uint8_t				ft_simple_bfs(t_map *map, uint8_t *visited)
{
	uint32_t		key;
	t_edges			*vert;
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
		vert = map->hashtab[key]->adjc;
		while (vert != NULL)
		{
			if (vert->way != closed_way && visited[vert->key] == unvisited_node)
			{
				visited[vert->key] = visited_node;
				map->hashtab[vert->key]->prev = map->hashtab[key];
				ft_queue_append(&queue, vert->key);
			}
			vert = vert->next;
		}
	}
	return (EXIT_FAILURE);
}
