/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 09:59:25 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/24 13:06:52 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_bug.h>
#include <lem_in_stacks.h>
#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>
#include <stdio.h>
/*
void					print_hash(t_map *map)
{
	for (register uint16_t index = 0; index < MAX_VERTICES; ++index)
	{
		if (map->hashtab[index]->name != NULL)
		{
			printf("%s", map->hashtab[index]->name);
			for (t_edges *ptr = map->hashtab[index]->adjc; ptr; (ptr = ptr->next))
				printf(" -> %s(%i)", map->hashtab[ptr->key]->name, ptr->way);
			printf("\n");
		}
	}
}

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
*/
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

static void				ft_open_path(t_map *map, uint32_t prevkey, uint32_t key)
{
	register t_edges	*node;

	node = map->hashtab[prevkey]->adjc;
	while (node != NULL)
	{
		if (node->key == key)
		{
			node->way = open_way;
			break ;
		}
		node = node->next;
	}
	node = map->hashtab[key]->adjc;
	while (node != NULL)
	{
		if (node->key == prevkey)
		{
			node->way = open_way;
			break ;
		}
		node = node->next;
	}
}

static uint8_t			ft_overlaps(t_map *map, uint32_t prevkey, uint32_t key)
{
	t_edges				*ptr;
	t_edges				*node;

	node = map->hashtab[prevkey]->adjc;
	while (node != NULL)
	{
		if (node->key == key && node->way == closed_way)
		{
			ptr = map->hashtab[key]->adjc;
			while (ptr != NULL)
			{
				if (ptr->key == prevkey && ptr->way == closed_way)
					return (EXIT_SUCCESS);
				ptr = ptr->next;
			}
		}
		node = node->next;
	}
	return (EXIT_FAILURE);
}

/*
**	Nettoie toutes les connexions du graph, sauf celles pour lesquelles deux
**	chemins se superposent.
*/

static inline void		ft_update_graph(t_map *map, t_listhead *head)
{
	uint32_t			hashkey;
	t_queue				*list;
	t_listhead			*node_head;
	t_listhead			*node;
	t_listhead			*ptr;

	ptr = head;
	while ((ptr = ptr->next) != head)
	{
		node_head = &(LIST_ENTRY(ptr, t_stack, list)->path->list);
		hashkey = LIST_ENTRY(node_head->next, t_queue, list)->key;
		node = node_head;
		while ((node = node->next) != node_head)
		{
			list = LIST_ENTRY(node, t_queue, list);
			if (LIKELY(ft_overlaps(map, hashkey, list->key) == EXIT_FAILURE))
				ft_open_path(map, hashkey, list->key);
			hashkey = list->key;
		}
	}
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

static void				ft_free_stacks(t_listhead *head)
{
	t_listhead			*node;
	t_listhead			*next;

	node = head->next;
	while (node != head)
	{
		next = node->next;
		ft_list_del(&(LIST_ENTRY(node, t_stack, list)->path->list));
		free((void *)LIST_ENTRY(node, t_stack, list)->path);
		free((void *)LIST_ENTRY(node, t_stack, list));
		node = next;
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
	ft_update_graph(map, &(stacks.list));
	if (UNLIKELY(&(stacks.list) == stacks.list.next))
		return (ft_puterror(DEADEND));
//	print_stack(map, &(stacks.list));
	ft_free_stacks(&(stacks.list));
	return (EXIT_SUCCESS);
}
