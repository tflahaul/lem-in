/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 09:59:25 by thflahau          #+#    #+#             */
/*   Updated: 2019/06/05 13:47:15 by thflahau         ###   ########.fr       */
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

static uint32_t			*foo(__unused t_map *map, t_listhead *head)
{
	t_listhead			*position;

	position = head;
	while ((position = position->next) != head);
	return (NULL);
}

static uint32_t			**ft_get_overlaps(t_map *map, t_listhead *head)
{
	uint32_t			**tab;
	uint64_t			length;
	t_listhead			*position;
	register uint16_t	index;

	index = 0;
	length = ft_list_size(head);
	if (!(tab = (uint32_t **)malloc(sizeof(uint32_t *) * length)))
		return (NULL);
	ft_memset(tab, 0, length);
	position = head;
	while ((position = position->next) != head)
	{
		tab[index] = foo(map, &(ft_stack_entry(position)->path->list));
		if (tab[index])
			++index;
	}
	return (tab);
}

static inline uint32_t	**ft_search_for_overlaps(t_map *map)
{
	uint32_t			**tab;
	t_stack				stacks;
	int8_t				visited[MAX_VERTICES];

	ft_list_init_head(&(stacks.list));
	ft_fast_bzero(visited, MAX_VERTICES);
	while (ft_breadth_first_search(map, visited) == EXIT_SUCCESS)
	{
		ft_join_paths(map, &(stacks.list));
		ft_make_directed(map, stacks.list.prev);
		ft_update_visited(visited, &(stacks.list));
	}
	tab = ft_get_overlaps(map, &(stacks.list));
	ft_free_stacks(&(stacks.list));
	return (tab);
}

uint8_t					ft_algorithm(t_map *map)
{
	t_stack				*solution;
	uint32_t			**overlaps;

	solution = NULL;
	overlaps = ft_search_for_overlaps(map);
//	solution = ft_get_best_solution(map, overlaps);
//	ft_print_movements(map, &(solution->list));
	return (EXIT_SUCCESS);
}
