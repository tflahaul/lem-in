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

void					clean_up_graph(t_map *map, t_stack *list)
{
	t_queue		*node;
	t_edges		*edges;

	node = list->path;
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
//	printf("\n===CLEAN===\n");
//	print_hashtab(map);
	
}

/*void					print_overlap(t_map *map)
{
	t_vertices *ptr;

	ptr = map->hashtab[map->end_index];
	printf("\n===OVERLAP===\n");
	while ((ptr = ptr->prev))
	{
		printf("%s\n", map->hashtab[ptr->key]->name);
	}
}*/

void					print_stack(t_stack *list, t_map *map)
{
	t_queue		*node;
	t_stack		*tmp;

	tmp = list;
	while (tmp)
	{
		node = tmp->path;
		printf("\n===PATH===\n");
		while (node)
		{
			printf("%s\n", map->hashtab[node->key]->name);
			node = node->next;
		}
		tmp = tmp->next;
	}
}

void					free_ptr(t_stack *ptr)
{
	t_queue		*node;
	t_queue		*tmp;

	node = ptr->path;
	while (node)
	{
		tmp = node;
		node = node->next;
		free((void *)node);
	}
	free(ptr);
}

void					reset_stack(t_stack *ptr, t_stack **list)
{
	t_stack		*tmp;
	t_stack		*prev;
	t_stack		*next;

	tmp = *list;
	prev = tmp;
	while (tmp != ptr)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	next = tmp->next;
	if (prev != ptr)
		prev->next = next;
	else 
		*list = next;
	free_ptr(ptr);
}

void					ft_algorithm(t_map *map)
{
	t_stack				*list;
	t_stack				*ptr;
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
	//		print_overlap(map);
			if ((ptr = get_overlap_path(list, map)))
			{
				clean_up_graph(map, ptr);
				reset_stack(ptr, &list);
			}
			map->superposition = 0;
		}
		ft_memset(visited, 0, MAX_VERTICES);
	}
	print_stack(list, map);
	set_last_to_null(list);
	ft_print_movements(map, list);
	ft_free_stacks(&list);
}
