/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:33:47 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/20 19:14:46 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>

int					func2(int pop, int diff, int paths)
{
	return ((pop + diff) / paths + 1);
}

int					nbr_optimum_paths(t_map *map, t_stack *stacks, int *path)
{
	int				size;
	int				sum;
	int				var;
	int				diff;
	t_stack			*tmp;

	diff = 0;
	var = map->population;
	size = stacks->size;
	tmp = stacks->next;
	while ((tmp = tmp->next) != NULL)
	{
		diff += tmp->size - size;
		sum = func2(map->population, diff, ++(*path));
		if (sum > var)
		{
			stacks->next->ant = var;
			return ((*path -= 1));
		}
		var = sum;
	}
	stacks->next->ant = var;
	if (*path == 2 && var == sum)
		stacks->next->ant -= 1;
	return (*path);
}

void				ants_sup(int population, int sum, t_stack *stacks)
{
	int				diff;
	t_stack			*tmp;

	while (sum > population)
	{
		tmp = stacks;
		while (tmp->next != NULL && tmp->next->ant > 0)
			tmp = tmp->next;
		diff = sum - population;
		if (((int)tmp->ant - diff) < 0)
		{
			sum -= tmp->ant;
			diff = ft_abs(tmp->ant - diff);
			tmp->ant = 0;
		}
		else
		{
			tmp->ant -= diff;
			sum -= diff;
		}
	}
	return ;
}

void				ants_to_path(uint32_t ants, int *sum, int pop, t_stack *ptr)
{
	int				tmp;
	t_stack			*lst;

	tmp = ants;
	lst = ptr;
	lst->ant = ants;
	while ((lst = lst->next) != NULL && tmp > 0 && *sum <= pop)
	{
		if ((tmp = ants - (lst->size - ptr->size)) > 0)
		{
			if (ptr->next == lst && lst->size == ptr->size && pop % 2)
				tmp -= 1;
			lst->ant = tmp;
			*sum += tmp;
		}
	}
}
#include <stdio.h>
void				ft_population_distribution(t_map *map, t_stack *stacks)
{
	int				sum;
	uint32_t		ants;

	ants = stacks->ant;
	sum = ants;
	if (stacks->next != NULL)
	{
		ants_to_path(ants, &sum, map->population, stacks);
		ants_sup(map->population, sum, stacks);
	}
	else
		stacks->ant = map->population;
	if (!!(map->visual & VISUAL))
		write_paths_to_file(map, stacks);
	printf("#%llu = steps\n", stacks->ant + stacks->size - 1);
}
