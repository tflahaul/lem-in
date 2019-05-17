/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:50:32 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/17 21:18:38 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_compiler.h>
#include <lem_in_queue.h>
#include <stdlib.h>

static inline t_queue	*ft_allocate_queue_node(uint32_t key)
{
	t_queue				*node;

	if (UNLIKELY((node = (t_queue *)malloc(sizeof(t_queue))) == NULL))
		return (NULL);
	node->key = key;
	node->ant = 0;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

inline uint8_t			ft_drain_queue(t_queue **head)
{
	t_queue				*ptr;
	t_queue				*node;

	node = *head;
	while (node != NULL)
	{
		ptr = node->next;
		free((void *)node);
		node = ptr;
	}
	*head = NULL;
	return (EXIT_SUCCESS);
}

void					ft_queue_push(t_queue **head, uint32_t key)
{
	t_queue				*node;

	if (head != NULL)
	{
		if (LIKELY((node = ft_allocate_queue_node(key)) != NULL))
		{
			node->next = *head;
			if (*head != NULL)
				(*head)->prev = node;
			*head = node;
		}
	}
}

void					ft_queue_append(t_queue **head, uint32_t key)
{
	t_queue				*tmp;
	t_queue				*node;

	if (LIKELY((node = ft_allocate_queue_node(key)) != NULL))
	{
		if (*head == NULL)
			*head = node;
		else
		{
			tmp = *head;
			while (tmp->next != NULL)
				tmp = tmp->next;
			node->prev = tmp;
			tmp->next = node;
		}
	}
}

t_queue					*ft_queue_pop(t_queue **head)
{
	t_queue				*node;

	if (head == NULL || *head == NULL)
		return (NULL);
	node = (*head)->next;
	free((void *)(*head));
	if (node != NULL)
		node->prev = NULL;
	return (node);
}
