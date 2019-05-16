/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:33:47 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/16 17:39:16 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>
#include <stdio.h>

double					func(int ants, int paths, int path_len)
{
	return ((double)ants / (double)paths + (path_len - 1));
}

int						nbr_optimum_paths(t_map *map, t_stack *stacks)
{
	double				a;
	double				b;
	int					cnt;
	int					paths;
	uint64_t			prev;
	t_stack				*tmp;

	if (UNLIKELY(map->population == 1))
		return (1);
	tmp = stacks->next;
	paths = 1;
	cnt = 0;
	a = func(map->population, paths, stacks->size);
	prev = stacks->size;
	while ((tmp = tmp->next) != NULL)
	{
		if (prev != tmp->size)
		{
			b = func(map->population, ++paths, tmp->size);
			if (a < b)
				return (paths + cnt);
			a = b;
		}
		else
			cnt++;
		prev = tmp->size;
	}
	return (paths + cnt);
}

int						get_init_ants(t_map *map, t_stack *stacks)
{
	t_stack				*tmp;
	int					total;
	int					size;
	int					ants;
	int					idx;

	total = 0;
	tmp = stacks;
	idx = 1;
	size = stacks->size;
	while ((tmp = tmp->next) != NULL)
	{
		total += tmp->size - size;
		idx++;
	}
	ants = (map->population + total) / idx;
	if (map->population % 2)
		ants += 1;
	if (map->visual != 0)
		append_to_file(DATA, ft_itoa(ants));
	return (ants);
}

uint32_t				ft_population_distribution(t_map *map, t_stack *stacks)
{
	uint32_t			ants;
	int					sum;
	uint32_t			tmpant;
	uint32_t			steps;
	t_stack				*tmp;

	sum = 0;
	printf("%u = pop\n", map->population);
//got to next path = path->ant = ants - diff size and init size
	tmp = stacks;
	ants = get_init_ants(map, stacks);
	tmpant = map->population - ants;
	steps = ants + tmp->size - 1;
	printf("%d = ant\n", ants);
	printf("%u = steps\n", steps);
	printf("%llu = tmp->size\n", tmp->size);
	tmp->ant = ants;
	while ((tmp = tmp->next) != NULL && tmpant > 0)
	{
		tmp->ant = ants - (tmp->size - stacks->size);
//		if (tmp->size == stacks->size && tmp == stacks->next && map->population % 2)
//			tmp->ant -= 1;
		printf("%d = tmpant\n", tmpant);
//		if (tmpant - tmp->ant <= 0)
//		{
//			printf("%d = tmpant\n", tmpant);
//			tmp->ant = tmpant;
//		}
		printf("%d = ant\n", tmp->ant);
		printf("%llu = tmp->size\n", tmp->size);
//		tmpant -= tmp->ant;			
	}
	if (tmp)
		printf("%llu = tmp->size\n", tmp->size);
	tmp = stacks;
	while (tmp && tmp->size > 0)
	{
//		printf("%d = ant\n", tmp->ant);
		sum += tmp->ant;
		tmp = tmp->next;
	}
	printf("%d = sum\n", sum);
	steps = ants + stacks->size - 1;
	printf("%u = steps\n", steps);
	return (1);
}
