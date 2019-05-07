/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 09:59:25 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/07 18:51:11 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
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
			visited[ptr->key] = VISITED;
	}
}

/*
**	Retourne la somme des tailles des `nb` chemins les plus courts.
*/

static uint64_t			ft_get_total_size(t_stack *stacks, uint32_t nb)
{
	uint64_t			size;

	size = 0;
	while (nb-- && LIKELY(stacks != NULL))
	{
		size += stacks->size - 1;
		stacks = stacks->next;
	}
	return (size);
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

static inline uint64_t	ft_magic_formula(t_map *map, t_stack *p, uint64_t size)
{
	return (map->population * (double)ABS(1 + (-p->size / size)) + p->size - 2);
}

static uint32_t			ft_compute_steps(t_map *map, t_stack *lst, uint32_t nb)
{
	t_stack				*ptr;
	int64_t				steps;
	uint16_t			index;
	uint64_t			length;

	steps = 0;
	if (nb == 1)
		return (map->population + (lst->size - 1) - 1);
	else if (LIKELY((lst = lst->next) != NULL))
	{
		index = 1;
		ptr = lst;
		length = ft_get_total_size(lst, nb);
		steps = (map->population / nb) + (ptr->size - 1) - 1;
		while (index++ < nb && LIKELY(ptr != NULL))
		{
			steps += ABS(steps - ft_magic_formula(map, ptr, length)); // ERR
			ptr = ptr->next;
		}
	}
	return ((uint32_t)steps);
}

/*
**	Fonction pour la distribution des fourmis dans les chemins
*/

static uint16_t			ft_population_distribution(t_map *map, t_stack *stacks)
{
	uint16_t			index;
	uint32_t			steps;

	index = 2;
	steps = ft_compute_steps(map, stacks, 1);
	printf("steps = %u\n", steps);
	while (index <= map->start_edges)
	{
		steps = ft_compute_steps(map, stacks, index);
		printf("steps = %u\n", steps);
		index++;
	}
	return (index - 1);
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
	ft_population_distribution(map, list);
	ft_free_stacks(&list);
}
