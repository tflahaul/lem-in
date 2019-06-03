/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 09:59:25 by thflahau          #+#    #+#             */
/*   Updated: 2019/06/03 11:31:14 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_bug.h>
#include <lem_in_stacks.h>
#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>

static void				ft_join_paths(t_map *map, t_listhead *head)
{
	t_queue				*list;
	t_stack				*node;
	t_vertices			*vertex;

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

static inline void		ft_make_residual_graph(t_map *map, t_listhead *head)
{
	uint32_t			key;
	t_listhead			*new_head;
	t_listhead			*position;

	new_head = &(ft_stack_entry(head)->path->list);
	position = new_head->next;
	key = ft_queue_entry(position)->key;
	while ((position = position->next) != new_head)
	{
		if (ft_overlaps(map, key, ft_queue_entry(position)->key) == 0)
			ft_update_graph(map, head->next);
		key = ft_queue_entry(position)->key;
	}
}

uint8_t					ft_algorithm(t_map *map)
{
	int32_t				s;
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
	ft_print_movements(map, &(stacks.list));
	ft_free_stacks(&(stacks.list));
	return (EXIT_SUCCESS);
}
