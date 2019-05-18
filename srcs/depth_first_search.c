/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_first_search.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 16:56:22 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/18 16:59:58 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_algorithm.h>
#include <lem_in_compiler.h>

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

uint8_t				ft_depth_first_search(t_graph *g,
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