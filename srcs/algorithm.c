/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 09:59:25 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/29 16:43:26 by thflahau         ###   ########.fr       */
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

/*
**	Update 'visited' array to indicate nodes through which the BFS algorithm
**	have gone. Function only used after overlaps have been handled, when
**	looking for distinct paths.
*/

static inline void		ft_update_visited_array(int8_t *array, t_listhead *head)
{
	t_listhead			*ref;
	t_listhead			*node;
	t_listhead			*position;

	position = head->next;
	ft_fast_bzero(array, MAX_VERTICES);
	while ((position = position->next) != head)
	{
		ref = &(ft_stack_entry(position)->path->list);
		node = ref->next;
		while ((node = node->next) != ref->prev)
			array[ft_queue_entry(node)->key] = visited_node;
	}
}

static void				ft_reopen_path(t_map *map,
										t_listhead *head,
										uint32_t hashkey,
										uint32_t prevkey)
{
	t_edges				*ptr;
	t_queue				*node;
	t_listhead			*position;

	position = head;
	while ((position = position->next) != head)
	{
		node = ft_queue_entry(position);
		if (node->key != hashkey && node->key != prevkey)
		{
			ptr = map->hashtab[node->key]->adjc;
			while (LIKELY(ptr != NULL) && ptr->key != prevkey)
				ptr = ptr->next;
			if (LIKELY(ptr != NULL))
				ptr->way = open_way;
		}
	}
}

static void				ft_make_residual_graph(t_map *map, t_listhead *head)
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
			ft_reopen_path(map, new_head, key, ft_queue_entry(position)->key);
		key = ft_queue_entry(position)->key;
	}
}

uint8_t					ft_algorithm(t_map *map)
{
	int					s;
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
	ft_update_graph(map, &(stacks.list));
	if (UNLIKELY(&(stacks.list) == stacks.list.next))
		return (ft_puterror(DEADEND));
	ft_update_graph(map, &(stacks.list));
	ft_fast_bzero(graph.visited, MAX_VERTICES);
	ft_delete_unused_stacks(&(stacks.list), 1);
	while (ft_breadth_first_search(map, graph.visited) == EXIT_SUCCESS)
	{
		ft_join_paths(map, &(stacks.list));
		if (UNLIKELY(ft_stack_entry(stacks.list.next)->size == 2))
			break ;
		ft_update_visited_array(graph.visited, &(stacks.list));
	}
	ft_delete_unused_stacks(&(stacks.list), \
		nbr_optimum_paths(map, &(stacks.list), &s));
	ft_population_distribution(map, &stacks);
	ft_free_stacks(&(stacks.list));
	return (EXIT_SUCCESS);
}
