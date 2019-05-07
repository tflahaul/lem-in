/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 16:05:49 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/07 13:55:01 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_stacks.h>

inline t_stack				*ft_stack_pop(t_stack **head)
{
	t_stack					*node;

	if (head == NULL || *head == NULL)
		return (NULL);
	node = (*head)->next;
	free((void *)(*head));
	return (node);
}

void						ft_free_stacks(t_stack **head)
{
	t_stack					*ptr;
	t_stack					*node;
	t_queue					*temp;

	if (head != NULL && *head != NULL)
	{
		node = *head;
		while (node != NULL)
		{
			ptr = node->next;
			while (node->path != NULL)
			{
				temp = node->path->next;
				free((void *)node->path);
				node->path = temp;
			}
			free((void *)node);
			node = ptr;
		}
	}
	*head = NULL;
}

static inline t_stack		*ft_allocate_stack_memory(void)
{
	t_stack					*head;

	if ((head = (t_stack *)malloc(sizeof(t_stack))) == NULL)
		return (NULL);
	ft_memset(head, 0, sizeof(t_stack));
	return (head);
}

static inline void			ft_fill_stack(t_map *map, t_stack **node)
{
	t_vertices				*path;

	path = map->hashtab[map->end_index];
	while (path != NULL)
	{
		ft_queue_push(&(*node)->path, path->key);
		path = path->prev;
		++(*node)->size;
	}
}

uint64_t					ft_push_path_to_stack(t_map *map, t_stack **stack)
{
	t_stack					*tmp;
	t_stack					*node;
	uint64_t				length;

	node = *stack;
	if ((tmp = ft_allocate_stack_memory()) == NULL)
		return (0);
	if (node == NULL)
	{
		*stack = tmp;
		ft_fill_stack(map, stack);
		length = (*stack)->size;
	}
	else
	{
		while (node->next != NULL)
			node = node->next;
		node->next = tmp;
		ft_fill_stack(map, &node->next);
		length = node->next->size;
	}
	return (length);
}
