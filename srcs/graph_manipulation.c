/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_manipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 14:37:21 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/16 22:25:21 by abrunet          ###   ########.fr       */
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
			node->way = OPEN;
			break ;
		}
		node = node->next;
	}
	node = map->hashtab[key]->adjc;
	while (node != NULL)
	{
		if (node->key == prevkey)
		{
			node->way = OPEN;
			break ;
		}
		node = node->next;
	}
}
#include <stdio.h>
static uint8_t			ft_overlaps(t_map *map, uint32_t prevkey, uint32_t key)
{
	t_edges				*ptr;
	t_edges				*node;

	node = map->hashtab[prevkey]->adjc;
	while (node != NULL)
	{
		if (node->key == key && node->way == CLOSED)
		{
			//		printf("here\n");
			ptr = map->hashtab[key]->adjc;
			while (ptr != NULL)
			{
				if (ptr->key == prevkey && ptr->way == CLOSED)
				{
					printf("overlap %s && %s\n",map->hashtab[prevkey]->name, map->hashtab[key]->name);

					return (EXIT_SUCCESS);
				}
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

inline void				ft_update_graph(t_map *map, t_stack *lst)
{
	t_queue				*node;
	uint32_t			hashkey;

	while (lst != NULL)
	{
		node = lst->path;
		hashkey = node->key;
		while ((node = node->next) != NULL)
		{
			if (LIKELY(ft_overlaps(map, hashkey, node->key) == EXIT_FAILURE))
				ft_open_path(map, hashkey, node->key);
			hashkey = node->key;
		}
		lst = lst->next;
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
			vstd[node->key] = SELECTED;
		stacks = stacks->next;
	}
}

void					ft_make_directed(t_map *map)
{
	uint32_t			key;
	t_edges				*ptr;
	t_vertices			*node;

	key = map->end_index;
	node = map->hashtab[map->end_index];
	while (node != NULL)
	{
		ptr = node->adjc;
		while (ptr != NULL)
		{
			if (ptr->key == key)
			{
				ptr->way = CLOSED;
				break ;
			}
			ptr = ptr->next;
		}
		key = node->key;
		node = node->prev;
	}
}
