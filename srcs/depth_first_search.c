/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_first_search.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 16:56:22 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/20 19:19:49 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_algorithm.h>
#include <lem_in_compiler.h>
#include <stdio.h>

void					print_graph(t_map *map)
{
	register uint16_t	index = 0;

	ft_putchar(10);
	while (index < MAX_VERTICES)
	{
		if (map->hashtab[index]->name != NULL)
		{
			printf("%s\t", map->hashtab[index]->name);
			t_edges *ptr = map->hashtab[index]->adjc;
			while (ptr != NULL)
			{
				printf("  -> %s(%i)", map->hashtab[ptr->key]->name, ptr->way);
				ptr = ptr->next;
			}
			printf("\n");
		}
		index++;
	}
}

void					print_paths(t_map *map, t_stack *list)
{
	while (list != NULL)
	{
		t_queue *ptr = list->path;
		printf("\n============\n");
		while (ptr != NULL)
		{
			printf("%s\n", map->hashtab[ptr->key]->name);
			ptr = ptr->next;
		}
		list = list->next;
	}
}

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
			path = ft_queue_pop(&path);
			++new->size;
		}
		prev = map->hashtab[new->path->key];
		while ((prev = prev->prev) != NULL)
		{
			ft_queue_push(&(new->path), prev->key);
			if (prev->key != map->start_index)
				++new->size;
		}
	}
}

static uint8_t		ft_explore(t_map *map, uint8_t visited[MAX_VERTICES],
							uint32_t key, t_stack *list, __unused int16_t nb)
{
	t_edges			*node;
	t_queue			*stack = NULL;
	t_queue			*parents = NULL;

	ft_queue_push(&stack, key);
	ft_queue_push(&parents, key);
	visited[key] = visited_node;
	while (stack != NULL && nb > 0)
	{
		node = map->hashtab[stack->key]->adjc;
		stack = ft_queue_pop(&stack);
		while (node != NULL)
		{
			if (node->way == open_way && visited[node->key] != visited_node)
			{
				visited[node->key] = visited_node;
				ft_queue_push(&stack, node->key);
				ft_queue_append(&parents, node->key);
				nb--;
				if (node->key == map->end_index)
				{
					ft_queue_append(&parents, node->key);
					ft_append_path(map, parents, &list);
					ft_make_directed(map, list);
					ft_drain_queue(&stack);
					return (EXIT_SUCCESS);
				}
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
	while (ft_explore(*g->map, visited, dest, list, ++nb) != EXIT_SUCCESS)
	{
		ft_memcpy(visited, g->visited, MAX_VERTICES);
		visited[key] = unvisited_node;
		if (nb >= 100)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
