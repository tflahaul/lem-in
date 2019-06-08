/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 09:59:25 by thflahau          #+#    #+#             */
/*   Updated: 2019/06/08 12:13:01 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_bug.h>
#include <lem_in_stacks.h>
#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>

#include <stdio.h>

inline void				ft_update_visited_array(int8_t *array, t_listhead *head)
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
	register uint16_t	ix;

	ix = 0;
	while (tab[ix] != 0)
		++ix;
	if (UNLIKELY(ix >= 32UL))
		return (EXIT_FAILURE);
	if (UNLIKELY(!(tab[ix] = (uint32_t *)malloc(sizeof(uint32_t) << 1))))
		return (EXIT_FAILURE);
	ft_actually_put_into_tab(map, &(ft_stack_entry(head)->path->list), tab[ix]);
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
	prevkey = ft_queue_entry(new->next)->key;
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
		{
			if (overlaps == NULL)
				if ((overlaps = (uint32_t **)malloc(sizeof(uint32_t *) * 32UL)))
					ft_memset(overlaps, 0, 32UL);
			ft_put_into_tab(map, stacks.list.prev, overlaps);
		}
	}
	ft_free_stacks(&(stacks.list));
	return (overlaps);
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
	ft_reinitialize_graph(map);
	funptr[!!(tab)](map, tab);
	ft_free_tab(tab);
	return (EXIT_SUCCESS);
}
