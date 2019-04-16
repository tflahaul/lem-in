/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:50:32 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/16 15:19:11 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_queue.h>

static inline t_queue			*ft_allocate_queue_node(uint64_t key)
{
	t_queue						*node;

	if ((node = (t_queue *)malloc(sizeof(t_queue))) == NULL)
		return (NULL);
	node->key = key;
	node->next = NULL;
	return (node);
}

void							ft_queue_push(t_queue **head, uint64_t key)
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

/*
**	Libère l'élément au sommet de la stack et retourne l'adresse du
**	nouveau sommet.
*/

t_queue							*ft_queue_pop(t_queue **queue)
{
	t_queue						*node;

	if (queue == NULL || *queue == NULL)
		return (NULL);
	node = (*queue)->next;
	free((void *)*queue);
	return (node);
}
