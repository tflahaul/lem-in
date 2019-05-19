/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:49:35 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/19 19:25:03 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_stacks.h>
#include <lem_in_compiler.h>
#include <string.h>

static inline void			ft_print_single_ant(uint16_t nb, char const *name)
{
	ft_putchar('L');
	ft_putnbr_light(nb);
	ft_putchar('-');
	ft_putstr(name);
	ft_putchar(' ');
}

/*
**	Go créer un buffer, le trim et l'afficher.
*/

char						*ft_make_buffer(char *buffer, char const *ant)
{
	char					*ptr;

	ptr = buffer;
	while (*buffer)
		buffer++;
	*buffer = ' ';
	strcpy(buffer, ant);
	return (ptr);
}

static inline void			ft_print_stack(t_map *map, t_queue *queue)
{
	uint32_t				tmp;

	while (queue != NULL && queue->key != map->start_index)
	{
		if (queue->ant && queue->ant <= map->population)
		{
			if (map->visual >= COLORS)
			{
				tmp = (queue->ant | map->visual);
				ft_print_colored_ant(tmp, map->hashtab[queue->key]->name);
			}
			else
				ft_print_single_ant(queue->ant, map->hashtab[queue->key]->name);
		}
		queue = queue->prev;
	}
}

/*
**	Sends values of each 'queue' element one rung lower to mime
**	movements of ants through each room.
*/

static void					ft_update_stack(t_queue *queue, uint64_t size)
{
	uint16_t				index;
	t_queue					*node;
	uint16_t				ants[size];

	index = 0;
	node = queue;
	while (node != NULL && index < size)
	{
		ants[index++] = node->ant;
		node = node->next;
	}
	index = 0;
	while ((queue = queue->next) != NULL)
		queue->ant = ants[index++];
}

/*
**	Attributes one ant on top of each stack/path. A Static variable
**	is used to keep track of the last ant sent.
*/

static inline void			ft_init_movements(t_stack *stack)
{
	static uint64_t			ant;

	while (stack != NULL)
	{
		if (stack->ant > 0)
		{
			stack->ant = stack->ant - 1;
			stack->path->ant = ++ant;
		}
		else
			stack->path->ant = 0;
		stack = stack->next;
	}
}

/*
** Function used to display ants' movements
*/

void						ft_print_movements(t_map *map, t_stack *list)
{
	uint32_t				length;
	t_stack					*stacks;

	length = list->ant + list->size;
	while (length-- > 0)
	{
		stacks = list;
		ft_init_movements(stacks);
		while (stacks != NULL)
		{
			ft_print_stack(map, list_last_node(stacks->path));
			ft_update_stack(stacks->path, stacks->size);
			stacks = stacks->next;
		}
		ft_putchar('\n');
	}
}
