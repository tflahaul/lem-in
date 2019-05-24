/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 09:59:25 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/24 16:37:45 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_bug.h>
#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>

/*
** Update 'visited' tab to indicate nodes through which the BFS algorithm have gone
** Function only used after overlaps have been handled, when looking for distinct paths
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
** Delete stacks that are not needed for ants distribution
*/

static void				ft_delete_unused_stacks(t_stack **stacks, uint16_t nb,
												t_map *map)
{
	t_stack				*node;
	t_stack				*tmp;
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

#include <stdio.h>
void					print_paths(t_map *map, t_stack *list)
{
	printf("\n============\n");
	while (list != NULL)
	{
		t_queue *ptr = list->path;
		while (ptr != NULL)
		{
			printf("%s\n", map->hashtab[ptr->key]->name);
			ptr = ptr->next;
		}
		list = list->next;
		printf("\n");
	}
}


uint8_t					ft_algorithm(t_map *map)
{
	t_stack				*list;
	int					path;
	uint8_t				visited[MAX_VERTICES];
	uint8_t				test;
	int					ind;

	ind = 2;
	list = NULL;
	path = 1;

	test = EXIT_SUCCESS;
	ft_fast_bzero(visited, MAX_VERTICES);
	while (--ind && test == EXIT_SUCCESS)
	{
		test = ft_bfs(map, visited, &list);
//		print_paths(map, list);
	}
	if (UNLIKELY(list == NULL))
		return (ft_printf(C_RED"lem-in: %s\n"C_NONE, DEADEND));
	ft_free_stacks(&list->next);
	ft_fast_bzero(visited, MAX_VERTICES);
	while (ft_simple_bfs(map, visited) == EXIT_SUCCESS)
	{
		if (UNLIKELY(ft_push_path_to_stack(map, &list)) == EXIT_FAILURE)
			ft_make_directed(map);
		ft_fast_bzero(visited, MAX_VERTICES);
		ft_update_tab(list, visited);
	}
	print_paths(map, list);

	ft_delete_unused_stacks(&list, nbr_optimum_paths(map, list, &path), map);
	ft_population_distribution(map, list);
//	print_movements
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
