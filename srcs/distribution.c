/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:33:47 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/14 12:44:37 by thflahau         ###   ########.fr       */
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

static uint32_t			ft_compute_steps(t_map *map, t_stack *ptr, uint32_t nb)
{
	uint32_t			ants;
	uint32_t			steps;
	register uint32_t	tmpsize;

	ants = (map->population >> 1);
	if (LIKELY(ants > nb))
	{
		tmpsize = ptr->size;
		steps = (ants -= nb) + ptr->size - 1;
		while ((ptr = ptr->next) != NULL && ants > 0)
		{
			if (ants > (ptr->size - tmpsize))
			{
				ants = ants - (ptr->size - tmpsize);
				steps += ft_abs(steps - (ants + ptr->size - 1));
				tmpsize = ptr->size;
			}
			else
				return (steps + ft_abs(steps - (ants + ptr->size - 1)));
		}
	}
	return (0);
}

uint16_t				ft_population_distribution(t_map *map, t_stack *stacks)
{
//	uint32_t			tmp;
	uint32_t			steps;
	register uint16_t	index;

	if (map->population == 1)
		return (1);
	index = 2;
	steps = ft_compute_steps(map, stacks, 1);
	while (index < ft_list_size(stacks) * 10)
	{
		steps = ft_compute_steps(map, stacks->next, index++);
		printf("steps = %u\n", steps);
	}
	return (0xf);
}
