/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_first_search.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 16:56:22 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/19 19:22:53 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_algorithm.h>
#include <lem_in_compiler.h>

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

static uint8_t		ft_explore(t_map *map, uint8_t visited[MAX_VERTICES],
							uint32_t key, t_stack *list, int nb)
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
		while (node != NULL && nb > 0)
		{
			if (node->way == open_way && visited[node->key] != visited_node)
			{
				if (node->key == map->end_index)
				{
					ft_queue_append(&parents, node->key);
					ft_append_path(map, parents, &list);
					ft_make_directed(map, list);
					return (EXIT_SUCCESS);
				}
				visited[node->key] = visited_node;
				ft_queue_append(&parents, node->key);
				ft_queue_push(&stack, node->key);
				--nb;
			}
			node = node->next;
		}
	}
	ft_drain_queue(&parents);
	return (EXIT_FAILURE);
}

uint8_t				ft_depth_first_search(t_graph *g,
					uint32_t key,
					uint32_t dest,
					t_stack *list)
{
	uint16_t		nb = list->size;
	uint8_t			visited[MAX_VERTICES];

	ft_memcpy(visited, g->visited, MAX_VERTICES);
	visited[key] = unvisited_node;
	while (ft_explore(*g->map, visited, dest, list, nb) == EXIT_FAILURE)
		if (nb++ >= 60)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
