/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:33:47 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/08 16:37:42 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>

static uint64_t			ft_get_total_size(t_stack *stacks, uint32_t nb)
{
	uint64_t			size;

	size = 0;
	while (nb-- && LIKELY(stacks != NULL))
	{
		size += stacks->size - 1;
		stacks = stacks->next;
	}
	return (size);
}

static inline uint64_t	ft_magic_ratio(t_map *map, t_stack *p, uint64_t size)
{
	double				ratio;

	ratio = (double)p->size / (double)size;
	return ((map->population * (double)(1 - ratio)) + p->size - 1);
}

static int64_t			ft_compute_steps(t_map *map, t_stack *ptr, uint32_t nb)
{
	int64_t				steps;
	uint64_t			size;
	register uint16_t	index;

	steps = 0;
	if (nb == 1)
		return (map->population + ptr->size - 1);
	else if (LIKELY((ptr = ptr->next) != NULL))
	{
		index = 0;
		size = ft_get_total_size(ptr, nb);
		steps = ft_magic_ratio(map, ptr, size);
		while (++index < (uint16_t)nb && LIKELY((ptr = ptr->next) != NULL))
			steps += ABS(steps - ft_magic_ratio(map, ptr, size));
	}
	return (steps);
}

uint16_t				ft_population_distribution(t_map *map, t_stack *stacks)
{
	int64_t				steps;
	register uint16_t	index;

	index = 2;
	steps = ft_compute_steps(map, stacks, 1);
	printf("steps = %lld\n", steps);
	while (index <= map->start_edges)
	{
		steps = ft_compute_steps(map, stacks, index);
		printf("steps = %lld\n", steps);
		index++;
	}
	return (index - 1);
}
