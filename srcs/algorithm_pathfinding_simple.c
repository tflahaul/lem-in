/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_pathfinding_simple.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 12:03:22 by thflahau          #+#    #+#             */
/*   Updated: 2019/06/11 12:15:06 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_stacks.h>
#include <lem_in_algorithm.h>

void					ft_simple_pathfinding(t_map *map, uint32_t **tab)
{
	int					s;
	t_stack				stacks;
	int8_t				visited[MAX_VERTICES];

	s = 1;
	(void)tab;
	stacks.size = 0;
	ft_list_init_head(&(stacks.list));
	ft_fast_bzero(visited, MAX_VERTICES);
	while (ft_breadth_first_search(map, visited) == EXIT_SUCCESS)
	{
		ft_join_paths(map, &(stacks.list));
		ft_update_visited_array(visited, &(stacks.list));
	}
	nbr_optimum_paths(map, &(stacks.list), &s);
	ft_population_distribution(map, &(stacks.list));
	ft_print_movements(map, &(stacks.list));
	ft_free_stacks(&(stacks.list));
}
