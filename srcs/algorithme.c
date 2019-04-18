/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithme.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:27:29 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/18 23:12:52 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_queue.h>
#include <lem_in_stacks.h>

uint32_t				get_optimum_path_nb(t_stack *list, uint32_t ants, uint64_t pos)
{
	uint32_t	res;
	uint32_t	index;
	uint32_t	sum1;
	int			ants_a;
	uint32_t	sum2;
	t_stack		*tmp;

	printf("%u = ants\n", ants);
	sum1 = ants + (list->size - 1) - 1;
//	printf("%u = sum1\n", sum1);
	tmp = list;
	if (pos && tmp->next)
		tmp = list->next;
	if (!list)
		return (0);
	res = 1;
	index = 1;
	while (tmp)
	{
		ants_a = ants / index;
		sum2 = (ants_a + (tmp->size - 1) - 1);
		if (sum1 > sum2)
			sum1 = sum2;
//		printf("%u = ants\n", ants / index);
	//	printf("%u = sum\n", sum1);
//		printf("%u = sum && size = %llu && ind = %u\n", sum1, tmp->size - 1, index);
//		printf("%llu = coups\n",(ants / index + (tmp->size - 1) - 1));
//		if (sum1 > (sum2 = (ants / index + (tmp->size - 1) - 1)))
//		{
//			sum1 = sum2;
//			res = index;
//		}
		tmp = tmp->next;
		index++;
	}
	printf("%u = sum1\n", sum1);
//	printf("%u = res\n", res);
	return (res);
}

void					ft_algorithm(t_map *map)
{
	t_stack				*list;
	uint8_t				visited[MAX_VERTICES];
	int					p;

	list = ft_allocate_stack_memory();
	ft_memset(visited, 0, MAX_VERTICES);
	while (ft_breadth_first_search(map, visited, &p) == EXIT_SUCCESS)
	{
		if (p)
			ft_push_path_to_stack(map, &list);
		ft_memset(visited, 0, MAX_VERTICES);
	}
	printf("start = %u && end = %u\n", map->start_edges, map->end_edges);
	set_last_to_null(list);
	get_optimum_path_nb(list, map->population, map->superposition);
	ft_free_stacks(&list);
}
