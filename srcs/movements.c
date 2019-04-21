/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:49:35 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/19 03:29:35 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_stacks.h>
#include <lem_in_compiler.h>

uint32_t					get_steps(t_stack *list, t_map *map)
{
	uint32_t				res;
	uint32_t				index;
	uint32_t				sum1;
	uint32_t				sum2;
	t_stack					*tmp;

	sum1 = map->population + (list->size - 1) - 1;
	tmp = list;
	if (map->superposition && tmp->next)
		tmp = list->next;
	if (!list)
		return (0);
	res = 1;
	index = 1;
	while (tmp)
	{
		sum2 = (map->population / index + (tmp->size - 1) - 1);
		if (sum1 > sum2)
		{
			sum1 = sum2;
			res = index;
		}
		tmp = tmp->next;
		index++;
	}
	return (sum2);
}

static inline void			ft_print_single_ant(uint16_t nb, const char *name)
{
	ft_putchar('L');
	ft_putnbr_light(nb);
	ft_putchar('-');
	ft_putstr(name);
	ft_putchar(' ');
}

static inline void			ft_print_stack(t_map *map, t_queue *queue)
{
	while ((queue = queue->next) != NULL)
		if (queue->ant > 0 && queue->ant <= map->population)
			ft_print_single_ant(queue->ant, map->hashtab[queue->key]->name);
}

static void					ft_update_stack(t_queue *queue, uint64_t size)
{
	uint16_t				index;
	t_queue					*node;
	uint16_t				ants[size];

	index = 0;
	node = queue;
	while (node != NULL)
	{
		ants[index++] = node->ant;
		node = node->next;
	}
	index = 0;
	while ((queue = queue->next) != NULL)
		queue->ant = ants[index++];
}

static inline void			ft_init_movements(t_stack *stack)
{
	static uint64_t			ants;

	while (stack != NULL)
	{
		stack->path->ant = ++ants;
		stack = stack->next;
	}
}

void						ft_print_movements(t_map *map, void *list)
{
	uint64_t				step;
	uint32_t				length;
	t_stack					*stacks;

	step = 0;
	length = get_steps((t_stack *)list, map);
	while (step++ <= length + 1)
	{
		stacks = (t_stack *)list;
		if (map->superposition)
			stacks = stacks->next;
		ft_init_movements(stacks);
		while (stacks != NULL)
		{
			ft_print_stack(map, stacks->path);
			ft_update_stack(stacks->path, stacks->size);
			stacks = stacks->next;
		}
		ft_putchar('\n');
	}
}
