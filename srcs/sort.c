/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 13:55:46 by thflahau          #+#    #+#             */
/*   Updated: 2019/06/05 10:17:32 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_list.h>
#include <lem_in_stacks.h>

static inline uint8_t	ft_size_cmp(t_listhead *prev, t_listhead *next)
{
	return (ft_stack_entry(prev)->size > ft_stack_entry(next)->size);
}

static void				ft_list_swap(t_listhead *head, t_listhead *prev,
									t_listhead *next)
{
	t_listhead			*node;

	node = prev->next;
	prev->next = next->next;
	next->next = node;
	if (prev->next != head)
		prev->next->prev = prev;
	if (next->next != head)
		next->next->prev = next;
	node = prev->prev;
	prev->prev = next->prev;
	next->prev = node;
	if (prev->prev != head)
		prev->prev->next = prev;
	next->prev->next = next;
}

/*
**	This function does a bubble sort on the given list (sorting nodes by
**	their `size` element). Sorting time is O(n^2) on average which is
**	wayyy too slow and should be changed in the future.
*/

void					ft_sort_stacks(t_listhead *head)
{
	t_listhead			*position;

	position = head;
	while ((position = position->next) != head)
	{
		if (position->next != head && ft_size_cmp(position, position->next))
		{
			ft_list_swap(head, position, position->next);
			position = head;
		}
	}
}
