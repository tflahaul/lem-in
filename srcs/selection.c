/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 14:44:42 by thflahau          #+#    #+#             */
/*   Updated: 2019/06/01 16:08:11 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_list.h>
#include <lem_in_stacks.h>
#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>

#include <lem_in.h>
#include <stdio.h>

/* 				En chantier				*/
static uint8_t			ft_get_non_overlapping(t_map *map, t_listhead *head, __unused uint16_t nb)
{
	t_listhead			*ptr;
	t_listhead			*position;
	uint8_t				visited[MAX_VERTICES];

	__builtin_memset(visited, 0, MAX_VERTICES);
	ptr = head;
	while ((ptr = ptr->next) != head)
	{
		position = ft_stack_entry(ptr)->path->list.next;
		while ((position = position->next) != ft_stack_entry(ptr)->path->list.prev)
			visited[ft_queue_entry(position)->key] = visited_node;
		for (uint16_t index = 0; index < MAX_VERTICES; ++index)
			if (UNLIKELY(visited[index] == visited_node))
				printf("[%s]\n", map->hashtab[index]->name);
		__builtin_memset(visited, 0, MAX_VERTICES);
		printf("==-==-==-==-==-==-==-==-==-==-==\n");
	}
	return (EXIT_FAILURE);
}

/* 				En chantier				*/
void					ft_keep_best_paths(t_map *map, t_listhead *head)
{
	uint16_t			index;

	index = 2;
	ft_get_non_overlapping(map, head, index);
}
