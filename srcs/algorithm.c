/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 09:59:25 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/27 18:12:08 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_bug.h>
#include <lem_in_stacks.h>
#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>

static void				ft_join_paths(t_map *map, t_listhead *head)
{
	t_queue				*list;
	t_stack				*node;
	t_vertices			*vertex;

	if (LIKELY((node = ft_stack_node()) != NULL))
	{
		if (LIKELY((node->path = (t_queue *)malloc(sizeof(t_queue))) != NULL))
			ft_list_init_head(&(node->path->list));
		vertex = map->hashtab[map->end_index];
		while (vertex != NULL)
		{
			if (LIKELY((list = ft_queue_node((uint32_t)vertex->key)) != NULL))
			{
				ft_list_push(&(list->list), &(node->path->list));
				++node->size;
			}
			vertex = vertex->prev;
		}
		ft_list_add_tail(&(node->list), head);
	}
}

/*
**	Update 'visited' array to indicate nodes through which the BFS algorithm
**	have gone. Function only used after overlaps have been handled, when
**	looking for distinct paths.
*/

static inline void		ft_update_visited_array(int8_t *array,
												int8_t value,
												t_listhead *head)
{
	t_listhead			*ref;
	t_listhead			*node;
	t_listhead			*position;

	position = head;
	ft_fast_bzero(array, MAX_VERTICES);
	while ((position = position->next) != head)
	{
		ref = &(ft_stack_entry(position)->path->list);
		node = ref->next;
		while ((node = node->next) != ref->prev)
			array[ft_queue_entry(node)->key] = value;
	}
}

/*
**	Reproduction d'un "Dévier (si possible) le chemin A et garder le B"
*/

static void				ft_conflict_management(t_graph *graph,
											t_listhead *head,
											uint32_t hashkey)
{
	t_queue				*node;
	t_listhead			*ptr;

	ptr = &(ft_stack_entry(head->prev)->path->list);
	while ((ptr = ptr->prev) != &(ft_stack_entry(head->prev)->path->list))
	{
		node = ft_queue_entry(ptr);
		if (node->key == hashkey)
		{
			while (ft_breadth_first_search(graph->map, graph->visited) == EXIT_FAILURE)
			{
				ptr = ptr->prev;
				graph->visited[ft_queue_entry(ptr)->key] = selected_node;
			}
			ft_join_paths(graph->map, head->next);
			break ;
		}
		graph->visited[node->key] = unvisited_node;
	}
//	ft_update_visited_array(graph->visited, visited_node, head->next); // crash
}

/*
**	Cherche les vertex communs aux deux derniers chemins trouvés. Pour chaque
**	vertex commun, un `conflit` est ouvert où on va déterminer la meilleure
**	action à faire (reste à savoir selon quelles heuristiques) parmi:
**	1 - Détruire le chemin A et n'utiliser que le B
**	2 - Détruire le chemin B et n'utiliser que le A
**	3 - Dévier (si possible) le chemin A et garder le B
**	4 - Dévier (si possible) le chemin B et garder le A
*/

static void				ft_search_for_common_vertices(t_graph *graph,
													t_listhead *head)
{
	t_listhead			*pv;
	t_listhead			*path;
	register uint32_t	hashkey;

	path = ft_stack_entry(head)->path->list.next;
	while ((path = path->next) != ft_stack_entry(head)->path->list.prev)
	{
		hashkey = ft_queue_entry(path)->key;
		pv = &(ft_stack_entry(head->prev)->path->list);
		if (LIKELY(head->prev != head->next))
			while ((pv = pv->next) != &(ft_stack_entry(head->prev)->path->list))
				if (ft_queue_entry(pv)->key == hashkey)
					ft_conflict_management(graph, head, hashkey);
	}
}

uint8_t					ft_algorithm(t_map *map)
{
	t_graph				graph;
	t_stack				stacks;

	ft_list_init_head(&(stacks.list));
	ft_fast_bzero(graph.visited, MAX_VERTICES);
	while (ft_breadth_first_search(map, graph.visited) == EXIT_SUCCESS)
	{
		ft_join_paths(map, &(stacks.list));
		ft_fast_bzero(graph.visited, MAX_VERTICES);
		ft_make_directed(map, stacks.list.prev);
	}
	if (UNLIKELY(&(stacks.list) == stacks.list.next))
		return (ft_puterror(DEADEND));
	ft_update_graph(map, &(stacks.list));
	ft_fast_bzero(graph.visited, MAX_VERTICES);
	ft_free_stacks(&(stacks.list));
	while (ft_breadth_first_search(map, graph.visited) == EXIT_SUCCESS)
	{
		ft_join_paths(map, &(stacks.list));
		ft_update_visited_array(graph.visited, selected_node, &(stacks.list));
		ft_search_for_common_vertices(&graph, stacks.list.prev);
	}
	ft_free_stacks(&(stacks.list));
	return (EXIT_SUCCESS);
}
