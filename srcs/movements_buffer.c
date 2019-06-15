/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 18:33:27 by thflahau          #+#    #+#             */
/*   Updated: 2019/06/15 18:39:56 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_stacks.h>
#include <lem_in_compiler.h>

static void				ft_fill_buff(t_map *map, t_listhead *head, char *buffer)
{
	char				*tmp;
	t_listhead			*new_head;
	t_listhead			*position;
	register t_queue	*ptr;
	register t_listhead	*node;

	position = head;
	while ((position = position->next) != head)
	{
		node = &(ft_stack_entry(position)->path->list);
		new_head = node;
		while ((node = node->prev) != new_head)
		{
			ptr = ft_queue_entry(node);
			if (ptr->ant > 0 && ptr->ant <= map->population
				&& ptr->key != map->start_index)
			{
				ft_strcat(buffer, " L");
				ft_strcat(buffer, (tmp = ft_itoa(ptr->ant)));
				free((void *)tmp);
				ft_strcat(buffer, "-");
				ft_strcat(buffer, map->hashtab[ptr->key]->name);
			}
		}
	}
}

static inline void		ft_print_buff(t_map *map, t_listhead *hd, uint32_t size)
{
	char				*buffer;

	if (LIKELY((buffer = ft_strnew(size)) != NULL))
	{
		ft_fill_buff(map, hd, buffer);
		if (buffer[0] != 0)
			ft_putstr_endl(buffer + 1);
		free((void *)buffer);
	}
}

void					ft_print_stack(t_map *map, t_listhead *head)
{
	t_queue				*ptr;
	t_listhead			*temp;
	t_listhead			*position;
	register uint32_t	length;

	length = 0;
	position = head;
	while ((position = position->next) != head)
	{
		temp = &(ft_stack_entry(position)->path->list);
		while ((temp = temp->prev) != ft_stack_entry(position)->path->list.next)
		{
			ptr = ft_queue_entry(temp);
			if (ptr->ant > 0 && ptr->ant <= map->population \
				&& ptr->key != map->start_index)
				length += ft_strlen(map->hashtab[ptr->key]->name) \
				+ ft_u32len(ptr->ant) + 3;
		}
	}
	ft_print_buff(map, head, length);
}
