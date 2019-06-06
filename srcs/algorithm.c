/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 09:59:25 by thflahau          #+#    #+#             */
/*   Updated: 2019/06/06 22:17:12 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_bug.h>
#include <lem_in_stacks.h>
#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>

#include <stdio.h>

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

static void				ft_actually_put_into_tab(t_map *map, t_listhead *head,
																uint32_t *tab)
{
	uint32_t			hashkey;
	uint32_t			prevkey;
	t_listhead			*position;

	position = head->next;
	prevkey = ft_queue_entry(head->next)->key;
	while ((position = position->next) != head)
	{
		hashkey = ft_queue_entry(position)->key;
		if (ft_overlaps(map, prevkey, hashkey) == EXIT_SUCCESS)
		{
			tab[0] = prevkey;
			tab[1] = hashkey;
		}
		prevkey = hashkey;
	}
}

static uint8_t			ft_put_into_tab(t_map *map, t_listhead *head,
										uint32_t **tab)
{
	register uint16_t	index;

	if (tab == NULL)
		if (LIKELY((tab = (uint32_t **)malloc(sizeof(uint32_t *) * 32UL))))
			ft_memset(tab, 0, 32UL);
	index = 0;
	while (tab[index] != 0)
		++index;
	if (UNLIKELY(index >= 32UL))
		return (EXIT_FAILURE);
	if (UNLIKELY(!(tab[index] = (uint32_t *)malloc(sizeof(uint32_t) << 1))))
		return (EXIT_FAILURE);
	ft_actually_put_into_tab(map, &(ft_stack_entry(head)->path->list), tab[index]);
	return (EXIT_SUCCESS);
}

static uint8_t			ft_foo(t_map *map, t_listhead *head)
{
	uint32_t			prevkey;
	uint32_t			hashkey;
	t_listhead			*position;
	t_listhead			*new;

	new = &(ft_stack_entry(head)->path->list);
	position = new;
	prevkey = ft_queue_entry(new)->key;
	while ((position = position->next) != new)
	{
		hashkey = ft_queue_entry(position)->key;
		if (ft_overlaps(map, prevkey, hashkey) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
		prevkey = hashkey;
	}
	return (EXIT_FAILURE);
}

static inline uint32_t	**ft_search_for_overlaps(t_map *map)
{
	t_stack				stacks;
	uint32_t			**overlaps;
	int8_t				visited[MAX_VERTICES];

	overlaps = NULL;
	ft_list_init_head(&(stacks.list));
	ft_fast_bzero(visited, MAX_VERTICES);
	while (ft_breadth_first_search(map, visited) == EXIT_SUCCESS)
	{
		ft_join_paths(map, &(stacks.list));
		ft_fast_bzero(visited, MAX_VERTICES);
		ft_make_directed(map, stacks.list.prev);
		if (ft_foo(map, stacks.list.prev) == EXIT_SUCCESS)
			ft_put_into_tab(map, stacks.list.prev, overlaps);
	}
	ft_free_stacks(&(stacks.list));
	return (overlaps);
}

static inline void		ft_free_tab(uint32_t **tab)
{
	register uint16_t	index;

	index = 0;
	if (LIKELY(tab != NULL))
	{
		while (index < 32U)
			if (tab[index++] != NULL)
				free((void *)tab[index - 1]);
		free((void *)tab);
	}
}

static void				ft_simple_pathfinding(t_map *map, __unused uint32_t **t)
{
	t_stack				stacks;
	int8_t				visited[MAX_VERTICES];

	ft_list_init_head(&(stacks.list));
	ft_fast_bzero(visited, MAX_VERTICES);
	while (ft_breadth_first_search(map, visited) == EXIT_SUCCESS)
	{
		ft_join_paths(map, &(stacks.list));
		ft_update_visited(visited, stacks.list.prev);
	}
	ft_print_movements(map, &(stacks.list));
	ft_free_stacks(&(stacks.list));
}

static void				ft_advanced_pathfinding(t_map *map, uint32_t **tab)
{
	(void)map;
	(void)tab;
}

uint8_t					ft_algorithm(t_map *map)
{
	uint32_t			**tab;
	void				(*funptr[2])(t_map *, uint32_t **);

	funptr[0] = &ft_simple_pathfinding;
	funptr[1] = &ft_advanced_pathfinding;
	tab = ft_search_for_overlaps(map);
	funptr[!!(tab)](map, tab);
	ft_free_tab(tab);
	return (EXIT_SUCCESS);
}
