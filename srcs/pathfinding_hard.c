/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_hard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 10:41:46 by thflahau          #+#    #+#             */
/*   Updated: 2019/06/08 15:29:57 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_list.h>
#include <lem_in_stacks.h>
#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>

static inline void		ft_copy_queue(t_listhead *dest, t_listhead *source)
{
	t_queue				*node;
	t_listhead			*position;

	position = source;
	while ((position = position->next) != source)
		if ((node = ft_queue_node(ft_queue_entry(position)->key)) != NULL)
			ft_list_add_tail(&(node->list), dest);
}

static inline void		ft_copy_list(t_listhead *dest, t_listhead *source)
{
	t_stack				*node;
	t_listhead			*position;

	position = source;
	ft_free_stacks(dest);
	ft_list_init_head(dest);
	while ((position = position->next) != source)
	{
		if (LIKELY((node = ft_stack_node()) != NULL))
		{
			if ((node->path = (t_queue *)malloc(sizeof(t_queue))))
				ft_list_init_head(&(node->path->list));
			node->ant = ft_stack_entry(position)->ant;
			node->size = ft_stack_entry(position)->size;
			ft_copy_queue(&(node->path->list), \
				&(ft_stack_entry(position)->path->list));
			ft_list_add_tail(&(node->list), dest);
		}
	}
}

static inline void		ft_reset_graph(t_map *map, uint32_t hk, uint32_t pk)
{
	t_edges				*ptr;
	register uint16_t	index;

	index = 0;
	while (index < MAX_VERTICES)
	{
		if (map->hashtab[index]->key != 0)
		{
			ptr = map->hashtab[index]->adjc;
			if (index == hk || index == pk)
			{
				while (ptr != NULL)
				{
					if (ptr->key == hk || ptr->key == pk)
						ptr->way = closed_way;
					else
						ptr->way = open_way;
					ptr = ptr->next;
				}
			}
			else
			{
				while (ptr != NULL)
				{
					ptr->way = open_way;
					ptr = ptr->next;
				}
			}
		}
		++index;
	}
}

static inline uint8_t	ft_evaluate_solution(t_map *map, t_listhead *new,
														t_listhead *head)
{
	int32_t				s;
	uint32_t			min;

	s = 1;
	nbr_optimum_paths(map, head, &s);
	ft_population_distribution(map, head);
	min = ft_stack_entry(head->next)->ant + ft_stack_entry(head->next)->size;
	s = 1;
	nbr_optimum_paths(map, new, &s);
	ft_population_distribution(map, new);
	if (ft_stack_entry(new->next)->ant + ft_stack_entry(new->next)->size < min)
		return (1);
	return (0);
}

void					ft_advanced_pathfinding(t_map *map, uint32_t **tab)
{
	int8_t				visited[MAX_VERTICES];
	t_stack				temp;
	t_stack				stacks;
	uint32_t			prevkey;
	uint32_t			hashkey;
	register uint16_t	index;

	index = 0;
	ft_list_init_head(&(temp.list));
	ft_list_init_head(&(stacks.list));
	while (tab[index] != 0)
	{
		prevkey = tab[index][0];
		hashkey = tab[index][1];
		ft_fast_bzero(visited, MAX_VERTICES);
		ft_reset_graph(map, hashkey, prevkey);
		while (ft_breadth_first_search(map, visited) == EXIT_SUCCESS)
		{
			ft_join_paths(map, &(temp.list));
			ft_update_visited_array(visited, &(temp.list));
		}
		if (ft_evaluate_solution(map, &(temp.list), &(stacks.list)) != 0)
			ft_copy_list(&(stacks.list), &(temp.list));
		ft_free_stacks(&(temp.list));
		++index;
	}
	ft_print_movements(map, &(stacks.list));
	ft_free_stacks(&(stacks.list));
}
