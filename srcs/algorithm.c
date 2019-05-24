/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 09:59:25 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/24 18:56:19 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_bug.h>
#include <lem_in_stacks.h>
#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>
#include <stdio.h>

static void				print_stack(t_map *map, t_listhead *head)
{
	t_stack				*node;
	t_listhead			*ptr;
	t_listhead			*position = head->next;

	while (position != head)
	{
		node = LIST_ENTRY(position, t_stack, list);
		ptr = node->path->list.next;
		printf("\n================\n");
		while (ptr != &(node->path->list))
		{
			printf("%s\n", map->hashtab[LIST_ENTRY(ptr, t_queue, list)->key]->name);
			ptr = ptr->next;
		}
		position = position->next;
	}
	ft_putchar(10);
}

static void				ft_join_paths(t_map *map, t_listhead *head)
{
	t_queue				*list;
	t_stack				*node;
	t_vertices			*vertice;

	if (LIKELY((node = (t_stack *)malloc(sizeof(t_stack))) != NULL))
	{
		node->ant = 0;
		node->size = 0;
		if (LIKELY((node->path = (t_queue *)malloc(sizeof(t_queue))) != NULL))
			ft_list_init_head(&(node->path->list));
		vertice = map->hashtab[map->end_index];
		while (vertice != NULL)
		{
			if (LIKELY((list = ft_queue_node((uint32_t)vertice->key)) != NULL))
			{
				ft_list_push(&(list->list), &(node->path->list));
				++node->size;
			}
			vertice = vertice->prev;
		}
		ft_list_add_tail(&(node->list), head);
	}
}

void					check_for_doubles(t_map *map)
{
	t_edges				*path;
	t_vertices			*node;
	t_vertices			*prev;
	t_vertices			*tmp;
	int32_t				i;
	int32_t				j;

	i = 0;
	node = map->hashtab[map->end_index];
	tmp = node;
	prev = node;
	while ((node = node->prev) != NULL)
	{
		i++;
		tmp = map->hashtab[map->end_index];
		j = 0;
		while (tmp != node)
		{
			tmp = tmp->prev;
			++j;
		}
		if (j != i)
		{
			path = map->hashtab[prev->key]->adjc;
			while (path != NULL)
			{
				if (path->key == node->key)
				{
					path->way = closed_way;
					break;
				}
				path = path->next;
			}
			path = map->hashtab[node->key]->adjc;
			while (path != NULL)
			{
				if (path->key == prev->key)
				{
					path->way = closed_way;
					break;
				}
				path = path->next;
			}
			break;
		}
		prev = node;
	}
	prev->prev = NULL;
}

t_edges					*look_for_neg_edge(t_edges *edge)
{
	t_edges				*tmp;

	tmp = edge;
	while (tmp != NULL)
	{
		if (tmp->way == -1)
		{
			tmp->way = 2;
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (tmp);
}

uint8_t					neg_edge_bfs(t_map *map,
									t_listhead *head,
									int8_t *visited,
									uint32_t key)
{
	t_edges				*vert;
	t_listhead			*node;

	node = head->next;
	while (node != head)
	{
		key = LIST_ENTRY(node, t_queue, list)->key;
		if (key == map->end_index)
			return (ft_list_del(head));
		ft_list_pop(node);
		vert = map->hashtab[key]->adjc;
		if ((vert = look_for_neg_edge(vert)) != NULL && visited[vert->key] != visited_node)
		{
			visited[key] = unvisited_node;
			visited[vert->key] = visited_node;
			map->hashtab[vert->key]->prev = map->hashtab[key];
			ft_list_add_tail(&(ft_queue_node(vert->key)->list), node);
			if (neg_edge_bfs(map, node->prev, visited, vert->key) == EXIT_FAILURE)
				return (neg_edge_bfs(map, node->prev, visited, key));
			else
				return (EXIT_SUCCESS);
		}
		vert = map->hashtab[key]->adjc;
		while (vert != NULL)
		{
			if (vert->way == open_way && !visited[vert->key] && (visited[vert->key] = visited_node))
			{
				map->hashtab[vert->key]->prev = map->hashtab[key];
				ft_list_add_tail(&(ft_queue_node(vert->key)->list), head->next);
			}
			vert = vert->next;
		}
	}
	return (EXIT_FAILURE);
}

static uint8_t			ft_bfs(t_map *map, int8_t *visited, t_listhead *head)
{
	t_queue				queue;
	register uint32_t	key;

	key = map->start_index;
	visited[key] = visited_node;
	ft_list_init_head(&(queue.list));
	ft_list_push(&(ft_queue_node(key)->list), &(queue.list));
	if (neg_edge_bfs(map, &(queue.list), visited, key) == EXIT_SUCCESS)
	{
		check_for_doubles(map);
		ft_join_paths(map, head);
		ft_make_directed(map, head->prev);
		ft_fast_bzero(visited, MAX_VERTICES);
		return (EXIT_SUCCESS);
	}
//	ft_update_graph(map, head);
	return (EXIT_FAILURE);
}

uint8_t					ft_algorithm(t_map *map)
{
	t_stack				stacks;
	int8_t				visited[MAX_VERTICES];
	uint8_t				test = EXIT_SUCCESS;
	int8_t				ind = 2;

	ft_list_init_head(&(stacks.list));
	ft_fast_bzero(visited, MAX_VERTICES);
	while (--ind && test == EXIT_SUCCESS)
	{
		test = ft_bfs(map, visited, &(stacks.list));
	}
	if (UNLIKELY(&(stacks.list) == stacks.list.next))
		return (ft_puterror(DEADEND));
	ft_fast_bzero(visited, MAX_VERTICES);
//	while (ft_breadth_first_search(map, visited) == EXIT_SUCCESS)
//	{
//		ft_join_paths(map, &(stacks.list));
//		ft_fast_bzero(visited, MAX_VERTICES);
//		ft_make_directed(map, stacks.list.prev);
//	}
	print_stack(map, &(stacks.list));
	ft_free_stacks(&(stacks.list));
	return (EXIT_SUCCESS);
}
