/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:33:47 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/16 01:25:00 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>
#include <stdio.h>
/*
static uint32_t			ft_compute_steps(t_map *map, t_stack *ptr, uint32_t nb)
{
	uint32_t			ants;
	uint32_t			step;
	uint32_t			ratio;
	register uint16_t	index;

	step = 0;
	ratio = (double)map->population / (double)nb;
	if (nb == 1)
		return (map->population + ptr->size - 1);
	else if (LIKELY((ptr = ptr->next) != NULL))
	{
		index = 0;
		step = ratio + ptr->size - 1;
		while (++index < (uint16_t)nb && LIKELY((ptr = ptr->next) != NULL))
			step += ft_abs(step - (ratio + ptr->size - 1));
	}
	return (step);
}

static uint32_t			ft_compute_steps(t_map *map, t_stack *ptr, uint32_t nb)
{
	uint32_t			ants;
	uint32_t			diff;
	uint32_t			steps;
	uint32_t			tmpsize;

	ants = (map->population >> 1) - nb;
	tmpsize = ptr->size;
	steps = ants + ptr->size - 1;
	while ((ptr = ptr->next) != NULL)
	{
		diff = ft_abs(ptr->size - tmpsize);
		tmpsize = ptr->size;
		if (ants > diff)
			steps += ft_abs(steps - ((ants -= diff) + ptr->size + 1));
		else
			return (steps + ft_abs(steps - (ants + ptr->size + 1)));
	}
	return (steps);
}
*/

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
	return (ants);
}

uint32_t				ft_population_distribution(t_map *map, t_stack *stacks)
{
	uint32_t			diff;
	uint32_t			ants;
	uint32_t			steps;
	uint32_t			tmpsize;

//	index = 2;
//	ants = get_init_ants(map, stacks);
//	tmp = ft_compute_steps(map, stacks->next, 1);
//	while ((steps = ft_compute_steps(map, stacks->next, index++)) < tmp)
//		tmp = steps;
	tmpsize = stacks->size;
	ants = get_init_ants(map, stacks);
	steps = ants + stacks->size - 1;
	printf("%u = steps\n", steps);
	while (LIKELY((stacks = stacks->next) != NULL))
	{
		diff = stacks->size - tmpsize;
		if (diff > ants)
			steps += ft_abs(steps - ((ants -= diff) + stacks->size - 1));
		else if (ants > 0)
			return (steps + ft_abs(steps - (ants + stacks->size - 1)));
	}
	return (steps);
}
