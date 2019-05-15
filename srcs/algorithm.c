/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 09:59:25 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/15 20:26:17 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_algorithm.h>

/*
**	Modifie le tableau `visited` pour bloquer les salles par lesquelles
**	le BFS est déjà passé. Fonction utilisée uniquement après avoir géré
**	les superpositions, au moment où l'on cherche des chemins distincts.
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
**	Supprime les stacks qui correspondent aux chemins qui ne seront pas
**	utilisés pour la solution finale.
*/

static void				ft_delete_unused_stacks(t_stack **stacks, uint16_t nb, t_map *map)
{
	t_stack				*tmp;
	t_stack				*node;
	t_queue				*ptr;

	tmp = *stacks;
	if (map->visual != 0)
	{
		ptr = tmp->path;
		while (ptr)
		{
			append_to_file(PATHS, map->hashtab[ptr->key]->name);
			ptr = ptr->next;
		}
		append_to_file(PATHS, "");
	}
//	printf("===LIST===\n");
//	while (tmp)
//	{
//		printf("%lld = size\n", tmp->size);
//		tmp = tmp->next;
//	}
//	printf("===END===\n");
	if (nb == 1)
		return (ft_free_stacks(&(*stacks)->next));
	*stacks = ft_stack_pop(stacks);
	node = *stacks;
	while (nb-- && node != NULL)
	{
		tmp = node;
		node = node->next;
	}
	tmp->next = NULL;
	ft_free_stacks(&node);
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
	ft_delete_unused_stacks(&list, nbr_optimum_paths(map, list), map);
	if (map->visual != 0 && write_paths_to_file(map, list) == EXIT_FAILURE)
		return (ft_free_stacks(&list));
	ft_population_distribution(map, list);
//	ft_print_movements(map, list);
	ft_free_stacks(&list);
}

/*
**	Tools
*/

inline uint64_t			ft_last_path_length(t_stack *list)
{
	if (list != NULL)
		while (list->next != NULL)
			list = list->next;
	return (list->size);
}

uint64_t				ft_list_size(t_stack *list)
{
	uint64_t			length;

	length = 0;
	while (list != NULL && ++length)
		list = list->next;
	return (length);
}
