/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 09:59:25 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/24 17:32:27 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Je teste juste des trucs dans ce fichier! Le vrai algo reste dans
**	algorithm.c!
*/

#include <lem_in.h>
#include <lem_in_stacks.h>
#include <lem_in_compiler.h>

void					print_hashtab(t_map *map);
void					print_paths(t_map *map, t_stack *list);

static uint8_t			ft_overlaps(t_map *map, uint32_t prevkey, uint32_t key)
{
	t_edges				*ptr;
	t_edges				*node;

	node = map->hashtab[prevkey]->adjc;
	while (node != NULL)
	{
		if (node->key == key && node->way == CLOSED)
		{
			ptr = map->hashtab[key]->adjc;
			while (ptr != NULL)
			{
				if (ptr->key == prevkey && ptr->way == CLOSED)
					return (EXIT_SUCCESS);
				ptr = ptr->next;
			}
		}
		node = node->next;
	}
	return (EXIT_FAILURE);
}

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

static inline void		ft_update_graph(t_map *map, t_stack *lst)
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

/*
**	Dirige le dernier chemin trouvé et met les pointeurs `prev` à null
**	dans le même temps. (à voir plus tard si c'est vraiment utile)
*/

static void				ft_make_directed(t_map *map)
{
	uint32_t			key;
	t_edges				*ptr;
	t_vertices			*tmp;
	t_vertices			*node;

	key = map->end_index;
	node = map->hashtab[map->end_index];
	while (node != NULL)
	{
		ptr = node->adjc;
		while (ptr != NULL)
		{
			if (ptr->key == key)
				ptr->way = CLOSED;
			ptr = ptr->next;
		}
		key = node->key;
		tmp = node->prev;
		node->prev = NULL;
		node = tmp;
	}
}

/*
**	Trouve uniquement le chemin le plus court, ne fais rien d'autre.
*/

uint8_t					ft_breadth_first_search(t_map *map, uint8_t *vstd)
{
	uint32_t			key;
	t_edges				*node;
	t_queue				*queue;

	queue = NULL;
	vstd[map->start_index] = 1;
	ft_queue_push(&queue, map->start_index);
	while (queue != NULL)
	{
		key = queue->key;
		if (key == map->end_index && ft_drain_queue(&queue) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
		queue = ft_queue_pop(&queue);
		node = map->hashtab[key]->adjc;
		while (node != NULL)
		{
			if (node->way == OPEN && !vstd[node->key] && (vstd[node->key] = 1))
			{
				map->hashtab[node->key]->prev = map->hashtab[key];
				ft_queue_append(&queue, node->key);
			}
			node = node->next;
		}
	}
	return (EXIT_FAILURE);
}

void					ft_algorithm(t_map *map)
{
	t_stack				*list;
	uint8_t				visited[MAX_VERTICES];

	list = NULL;
	ft_fast_bzero(visited, MAX_VERTICES);
	while (ft_breadth_first_search(map, visited) == EXIT_SUCCESS)
	{
		ft_fast_bzero(visited, MAX_VERTICES);
		ft_push_path_to_stack(map, &list);
		if (map->population < list->size - 1)
			return (ft_print_movements(map, list));
		ft_make_directed(map);
	}
	ft_fast_bzero(visited, MAX_VERTICES);
	ft_update_graph(map, list);
	ft_free_stacks(&list);
	while (ft_breadth_first_search(map, visited) == EXIT_SUCCESS)
	{
		ft_fast_bzero(visited, MAX_VERTICES);
		ft_push_path_to_stack(map, &list);
		ft_make_directed(map);
	}
	ft_print_movements(map, list);
	ft_free_stacks(&list);
}
