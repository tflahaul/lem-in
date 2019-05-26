/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 09:59:25 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/26 13:38:15 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_bug.h>
#include <lem_in_stacks.h>
#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>
/*
#include <stdio.h>

static void				print_stack(t_map *map, t_listhead *head)
{
	t_stack				*node;
	t_listhead			*ptr;
	t_listhead			*position = head->next;

	while (position != head)
	{
		node = ft_stack_entry(position);
		ptr = node->path->list.next;
		printf("\n================\n");
		while (ptr != &(node->path->list))
		{
			printf("%s\n", map->hashtab[ft_queue_entry(ptr)->key]->name);
			ptr = ptr->next;
		}
		position = position->next;
	}
	ft_putchar(10);
}
*/
static void				ft_join_paths(t_map *map, t_listhead *head)
{
	t_queue				*list;
	t_stack				*node;
	t_vertices			*vertice;

	if (LIKELY((node = (t_stack *)malloc(sizeof(t_stack))) != NULL))
	{
		node->ant = 0;
		node->size = 0;
		if (LIKELY((node->path = (t_queue *)malloc(sizeof(t_queue))) != NULL))
			ft_list_init_head(&(node->path->list));
		vertice = map->hashtab[map->end_index];
		while (vertice != NULL)
		{
			if (LIKELY((list = ft_queue_node((uint32_t)vertice->key)) != NULL))
			{
				ft_list_push(&(list->list), &(node->path->list));
				++node->size;
			}
			vertice = vertice->prev;
		}
		ft_list_add_tail(&(node->list), head);
	}
}

uint8_t					ft_algorithm(t_map *map)
{
	t_stack				stacks;
	int8_t				visited[MAX_VERTICES];

	ft_list_init_head(&(stacks.list));
	ft_fast_bzero(visited, MAX_VERTICES);
	while (ft_breadth_first_search(map, visited) == EXIT_SUCCESS)
	{
		ft_join_paths(map, &(stacks.list));
		ft_fast_bzero(visited, MAX_VERTICES);
		ft_make_directed(map, stacks.list.prev);
	}
	if (UNLIKELY(&(stacks.list) == stacks.list.next))
		return (ft_puterror(DEADEND));
//	print_stack(map, &(stacks.list));
	ft_free_stacks(&(stacks.list));
	return (EXIT_SUCCESS);
}
