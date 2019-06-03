/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 09:59:25 by thflahau          #+#    #+#             */
/*   Updated: 2019/06/03 15:32:05 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_bug.h>
#include <lem_in_stacks.h>
#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>
#include <stdio.h>

__attribute__((deprecated))
static void					print_stack(t_map *map, t_listhead *head)
{
	t_stack					*node;
	t_listhead				*ptr;
	t_listhead				*position = head->next;
	while (position != head)
	{
		node = ft_stack_entry(position);
		ptr = node->path->list.next;
		printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
		while (ptr != &(node->path->list))
		{
			printf("[ %s ]\n", map->hashtab[ft_queue_entry(ptr)->key]->name);
			ptr = ptr->next;
		}
		position = position->next;
	}
	ft_putchar(10);
}

static void					ft_join_paths(t_map *map, t_listhead *head)
{
	t_queue					*list;
	t_stack					*node;
	t_vertices				*vertex;

	if (LIKELY((node = ft_stack_node()) != NULL))
	{
		if (LIKELY((node->path = (t_queue *)malloc(sizeof(t_queue))) != NULL))
			ft_list_init_head(&(node->path->list));
		vertex = map->hashtab[map->end_index];
		while (vertex != NULL)
		{
			if (LIKELY((list = ft_queue_node((uint32_t)vertex->key)) != NULL))
			{
				ft_list_push(&(list->list), &(node->path->list));
				++node->size;
			}
			vertex = vertex->prev;
		}
		ft_list_add_tail(&(node->list), head);
	}
}

static inline void		ft_update_visited(int8_t *array, t_listhead *head)
{
	t_listhead			*ref;
	t_listhead			*node;
	t_listhead			*position;

	position = head;
	ft_fast_bzero(array, MAX_VERTICES);
	while ((position = position->next) != head)
	{
		ref = &(ft_stack_entry(position)->path->list);
		node = ref->next;
		while ((node = node->next) != ref->prev)
			array[ft_queue_entry(node)->key] = visited_node;
	}
}

static t_stack			*ft_get_paths_in_graph(t_map *map)
{
	t_stack				*stacks;
	t_stack				*final = NULL;
	uint32_t			tmp = 0;
	uint32_t			min = 0;
	uint32_t			superposition[2];
	int8_t				visited[MAX_VERTICES];

	if (UNLIKELY((stacks = ft_stack_node()) == NULL))
		return (NULL);
	ft_list_init_head(&(stacks->list));
	ft_fast_bzero(visited, MAX_VERTICES);
	while (ft_breadth_first_search(map, visited) == EXIT_SUCCESS)
	{
		ft_join_paths(map, &(stacks->list));
		ft_update_visited(visited, &(stacks->list));
		/* On trouve une superposition en inversant le chemin */
		if (ft_make_directed(map, stacks->list.prev) == EXIT_FAILURE)
		{
			/* Remplie le tableau `superposition` par les deux clefs où se
			 * situe la superposition */
			ft_get_superposition(stacks->list.prev, superposition);
			/* Remet tout le graph à 0 excepté la superposition [0]-[1]
			 * pour partir sur une nouvelle recherche de chemins */
			ft_update_graph(map, superposition[0], superposition[1]);
			tmp = ft_compute_steps(&(stacks->list));
			if (tmp < min)
			{
				min = tmp;
				ft_free_stacks(final);
				final = stacks;
			}
			ft_fast_bzero(visited, MAX_VERTICES);
		}
	}
	if (UNLIKELY(&(stacks->list) == stacks->list.next))
		return (NULL);
	/* Ici, on est """censés""" avoir la meilleure solution (final) */
	return (final);
}

uint8_t					ft_algorithm(t_map *map)
{
	t_stack				*ptr;

	ptr = ft_get_paths_in_graph(map);
/*	int32_t				s;
	t_graph				graph;
	t_stack				stacks;

	s = 1;
	graph.map = map;
	ft_memset(&stacks, 0, sizeof(t_stack));
	ft_list_init_head(&(stacks.list));
	ft_fast_bzero(graph.visited, MAX_VERTICES);
	while (ft_breadth_first_search(map, graph.visited) == EXIT_SUCCESS)
	{
		ft_join_paths(map, &(stacks.list));
		ft_fast_bzero(graph.visited, MAX_VERTICES);
		ft_make_directed(map, stacks.list.prev);
		ft_make_residual_graph(map, stacks.list.prev);
	}
	if (UNLIKELY(&(stacks.list) == stacks.list.next))
		return (ft_puterror(DEADEND));
	ft_sort_stacks(&(stacks.list));
	ft_delete_unused_stacks(&(stacks.list), map, \
		nbr_optimum_paths(map, &(stacks.list), &s));
//	ft_keep_best_paths(&(stacks.list));
	ft_population_distribution(map, &(stacks.list));
	ft_print_movements(map, &(stacks.list));	*/
	ft_free_stacks(&(ptr->list));
	return (EXIT_SUCCESS);
}
