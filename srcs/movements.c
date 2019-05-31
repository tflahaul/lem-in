/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:49:35 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/31 16:18:18 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_stacks.h>
#include <lem_in_compiler.h>

static void					ft_fill_buffer(t_map *map, t_listhead *head,
											char *buffer)
{
	char					*tmp;
	register t_queue		*ptr;
	register t_listhead		*node;
	t_listhead				*new_head;
	t_listhead				*position;

	position = head;
	while ((position = position->next) != head)
	{
		node = &(ft_stack_entry(position)->path->list);
		new_head = node;
		while ((node = node->next) != new_head)
		{
			ptr = ft_queue_entry(node);
			if (ptr->ant > 0 && ptr->ant <= map->population
				&& ptr->key != map->start_index)
			{
				ft_strcat(buffer, " ");
				ft_strcat(buffer, "L");
				ft_strcat(buffer, (tmp = ft_itoa(ptr->ant)));
				free((void *)tmp);
				ft_strcat(buffer, "-");
				ft_strcat(buffer, map->hashtab[ptr->key]->name);
			}
		}
	}
}

static void					ft_print_stack(t_map *map, t_listhead *head)
{
	char					*buffer;
	t_queue					*node;
	t_listhead				*temp;
	t_listhead				*position;
	register uint32_t		length;

	length = 0;
	position = head;
	while ((position = position->next) != head)
	{
		temp = &(ft_stack_entry(position)->path->list);
		while ((temp = temp->prev) != ft_stack_entry(position)->path->list.next)
		{
			node = ft_queue_entry(temp);
			if (node->ant > 0 && node->ant <= map->population
				&& node->key != map->start_index)
				length += ft_strlen(map->hashtab[node->key]->name) + \
					ft_u32len(node->ant) + 3;
		}
	}
	if (LIKELY((buffer = ft_strnew(length)) != NULL))
	{
		ft_fill_buffer(map, head, buffer);
		if (LIKELY(buffer[0]))
			ft_putstr_endl(buffer + 1);
		free((void *)buffer);
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

	ft_putchar('\n');
	length = ft_stack_entry(head)->ant + ft_stack_entry(head->next)->size + 1;
	while (length-- > 0)
	{
		position = head;
		ft_init_movements(head);
		ft_print_stack(map, head);
		while ((position = position->next) != head)
		{
			stacks = ft_stack_entry(position);
			ft_update_stack(&(stacks->path->list), stacks->size);
		}
	}
}
