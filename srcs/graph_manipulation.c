/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_manipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 14:37:21 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/17 22:47:10 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>

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
** Makes all directed edges undirected, unless an overlap is found.
*/

inline void				ft_update_graph(t_map *map, t_stack *list)
{
	t_queue				*node;
	uint32_t			hashkey;

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

inline void				ft_update_visited_array(t_stack *stacks, uint8_t *vstd)
{
	t_queue				*node;

	ft_fast_bzero(vstd, MAX_VERTICES);
	while (stacks != NULL)
	{
		node = stacks->path;
		while ((node = node->next) != NULL)
			vstd[node->key] = selected_way;
		stacks = stacks->next;
	}
}
#include <stdio.h>
void					ft_make_directed(t_map *map)
{
	uint32_t			key;
	t_edges				*ptr;
	t_vertices			*node;

	key = map->end_index;
	node = map->hashtab[map->end_index];
	while (node != NULL)
	{
		printf("000\n");
		ptr = node->adjc;
		while (ptr != NULL)
		{
			printf("111\n");
			if (ptr->key == key)
				ptr->way = closed_way;
			ptr = ptr->next;
		}
		key = node->key;
		node = node->prev;
	}
}
