/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 16:05:49 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/22 10:44:10 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_stacks.h>

inline t_stack				*ft_allocate_stack_memory(void)
{
	t_stack					*head;

	if ((head = (t_stack *)malloc(sizeof(t_stack))) == NULL)
		return (NULL);
	ft_memset(head, 0, sizeof(t_stack));
	return (head);
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
}

void						set_last_to_null(t_stack *stack)
{
	t_stack					*tmp;
	t_stack					*tmp_free;

	if (!stack)
		return ;
	tmp = stack;
	if (!tmp->next)
	{
		tmp_free = tmp;
		tmp = NULL;
		free(tmp_free);
	}
	while (tmp->next->size != 0)
		tmp = tmp->next;
	tmp_free = tmp->next;
	tmp->next = NULL;
	free(tmp_free);
}

uint8_t						ft_push_path_to_stack(t_map *map, t_stack **stack)
{
	t_stack					*node;
	t_vertices				*paths;

	node = *stack;
	while (node != NULL && node->path != NULL)
		node = node->next;
	paths = map->hashtab[map->end_index];
	while (paths != NULL)
	{
		ft_queue_push(&node->path, paths->key);
		node->size++;
		paths = paths->prev;
	}
	if ((node->next = ft_allocate_stack_memory()) == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
