/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_pathfinding_hard.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 10:41:46 by thflahau          #+#    #+#             */
/*   Updated: 2019/06/11 12:32:37 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_list.h>
#include <lem_in_stacks.h>
#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>

static inline uint8_t	ft_evaluate_solution(t_map *map, t_listhead *new,
												uint32_t *min)
{
	int32_t				s;

	s = 1;
	ft_delete_unused_stacks(new, map, nbr_optimum_paths(map, new, &s));
	ft_population_distribution(map, new);
	if (ft_stack_entry(new)->ant + ft_stack_entry(new->next)->size < *min)
	{
		*min = ft_stack_entry(new)->ant + ft_stack_entry(new->next)->size;
		return (1);
	}
	return (0);
}

void					ft_advanced_pathfinding(t_map *map, uint32_t **tab)
{
	int32_t				i;
	int32_t				s;
	uint32_t			min;
	int8_t				visited[MAX_VERTICES];
	t_stack				temp;
	t_stack				stacks;
	register uint16_t	index;

	s = 1;
	index = 0;
	min = UINT32_MAX;
	ft_list_init_head(&(temp.list));
	ft_list_init_head(&(stacks.list));
	while (tab[index] != 0)
	{
		ft_fast_bzero(visited, MAX_VERTICES);
		ft_reset_graph(map, tab[index][0], tab[index][1]);
		while (ft_breadth_first_search(map, visited) == EXIT_SUCCESS)
		{
			ft_join_paths(map, &(temp.list));
			ft_update_visited_array(visited, &(temp.list));
		}
		if (ft_evaluate_solution(map, &(temp.list), &min) != 0)
		{
			ft_copy_list(&(stacks.list), &(temp.list));
			stacks.ant = temp.ant;
			nbr_optimum_paths(map, &(stacks.list), &s);
			ft_population_distribution(map, &(stacks.list));
		}
		ft_free_stacks(&(temp.list));
		++index;
	}
	index = 0;
	ft_reset_graph(map, 0, 0);
	while (tab[index] != 0)
	{
		i = 0;
		ft_fast_bzero(visited, MAX_VERTICES);
		while (tab[i] != 0)
		{
			ft_reset_graph(map, tab[index][0], tab[index][1]);
			ft_add_overlap(map, tab[i][0], tab[i][1]);
			while (ft_breadth_first_search(map, visited) == EXIT_SUCCESS)
			{
				ft_join_paths(map, &(temp.list));
				ft_update_visited_array(visited, &(temp.list));
			}
			if (ft_evaluate_solution(map, &(temp.list), &min) != 0)
			{
				ft_copy_list(&(stacks.list), &(temp.list));
				stacks.ant = temp.ant;
				nbr_optimum_paths(map, &(stacks.list), &s);
				ft_population_distribution(map, &(stacks.list));
			}
			ft_free_stacks(&(temp.list));
			++i;
		}
		++index;
	}
	s = 1;
	for (t_listhead *ptr = stacks.list.next; ptr != &(stacks.list); ptr = ptr->next)
		ft_stack_entry(ptr)->ant = 0;
	nbr_optimum_paths(map, &(stacks.list), &s);
	ft_population_distribution(map, &(stacks.list));
	ft_print_movements(map, &(stacks.list));
	ft_free_stacks(&(stacks.list));
}
