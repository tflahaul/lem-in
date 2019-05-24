/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_manipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:35:33 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/24 17:54:24 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_stacks.h>
#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>

void					ft_make_directed(t_map *map, t_listhead *head)
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
**	Makes all directed edges undirected, unless an overlap is found.
*/

inline void				ft_update_graph(t_map *map, t_listhead *head)
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
