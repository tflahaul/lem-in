/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:27:29 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/19 18:59:37 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_queue.h>
#include <lem_in_stacks.h>
#include <lem_in_compiler.h>

uint32_t				get_optimum_path_nb(t_stack *list, uint32_t ants, uint64_t pos)
{
	uint32_t			res;
	uint32_t			index;
	uint32_t			sum1;
	uint32_t			sum2;
	t_stack				*tmp;

	sum1 = ants + (list->size - 1) - 1;
	tmp = list;
	if (pos && tmp->next)
		tmp = list->next;
	if (!list)
		return (0);
	res = 1;
	index = 1;
	while (tmp)
	{
		sum2 = (ants / index + (tmp->size - 1) - 1);
		if (sum1 > sum2)
		{
			sum1 = sum2;
			res = index;
		}
		tmp = tmp->next;
		index++;
	}
	return (res);
}

void					ft_algorithm(t_map *map)
{
	t_stack				*list;
	uint32_t			paths;
	uint8_t				visited[MAX_VERTICES];
	int					p = 0;

	list = ft_allocate_stack_memory();
	ft_memset(visited, 0, MAX_VERTICES);
	while (ft_breadth_first_search(map, visited, &p) == EXIT_SUCCESS)
	{
		if (p > 0)
			ft_push_path_to_stack(map, &list);
		ft_memset(visited, 0, MAX_VERTICES);
	}
//	printf("%u = start %u = end\n", map->start_edges, map->end_edges);
	set_last_to_null(list);
	paths = get_optimum_path_nb(list, map->population, map->superposition);
	ft_print_movements(map, list, paths + 1);
//	ft_print_movements(map, list->path, list->size);
	ft_free_stacks(&list);
}
