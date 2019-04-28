/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 09:59:25 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/28 11:21:47 by thflahau         ###   ########.fr       */
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

static inline void		ft_update_visited(void *stacks, uint8_t *visited)
{
	t_queue				*node;

	ft_fast_bzero(visited, MAX_VERTICES);
	while (stacks != NULL)
	{
		node = ((t_stack *)stacks)->path;
		while (node != NULL)
		{
			visited[node->key] = 2;
			node = node->next;
		}
		stacks = ((t_stack *)stacks)->next;
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

void					ft_algorithm(t_map *map)
{
	t_stack				*list;
	uint8_t				visited[MAX_VERTICES];

	list = NULL;
	ft_fast_bzero(visited, MAX_VERTICES);
	while (ft_breadth_first_search(map, visited) == EXIT_SUCCESS)
	{
		ft_push_path_to_stack(map, &list);
		ft_update_visited(list, visited);
		ft_make_directed(map);
	}
	ft_fast_bzero(visited, MAX_VERTICES);
	ft_update_graph(map, list);
	ft_free_stacks(&list);
	while (ft_breadth_first_search(map, visited) == EXIT_SUCCESS)
	{
		ft_push_path_to_stack(map, &list);
		ft_update_visited(list, visited);
		ft_make_directed(map);
	}
	print_paths(map, list);
	ft_free_stacks(&list);
}
