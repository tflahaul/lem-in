/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 09:59:25 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/29 16:30:45 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_stacks.h>
#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>

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

/*
**	Nettoie toutes les connexions du graph, sauf celles pour lesquelles deux
**	chemins se superposent, qui restent bloquées... pour toujours...
*/

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

static inline void		ft_update_visited_array(t_stack *stacks, uint8_t *vstd)
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

/*
**	Modifie le tableau `visited` pour bloquer les salles par lesquelles
**	le BFS est déjà passé. Fonction utilisée uniquement après avoir géré
**	les superpositions, au moment où on cherche des chemins distincts.
*/

static inline void		ft_update_tab(t_stack *node, uint8_t *visited)
{
	t_queue				*ptr;

	while ((node = node->next) != NULL)
	{
		ptr = node->path;
		while ((ptr = ptr->next)->next != NULL)
			visited[ptr->key] = VISITED;
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
		ft_update_visited_array(list, visited);
		ft_make_directed(map);
	}
	ft_update_graph(map, list);
	ft_free_stacks(&list->next);
	ft_fast_bzero(visited, MAX_VERTICES);
	while (ft_simple_bfs(map, visited) == EXIT_SUCCESS)
	{
		ft_push_path_to_stack(map, &list);
		ft_fast_bzero(visited, MAX_VERTICES);
		ft_update_tab(list, visited);
	}
	print_paths(map, list);
	ft_free_stacks(&list);
}
