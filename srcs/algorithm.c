/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 09:59:25 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/22 19:31:21 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_bug.h>
#include <lem_in_stacks.h>
#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>
#include <stdio.h>

static void				print_stack(t_map *map, t_listhead *head)
{
	t_stack				*node;
	t_listhead			*ptr;
	t_listhead			*position = head->next;

	while (position != head)
	{
		node = LIST_ENTRY(position, t_stack, list);
		ptr = node->path->list.next;
		printf("\n================\n");
		while (ptr != &(node->path->list))
		{
			printf("%s\n", map->hashtab[LIST_ENTRY(ptr, t_queue, list)->key]->name);
			ptr = ptr->next;
		}
		position = position->next;
	}
	ft_putchar(10);
}

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
			if (LIKELY((list = (t_queue *)malloc(sizeof(t_queue))) != NULL))
			{
				list->key = (uint32_t)vertice->key;
				ft_list_push(&(list->list), &(node->path->list));
				++node->size;
			}
			vertice = vertice->prev;
		}
		ft_list_add_tail(&(node->list), head);
	}
}

static void				ft_make_directed(t_map *map, t_listhead *head)
{
	t_stack				*ptr;
	t_edges				*tmp;
	t_listhead			*list;
	register uint32_t	hashkey;

	ptr = LIST_ENTRY(head, t_stack, list);
	list = &(ptr->path->list);
	while ((list = list->next) != ptr->path->list.prev)
	{
		hashkey = LIST_ENTRY(list->next, t_queue, list)->key;
		tmp = map->hashtab[LIST_ENTRY(list, t_queue, list)->key]->adjc;
		while (tmp->key != hashkey && LIKELY(tmp != NULL))
			tmp = tmp->next;
		tmp->way = closed_way;
	}
}

/*
**	Update 'visited' array to relabel nodes through which the BFS algorithm
**	have gone.
*/

static inline void		ft_relabel_directed_nodes(int8_t *vstd, t_stack *stack)
{
	t_listhead			*node;
	t_listhead			*position;

	ft_fast_bzero(vstd, MAX_VERTICES);
	node = &(LIST_ENTRY(stack->list.prev, t_stack, list)->path->list);
	position = node->next;
	while ((position = position->next) != node->prev)
		vstd[LIST_ENTRY(position, t_queue, list)->key] = selected_node;
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
		ft_make_directed(map, stacks.list.prev);
		ft_relabel_directed_nodes(visited, &stacks);
	}
	if (UNLIKELY(&(stacks.list) == stacks.list.next))
		return ((uint8_t)ft_printf(C_RED"lem-in: %s"C_NONE, DEADEND));
	print_stack(map, &(stacks.list));
	return (EXIT_SUCCESS); // Leaks
}
