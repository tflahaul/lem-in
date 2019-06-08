/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_hard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 10:41:46 by thflahau          #+#    #+#             */
/*   Updated: 2019/06/08 12:50:53 by thflahau         ###   ########.fr       */
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
		if (LIKELY((node = ft_queue_node(ft_queue_entry(position)->key))))
			ft_list_add_tail(&(node->list), dest);
}

static inline void		ft_copy_list(t_listhead *dest, t_listhead *source)
{
	t_stack				*node;
	t_listhead			*position;

	position = source;
	ft_free_stacks(dest);
	while ((position = position->next) != source)
	{
		if (LIKELY((node = ft_stack_node()) != NULL))
		{
			ft_memcpy(node, ft_stack_entry(position), sizeof(t_stack));
			ft_copy_queue(&(node->list), position);
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

static uint8_t			ft_evaluate_solution(t_listhead *new, t_listhead *head)
{
	(void)new;
	(void)head;
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
		if (ft_evaluate_solution(&(temp.list), &(stacks.list)) != 0)
			ft_copy_list(&(stacks.list), &(temp.list));
		ft_free_stacks(&(temp.list));
		++index;
	}
//	ft_print_movements(map, &(stacks.list));
	ft_free_stacks(&(stacks.list));
}
