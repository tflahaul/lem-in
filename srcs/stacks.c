/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 16:05:49 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/23 13:24:07 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_stacks.h>

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

uint8_t						ft_push_path_to_stack(t_map *map, t_stack **stack)
{
	t_stack					*tmp;
	t_stack					*node;

	node = *stack;
	if ((tmp = ft_allocate_stack_memory()) == NULL)
		return (EXIT_FAILURE);
	if (node == NULL)
	{
		*stack = tmp;
		ft_fill_stack(map, stack);
	}
	else
	{
		while (node->next != NULL)
			node = node->next;
		node->next = tmp;
		ft_fill_stack(map, &node->next);
	}
	return (EXIT_SUCCESS);
}
