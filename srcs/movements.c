/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:49:35 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/31 12:36:20 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_stacks.h>
#include <lem_in_compiler.h>

static inline void			ft_print_single_ant(uint16_t nb, char const *name)
{
	ft_putchar('L');
	ft_putnbr_light(nb);
	ft_putchar('-');
	ft_putstr(name);
	ft_putchar(' ');
}

static inline void			ft_print_stack(t_map *map, t_listhead *head)
{
	t_queue					*node;
	t_listhead				*position;

	position = head;
	if (UNLIKELY(map->visual >= COLORS))
	{
		while ((position = position->prev) != head->next)
		{
			node = ft_queue_entry(position);
			if (node->ant <= map->population)
				ft_print_colored_ant(node->ant | map->visual, \
					map->hashtab[node->key]->name);
		}
	}
	else
	{
		while ((position = position->prev) != head->next)
		{
			node = ft_queue_entry(position);
			if (node->ant > 0 && node->ant <= map->population)
				ft_print_single_ant(node->ant, map->hashtab[node->key]->name);
		}
	}
}

/*
**	Sends values of each 'queue' element one rung lower to mime
**	movements of ants through each room.
*/

static void					ft_update_stack(t_listhead *head, uint64_t size)
{
	register uint16_t		index;
	t_listhead				*node;
	uint16_t				ants[size];

	index = 0;
	node = head;
	while ((node = node->next) != head && index < size)
		ants[index++] = ft_queue_entry(node)->ant;
	index = 0;
	node = head->next;
	while ((node = node->next) != head->next)
		ft_queue_entry(node)->ant = ants[index++];
}

/*
**	Attributes one ant on top of each stack/path. A static variable
**	is used to keep track of the last ant sent.
*/

static inline void			ft_init_movements(t_stack *stacks)
{
	t_listhead				*position;
	t_stack					*node;
	static uint64_t			ant;

	position = &(stacks->list);
	while ((position = position->next) != &(stacks->list))
	{
		node = ft_stack_entry(position);
		node->path->ant = ++ant;
	}
}

void						ft_print_movements(t_map *map, t_stack *list)
{
	uint32_t				length;
	t_stack					*stacks;
	t_listhead				*position;

	length = ft_stack_entry(list->list.next)->ant + ft_stack_entry(list->list.next)->size - 1;
	while (length-- > 0)
	{
		ft_init_movements(list);
		position = &(list->list);
		while ((position = position->next) != &(list->list))
		{
			stacks = ft_stack_entry(position);
			ft_print_stack(map, &(stacks->path->list));
			ft_update_stack(&(stacks->path->list), stacks->size);
		}
		ft_putchar('\n');
	}
}
