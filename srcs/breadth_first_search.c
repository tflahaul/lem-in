/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breadth_first_search.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:42:42 by thflahau          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/05/17 23:50:13 by thflahau         ###   ########.fr       */
=======
/*   Updated: 2019/05/17 22:50:02 by abrunet          ###   ########.fr       */
>>>>>>> hash
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_algorithm.h>
#include <stdio.h>

void					print_paths(t_map *map, t_stack *list)
{
	printf("\n============\n");
	while (list != NULL)
	{
		t_queue *ptr = list->path;
		while (ptr != NULL)
		{
			printf("%s\n", map->hashtab[ptr->key]->name);
			ptr = ptr->next;
		}
		list = list->next;
	}
}

static uint8_t		ft_explore_child(t_map *map, uint8_t visited[MAX_VERTICES], uint32_t key, t_stack *list)
{
	t_edges			*ptr;
	t_edges			*node;

	if (key == map->end_index)
	{
		ft_push_path_to_stack(map, &list);
//		print_paths(map, list);
		ft_make_directed(map);
		return (EXIT_SUCCESS);
	}
	node = map->hashtab[key]->adjc;
	visited[key] = visited_node;
	while (node != NULL)
	{
		ptr = map->hashtab[node->key]->adjc;
		while (ptr != NULL)
		{
			if (visited[ptr->key] != visited_node && ptr->way == open_way)
			{
				visited[ptr->key] = visited_node;
				map->hashtab[ptr->key]->prev = map->hashtab[node->key];
				ft_explore_child(map, visited, ptr->key, list);
			}
			ptr = ptr->next;
		}
		node = node->next;
	}
	return (EXIT_FAILURE);
}

static uint8_t		ft_depth_first_search(t_graph *g, uint32_t key, uint32_t dest, t_stack *list)
{
	uint8_t			visited[MAX_VERTICES];

	ft_memcpy(visited, g->visited, MAX_VERTICES);
	visited[key] = unvisited_node;
//	(*g->map)->hashtab[dest]->prev = (*g->map)->hashtab[key];
	if (ft_explore_child(*g->map, visited, dest, list) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

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
** 	Looks at the adjacency list of the 'node' item then goes through
** 	all respective adjacency lists of each element within that list.
**	This is done to find directed edges. If found, those are added to the queue.
** 	Else, (head == g->queue) -> EXIT_FAILURE
*/

static uint8_t		ft_directed_edges(t_graph *g, t_edges *node, uint32_t key, t_stack *ptr)
{
	t_edges			*list;
	t_queue			*head;

	head = *g->queue;
	while (node != NULL)
	{
		if (node->way == open_way && g->visited[node->key] != visited_node)
		{
			list = (*g->map)->hashtab[node->key]->adjc;
			while (list != NULL)
			{
				if (list->key == key && list->way == closed_way)
				{
	//				(*g->map)->hashtab[node->key]->prev = (*g->map)->hashtab[key];
					if (ft_depth_first_search(g, key, node->key, ptr) == EXIT_SUCCESS)
						return (EXIT_SUCCESS);
				}
				list = list->next;
			}
		}
		node = node->next;
	}
	return (head != *g->queue ? EXIT_SUCCESS : EXIT_FAILURE);
}

/*
**	Finds the shortest path while prioritizing fully directed edges.
**	If a directed edge is found we go through that path no matter what
**	(unless vertex has already been 'visited')
*/

uint8_t				ft_breadth_first_search(t_map *map, uint8_t *vstd, void *ptr)
{
	uint32_t		key;
	t_graph			graph;
	t_edges			*node;
	t_queue			*queue;

	queue = NULL;
	vstd[map->start_index] = visited_node;
	graph.map = &map;
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
		if (ft_directed_edges(&graph, node, key, (t_stack *)ptr) == EXIT_FAILURE)
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
			if (v->way == open_way && !visited[v->key] && (visited[v->key] = 1))
			{
				map->hashtab[v->key]->prev = map->hashtab[key];
				ft_queue_append(&queue, v->key);
			}
			v = v->next;
		}
	}
	return (EXIT_FAILURE);
}
