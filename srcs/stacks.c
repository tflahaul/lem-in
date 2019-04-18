/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 16:05:49 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/18 16:28:14 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_stacks.h>

t_stack						*ft_allocate_stack_memory(t_stack *head)
{
	if ((head = (t_stack *)malloc(sizeof(t_stack))) == NULL)
		return (NULL);
	head->path = NULL;
	head->next = NULL;
	return (head);
}

uint8_t						ft_add_path_to_stack(t_map *map, t_stack **stack)
{
	t_stack					*node;
	t_vertices				*paths;

	node = *stack;
	while (node != NULL && node->path != NULL)
		node = node->next;
	paths = map->hashtab[map->end_index];
	while (paths != NULL)
	{
		paths = paths->prev;
	}
	return (EXIT_SUCCESS);
}

int							main(void)
{
	t_stack					*ptr;

	ptr = ft_allocate_stack_memory(ptr);
	return (0);
}
