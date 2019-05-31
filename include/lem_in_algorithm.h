/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_algorithm.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:37:31 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/31 12:45:37 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_ALGORITHM_H
# define LEM_IN_ALGORITHM_H

# ifndef LEM_IN_H
#  include <lem_in.h>
# endif
# ifndef LEM_IN_STACKS_H
#  include <lem_in_stacks.h>
# endif

enum					e_vertex {
	selected_node = -1,
	unvisited_node,
	visited_node
};

enum					e_direction {
	closed_way,
	open_way,
	selected_way
};

typedef struct			s_graph
{
	t_map				*map;
	int8_t				visited[MAX_VERTICES];
}						t_graph;

int						nbr_optimum_paths(t_map *map, t_listhead *head, int *p);
void					ft_population_distribution(t_map *map, t_listhead *h);
void					ft_print_movements(t_map *map, t_listhead *head);
void					ft_make_directed(t_map *map, t_listhead *head);
void					ft_update_graph(t_map *map, t_listhead *head);
uint8_t					ft_overlaps(t_map *map, uint32_t prev, uint32_t key);

#endif
