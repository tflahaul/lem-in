/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 09:59:25 by thflahau          #+#    #+#             */
/*   Updated: 2019/06/15 18:25:44 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_bug.h>
#include <lem_in_stacks.h>
#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>

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

uint8_t					ft_algorithm(t_map *map)
{
	t_stack				stacks;
	int8_t				visited[MAX_VERTICES];

	ft_list_init_head(&(stacks.list));
	ft_fast_bzero(visited, MAX_VERTICES);
	while (ft_breadth_first_search(map, visited) == EXIT_SUCCESS)
	{
		ft_join_paths(map, &(stacks.list));
		ft_fast_bzero(visited, MAX_VERTICES);
		ft_make_directed(map, stacks.list.prev);
	}
	if (UNLIKELY(stacks.list.next == &(stacks.list)))
		return (ft_puterror(DEADEND));
	ft_update_graph(map, &(stacks.list));
	ft_free_stacks(&(stacks.list));
	while (ft_breadth_first_search(map, visited) == EXIT_SUCCESS)
	{
		ft_join_paths(map, &(stacks.list));
		ft_update_visited_array(visited, &(stacks.list));
	}
	ft_delete_unused_stacks(&(stacks.list), map, \
		nbr_optimum_paths(map, &(stacks.list)));
	ft_population_distrib(map, &(stacks.list), 1);
	ft_print_movements(map, &(stacks.list));
	ft_free_stacks(&(stacks.list));
	return (EXIT_SUCCESS);
}
