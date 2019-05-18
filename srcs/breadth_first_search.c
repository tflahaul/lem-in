/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breadth_first_search.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:42:42 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/18 16:53:51 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>
#include <lem_in_stacks.h>

// void					print_paths(t_map *map, t_stack *list)
// {
// 	while (list != NULL)
// 	{
// 		t_queue *ptr = list->path;
// 		ft_printf("\n============\n");
// 		while (ptr != NULL)
// 		{
// 			ft_printf("%s\n", map->hashtab[ptr->key]->name);
// 			ptr = ptr->next;
// 		}
// 		list = list->next;
// 	}
// }

// void				print_stack(t_queue *node, t_map *map)
// {
// 	ft_printf("\n============\n");
// 	while (node != NULL)
// 	{
// 		ft_printf("%s\n", map->hashtab[node->key]->name);
// 		node = node->next;
// 	}
// }

static void			ft_append_path(t_map *map, t_queue *path, t_stack **list)
{
	t_stack			*new;
	t_stack			*node;
	t_vertices		*prev;

	node = *list;
	if (LIKELY((new = ft_allocate_stack_memory()) != NULL))
	{
		while (node->next != NULL)
			node = node->next;
		node->next = new;
		while (path != NULL)
		{
			ft_queue_append(&(new->path), path->key);
			if (path->key != map->start_index)
				++new->size;
			path = ft_queue_pop(&path);
		}
		prev = map->hashtab[new->path->key];
		while ((prev = prev->prev) != NULL)
			ft_queue_push(&(new->path), prev->key);
	}
}

static uint8_t		ft_explore(t_map *map,
								uint8_t visited[MAX_VERTICES],
								uint32_t key,
								t_stack *list)
{
	t_edges			*node;
	t_queue			*stack = NULL;
	t_queue			*parents = NULL;

	ft_queue_push(&stack, key);
	ft_queue_push(&parents, key);
	while (stack != NULL)
	{
		node = map->hashtab[stack->key]->adjc;
		stack = ft_queue_pop(&stack);
		visited[key] = visited_node;
		while (node != NULL)
		{
			if (node->way == open_way && visited[node->key] != visited_node)
			{
				if (node->key == map->end_index)
				{
					ft_queue_append(&parents, node->key);
					ft_append_path(map, parents, &list);
					ft_make_directed(map, list);
	//				print_paths(map, list);
					return (EXIT_SUCCESS);
				}
				visited[node->key] = visited_node;
				ft_queue_append(&parents, node->key);
				ft_queue_push(&stack, node->key);
			}
			node = node->next;
		}
	}
	return (EXIT_FAILURE);
}

static uint8_t		ft_depth_first_search(t_graph *g,
										uint32_t key,
										uint32_t dest,
										t_stack *list)
{
	uint8_t			visited[MAX_VERTICES];

	ft_memcpy(visited, g->visited, MAX_VERTICES);
	visited[key] = unvisited_node;
	if (ft_explore(*g->map, visited, dest, list) == EXIT_SUCCESS)
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
					(*g->map)->hashtab[node->key]->prev = (*g->map)->hashtab[key];
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
