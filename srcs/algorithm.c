/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:27:29 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/20 18:01:35 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_queue.h>
#include <lem_in_stacks.h>
#include <lem_in_compiler.h>

uint32_t				get_optimum_path_nb(t_stack *list, uint32_t ants, uint64_t pos)
{
	uint32_t			res;
	uint32_t			index;
	uint32_t			sum1;
	uint32_t			sum2;
	t_stack				*tmp;

	sum1 = ants + (list->size - 1) - 1;
	tmp = list;
	if (pos && tmp->next)
		tmp = list->next;
	if (!list)
		return (0);
	res = 1;
	index = 1;
	while (tmp)
	{
		sum2 = (ants / index + (tmp->size - 1) - 1);
		if (sum1 > sum2)
		{
			sum1 = sum2;
			res = index;
		}
		tmp = tmp->next;
		index++;
	}
	return (res);
}

void					clean_up_overlap(t_map *map)
{
	t_vertices			*ptr;
	t_edges				*node;

	ptr = map->hashtab[map->end_index];
	while (ptr)
	{
		node = ptr->adjc;
		while (node)
		{
			if (node->way == CLOSED)
				node->way = OPEN;
			node = node->next;
		}
		ptr = ptr->prev;
	}
}

void					clean_up_graph(t_map *map, t_stack **list)
{
	t_queue		*node;
	t_edges		*edges;
//	t_stack		*tmp;

//	tmp = list;
	while ((*list)->next->next)
		*list = (*list)->next;
	node = (*list)->path;
	while (node)
	{
		edges = map->hashtab[node->key]->adjc;	
		while (edges)
		{
			if (edges->way == CLOSED)
				edges->way = OPEN;
			edges = edges->next;
		}
		node = node->next;
	}
	clean_up_overlap(map);
	printf("\n===CLEAN===\n");
	print_hashtab(map);
	
}

void					ft_algorithm(t_map *map)
{
	t_stack				*list;
	uint32_t			paths;
	uint8_t				visited[MAX_VERTICES];

	if (map->vertices == 0)
		return ;
	list = ft_allocate_stack_memory();
	ft_memset(visited, 0, MAX_VERTICES);
	print_hashtab(map);
	while (ft_breadth_first_search(map, visited) == EXIT_SUCCESS)
	{
		if (!map->superposition)
			ft_push_path_to_stack(map, &list);
		else
		{
			clean_up_graph(map, &list);
			map->superposition = 0;
		}
		ft_memset(visited, 0, MAX_VERTICES);
	}
	set_last_to_null(list);
	paths = get_optimum_path_nb(list, map->population, map->superposition);
	ft_print_movements(map, list);
	ft_free_stacks(&list);
}
