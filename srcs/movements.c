/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:49:35 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/31 14:43:27 by thflahau         ###   ########.fr       */
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
	while ((position = position->prev) != head->next)
	{
		node = ft_queue_entry(position);
		if (node->ant > 0 && node->ant <= map->population)
			ft_print_single_ant(node->ant, map->hashtab[node->key]->name);
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

static inline void			ft_init_movements(t_listhead *head)
{
	t_listhead				*position;
	t_stack					*node;
	static uint64_t			ant;

	position = head;
	while ((position = position->next) != head)
	{
		node = ft_stack_entry(position);
		if (node->ant > 0)
		{
			ft_queue_entry(node->path->list.next)->ant = ++ant;
			node->ant = node->ant - 1;
		}
		else
			ft_queue_entry(node->path->list.next)->ant = 0;
	}
}

void						ft_print_movements(t_map *map, t_listhead *head)
{
	int32_t					length;
	t_stack					*stacks;
	t_listhead				*position;

	length = ft_stack_entry(head)->ant + ft_stack_entry(head->next)->size + 1;
	while (length-- > 0)
	{
		position = head;
		ft_init_movements(head);
		while ((position = position->next) != head)
		{
			stacks = ft_stack_entry(position);
			ft_print_stack(map, &(stacks->path->list));
			ft_update_stack(&(stacks->path->list), stacks->size);
		}
		ft_putchar('\n');
	}
}
