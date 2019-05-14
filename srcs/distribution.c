/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:33:47 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/14 19:17:52 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>

static inline uint64_t	ft_abs(int64_t nb)
{
	return ((nb < 0) ? -nb : nb);
}

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
*/

static inline double	func(int ants, int paths, int path_len)
{
	return ((double)ants / (double)paths + (path_len - 1));
}

int						nbr_optimum_paths(t_map *map, t_stack *stacks)
{
	float a;
	float b;
	int paths;
	t_stack *tmp;

	if (UNLIKELY(map->population == 1))
		return (1);
    tmp = stacks;
    paths = 1;
    a = func(map->population, paths, tmp->size);
    while ((tmp=tmp->next) != NULL)
    {
        b = func(map->population, ++paths, tmp->size);
        if (a < b)
            return (paths - 1);
        a = b;
    }
    return (paths - 1);
}

static uint32_t			ft_compute_steps(t_map *map, t_stack *ptr, uint32_t nb)
{
	uint32_t			ants;
	uint32_t			diff;
	uint32_t			steps;
	uint32_t			tmpsize;

	ants = ((double)map->population / (double)nb);
	tmpsize = ptr->size;
	steps = ants + ptr->size - 1;
	while ((ptr = ptr->next) != NULL)
	{
		diff = ft_abs(ptr->size - tmpsize);
		tmpsize = ptr->size;
		if (ants > diff)
			steps += ft_abs(steps - ((ants - diff) + ptr->size + 1));
		else
			return (steps + ft_abs(steps - (ants + ptr->size + 1)));
	}
	return (steps);
}

uint16_t				ft_population_distribution(t_map *map, t_stack *stacks)
{
	uint32_t			tmp;
	uint32_t			steps;
	register uint16_t	index;

	index = 2;
	tmp = ft_compute_steps(map, stacks->next, 1);
	while ((steps = ft_compute_steps(map, stacks->next, index++)) < tmp)
		tmp = steps;
	printf("steps = %u\n", steps);
	return (steps);
}
