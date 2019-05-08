/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 09:59:25 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/08 16:37:46 by thflahau         ###   ########.fr       */
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

static void				ft_delete_unused_stacks(t_stack **stacks, uint16_t nb)
{
	t_stack				*node;

	node = *stacks;
	if (nb == 1)
		ft_free_stacks(&(*stacks)->next);
	else
	{
		*stacks = ft_stack_pop(stacks);
		node = *stacks;
		while (node != NULL && nb--)
			node = node->next;
		ft_free_stacks(&node);
	}
}
*/

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
	ft_population_distribution(map, list);
	ft_free_stacks(&list);
}
