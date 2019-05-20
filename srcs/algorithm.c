/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 09:59:25 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/20 17:47:19 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_bug.h>
#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>

/*
**	Update 'visited' tab to indicate nodes through which the BFS algorithm
**	have gone.
**	Function only used after overlaps have been handled, when looking for
**	distinct paths
*/

static inline void		ft_update_tab(t_stack *node, uint8_t *visited)
{
	t_queue				*ptr;

	while ((node = node->next) != NULL)
	{
		ptr = node->path;
		while ((ptr = ptr->next)->next != NULL)
			visited[ptr->key] = visited_node;
	}
}

/*
**	Delete stacks that are not needed for ants distribution
*/

static void				ft_delete_unused_stacks(t_stack **stacks, uint16_t nb,
												t_map *map)
{
	t_stack				*node;
	t_stack				*tmp = NULL;
	t_queue				*ptr;

	if (!!(map->visual & VISUAL))
	{
		ptr = (*stacks)->path;
		while (ptr != NULL)
		{
			append_to_file(PATHS, map->hashtab[ptr->key]->name);
			ptr = ptr->next;
		}
		append_to_file(PATHS, "");
	}
	if (nb == 1)
		return ((void)ft_free_stacks(&(*stacks)->next));
	*stacks = ft_stack_pop(stacks);
	node = (*stacks)->next;
	while (nb-- > 0 && node != NULL)
	{
		tmp = node;
		node = node->next;
	}
	tmp->next = NULL;
	ft_free_stacks(&node);
}

uint8_t					ft_algorithm(t_map *map)
{
	t_stack				*list;
	int32_t				path;
	uint8_t				visited[MAX_VERTICES];

	path = 1;
	list = NULL;
	ft_fast_bzero(visited, MAX_VERTICES);
	while (ft_breadth_first_search(&map, visited, list) == EXIT_SUCCESS)
	{
		ft_push_path_to_stack(map, &list);
		ft_fast_bzero(visited, MAX_VERTICES);
		ft_make_directed(map, list);
	}
	if (UNLIKELY(list == NULL))
		return (ft_printf(C_RED"lem-in: %s\n"C_NONE, DEADEND));
	ft_update_graph(map, list);
	ft_free_stacks(&list->next);
	ft_fast_bzero(visited, MAX_VERTICES);
	while (ft_simple_bfs(map, visited) == EXIT_SUCCESS)
	{
		if (UNLIKELY(ft_push_path_to_stack(map, &list)) == EXIT_FAILURE)
			ft_make_directed(map, list);
		ft_fast_bzero(visited, MAX_VERTICES);
		ft_update_tab(list, visited);
	}
	ft_delete_unused_stacks(&list, nbr_optimum_paths(map, list, &path), map);
	ft_population_distribution(map, list);
	ft_print_movements(map, list);
	return (ft_free_stacks(&list));
}

inline uint64_t			ft_last_path_length(t_stack *list)
{
	if (list == NULL)
		return (0);
	while (list->next != NULL)
		list = list->next;
	return (list->size);
}
