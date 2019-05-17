/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 09:59:25 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/17 23:44:43 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_bug.h>
#include <lem_in_compiler.h>
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
			visited[ptr->key] = visited_node;
	}
}

/*
**	Supprime les stacks qui correspondent aux chemins qui ne seront pas
**	utilisés pour la solution finale.
*/

static void				ft_delete_unused_stacks(t_stack **stacks, uint16_t nb,
												t_map *map)
{
	t_stack				*node;
	t_stack				*tmp;
	t_queue				*ptr;

	if (!!(map->visual & VISUAL))
	{
		ptr = (*stacks)->path;
		while (ptr != NULL)
		{
			append_to_file(PATHS, map->hashtab[ptr->key]->name);
			ptr = ptr->next;
		}
		append_to_file(PATHS, "");
	}
	if (nb == 1)
		return ((void)ft_free_stacks(&(*stacks)->next));
	*stacks = ft_stack_pop(stacks);
	node = (*stacks)->next;
	while (nb-- > 0 && node != NULL)
	{
		tmp = node;
		node = node->next;
	}
	tmp->next = NULL;
	ft_free_stacks(&node);
}

/*
void					print_graph(t_map *map)
{
	register uint16_t	index = 0;

	while (index < MAX_VERTICES)
	{
		if (map->hashtab[index]->name != NULL)
		{
			printf("%s\t", map->hashtab[index]->name);
			t_edges *ptr = map->hashtab[index]->adjc;
			while (ptr != NULL)
			{
				printf("  -> %s(%i)", map->hashtab[ptr->key]->name, ptr->way);
				ptr = ptr->next;
			}
			printf("\n");
		}
		index++;
	}
}
*/

uint8_t					ft_algorithm(t_map *map)
{
	t_stack				*list;
	int					path;
	uint8_t				visited[MAX_VERTICES];

	list = NULL;
	path = 1;
	ft_fast_bzero(visited, MAX_VERTICES);
	while (ft_breadth_first_search(map, visited, list) == EXIT_SUCCESS)
	{
		ft_push_path_to_stack(map, &list);
		ft_update_visited_array(list, visited);
		ft_make_directed(map);
	}
//	print_paths(map, list);
//	print_graph(map);
	if (UNLIKELY(list == NULL))
		return (ft_printf(C_RED"lem-in: %s\n"C_NONE, DEADEND));
	ft_update_graph(map, list);
	ft_free_stacks(&list->next);
	ft_fast_bzero(visited, MAX_VERTICES);
	while (ft_simple_bfs(map, visited) == EXIT_SUCCESS)
	{
		if (UNLIKELY(ft_push_path_to_stack(map, &list)) == EXIT_FAILURE)
			ft_make_directed(map);
		ft_fast_bzero(visited, MAX_VERTICES);
		ft_update_tab(list, visited);
	}
//	print_paths(map, list);
//	return (ft_free_stacks(&list));
	ft_delete_unused_stacks(&list, nbr_optimum_paths(map, list, &path), map);
	if (map->visual & VISUAL && write_paths_to_file(map, list) == EXIT_FAILURE)
		return (ft_free_stacks(&list));
	ft_population_distribution(map, list);
	ft_print_movements(map, list);
	return (ft_free_stacks(&list));
}

inline uint64_t			ft_last_path_length(t_stack *list)
{
	if (list == NULL)
		return (0);
	while (list->next != NULL)
		list = list->next;
	return (list->size);
}
