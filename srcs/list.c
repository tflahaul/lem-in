/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 13:36:02 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/21 15:53:00 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_list.h>
#include <lem_in_queue.h>
#include <lem_in_compiler.h>
#include <stdlib.h>

/*
**	These are easy-to-use, highly portable functions for manipulating
**	circularly-linked list. This implementation comes from the Linux
**	kernel source tree, file `include/linux/list.h`
*/

inline void				ft_list_head_init(t_listhead *head)
{
	head->next = head;
	head->prev = head;
}

/*
**	Insert a new entry between two known consecutive entries (prev & next).
**	This is only for internal list manipulation where we know the `prev`
**	and `next` pointers.
*/

inline void				ft_list_add(t_listhead *node,
									t_listhead *prev,
									t_listhead *next)
{
	if (LIKELY(node != NULL && prev != NULL && next != NULL))
	{
		next->prev = node;
		node->next = next;
		node->prev = prev;
		prev->next = node;
	}
}

/*
**	Insert a new entry AFTER the specified head. This is good for
**	implementing stacks.
*/

inline void				ft_list_push(t_listhead *node, t_listhead *head)
{
	ft_list_add(node, head, head->next);
}

/*
**	Insert a new entry BEFORE the specified head. This is good for
**	implementing queues.
*/

inline void				ft_list_add_tail(t_listhead *node, t_listhead *head)
{
	ft_list_add(node, head->prev, head);
}

inline void				ft_list_pop(t_listhead *node)
{
	if (LIKELY(node != NULL))
	{
		node->next->prev = node->prev;
		node->prev->next = node->next;
		free((void *)LIST_ENTRY(node, t_queue, list));
	}
}

// void				ft_list_del(t_listhead *head)
// {
// 	t_list			*ptr;
// 	t_listhead		*node;
// 	t_listhead		*next;

// 	node = head->next;
// 	next = node->next;
// 	while (node != head)
// 	{
// 		if ((ptr = LIST_ENTRY(node, t_list, list)) != NULL)
// 			free((void *)ptr);
// 		node = next;
// 		next = node->next;
// 	}
// }
