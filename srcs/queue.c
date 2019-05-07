/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:50:32 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/07 13:55:10 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <lem_in_queue.h>

static inline t_queue			*ft_allocate_queue_node(uint32_t key)
{
	t_queue						*node;

	if ((node = (t_queue *)malloc(sizeof(t_queue))) == NULL)
		return (NULL);
	node->key = key;
	node->ant = 0;
	node->next = NULL;
	return (node);
}

inline uint8_t					ft_drain_queue(t_queue **head)
{
	t_queue						*ptr;
	t_queue						*node;

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

void							ft_queue_push(t_queue **head, uint32_t key)
{
	t_queue						*node;

	if (head != NULL)
	{
		if ((node = ft_allocate_queue_node(key)) != NULL)
		{
			node->key = key;
			node->next = *head;
			*head = node;
		}
	}
}

void							ft_queue_append(t_queue **head, uint32_t key)
{
	t_queue						*tmp;
	t_queue						*node;

	if ((node = ft_allocate_queue_node(key)) != NULL)
	{
		tmp = *head;
		if (tmp == NULL)
			*head = node;
		else
		{
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = node;
		}
	}
}

t_queue							*ft_queue_pop(t_queue **head)
{
	t_queue						*node;

	if (head == NULL || *head == NULL)
		return (NULL);
	node = (*head)->next;
	free((void *)(*head));
	return (node);
}
