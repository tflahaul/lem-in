/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_hard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 10:41:46 by thflahau          #+#    #+#             */
/*   Updated: 2019/06/09 12:33:11 by thflahau         ###   ########.fr       */
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
	ft_stack_entry(dest)->ant = ft_stack_entry(source)->ant;
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
												uint32_t *min)
{
	int32_t				s;

	s = 1;
	ft_delete_unused_stacks(new, map, nbr_optimum_paths(map, new, &s));
	ft_population_distribution(map, new);
	if (ft_stack_entry(new)->ant + ft_stack_entry(new->next)->size < *min)
	{
		*min = ft_stack_entry(new)->ant + ft_stack_entry(new->next)->size;
		return (1);
	}
	return (0);
}

void					ft_advanced_pathfinding(t_map *map, uint32_t **tab)
{
	int32_t				s;
	uint32_t			min;
	int8_t				visited[MAX_VERTICES];
	t_stack				temp;
	t_stack				stacks;
	register uint16_t	index;

	s = 1;
	index = 0;
	min = UINT32_MAX;
	ft_list_init_head(&(temp.list));
	ft_list_init_head(&(stacks.list));
	while (tab[index] != 0)
	{
		ft_fast_bzero(visited, MAX_VERTICES);
		ft_reset_graph(map, tab[index][0], tab[index][1]);
		while (ft_breadth_first_search(map, visited) == EXIT_SUCCESS)
		{
			ft_join_paths(map, &(temp.list));
			ft_update_visited_array(visited, &(temp.list));
		}
		if (ft_evaluate_solution(map, &(temp.list), &min) != 0)
		{
			s = 1;
			ft_copy_list(&(stacks.list), &(temp.list));
			stacks.ant = temp.ant;
			nbr_optimum_paths(map, &(stacks.list), &s);
			ft_population_distribution(map, &(stacks.list));
		}
		ft_free_stacks(&(temp.list));
		++index;
	}
	ft_print_movements(map, &(stacks.list));
	ft_free_stacks(&(stacks.list));
}
