/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 16:05:49 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/19 23:14:12 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_stacks.h>
#include <lem_in_compiler.h>

inline t_stack				*ft_stack_pop(t_stack **head)
{
	t_stack					*node;

	if (head == NULL || *head == NULL)
		return (NULL);
	node = (*head)->next;
	ft_drain_queue(&(*head)->path);
	free((void *)(*head));
	return (node);
}

uint8_t						ft_free_stacks(t_stack **head)
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
	return (EXIT_SUCCESS);
}

static inline t_stack		*ft_allocate_stack_memory(void)
{
	t_stack					*head;

	if (UNLIKELY((head = (t_stack *)malloc(sizeof(t_stack))) == NULL))
		return (NULL);
	ft_memset(head, 0, sizeof(t_stack));
	return (head);
}
#include <stdio.h>

static inline void			ft_fill_stack(t_map *map, t_stack **node)
{
	t_vertices				*path;
	t_vertices				*tmp;

	path = map->hashtab[map->end_index];
	while (path != NULL)
	{
		tmp = path;
//		printf("prev list = %s\n", map->hashtab[path->key]->name);
		ft_queue_push(&(*node)->path, path->key);
		if (path->key != map->start_index)
			++(*node)->size;
		path = path->prev;
	//	tmp->prev = NULL;
	}
}

uint32_t					ft_push_path_to_stack(t_map *map, t_stack **stack)
{
	t_stack					*tmp;
	t_stack					*node;

	node = *stack;
	if (UNLIKELY((tmp = ft_allocate_stack_memory()) == NULL))
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
		if (UNLIKELY(ft_path_checker(map, tmp->path) == EXIT_FAILURE))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
