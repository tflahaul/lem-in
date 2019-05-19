/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_manipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 14:37:21 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/19 15:10:01 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>

static void				ft_open_path(t_map *map, uint32_t prevkey, uint32_t key)
{
	t_edges				*node;

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
		if (node->key == key && node->way != open_way)
		{
			ptr = map->hashtab[key]->adjc;
			while (ptr != NULL)
			{
				if (ptr->key == prevkey && ptr->way != open_way)
					return (EXIT_SUCCESS);
				ptr = ptr->next;
			}
		}
		node = node->next;
	}
	return (EXIT_FAILURE);
}

/*
**	Makes all directed edges undirected, unless an overlap is found.
*/

inline void				ft_update_graph(t_map *map, t_stack *list)
{
	t_queue				*node;
	register uint32_t	hashkey;

	while (list != NULL)
	{
		node = list->path;
		hashkey = node->key;
		while ((node = node->next) != NULL)
		{
			if (LIKELY(ft_overlaps(map, hashkey, node->key) == EXIT_FAILURE))
				ft_open_path(map, hashkey, node->key);
			hashkey = node->key;
		}
		list = list->next;
	}
}

void					ft_make_directed(t_map *map, t_stack *stack)
{
	register uint32_t	key;
	t_queue				*node;
	t_edges				*list;

	while (stack->next != NULL)
		stack = stack->next;
	node = stack->path;
	while (node->next != NULL)
	{
		key = node->next->key;
		list = map->hashtab[node->key]->adjc;
		while (LIKELY(list != NULL) && list->key != key)
			list = list->next;
		if (LIKELY(list != NULL))
			list->way = closed_way;
		node = node->next;
	}
}
