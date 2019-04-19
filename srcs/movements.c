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

static inline void		ft_print_single_ant(uint16_t nb, const char *name)
{
	ft_putchar('L');
	ft_putnbr_light(nb);
	ft_putchar('-');
	ft_putstr(name);
	ft_putchar(' ');
}

static inline void		ft_print_stack(t_map *map, t_queue *queue)
{
	while ((queue = queue->next) != NULL)
		if (queue->ant && queue->ant <= map->population)
			ft_print_single_ant(queue->ant, map->hashtab[queue->key]->name);
}

static inline void		ft_update_stack(t_queue *queue, uint64_t size)
{
	uint16_t			index;

	index = 0;
	while (queue != NULL && index++ <= size)
	{
		queue->ant = queue->ant + 1;
		queue = queue->next;
	}
}

void					ft_print_movements(t_map *map, void *list, uint16_t nb)
{
	uint64_t			ant;
	t_stack				*stacks;

	ant = 0;
	while (ant++ <= map->population + nb)
	{
		stacks = (t_stack *)list;
		while (stacks->next != NULL)
		{
			ft_print_stack(map, stacks->path);
			ft_update_stack(stacks->path, ant);
			stacks = stacks->next;
		}
		ft_putchar('\n');
	}
}
