/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_algorithm.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:37:31 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/21 15:41:55 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_ALGORITHM_H
# define LEM_IN_ALGORITHM_H

# include <lem_in.h>
# include <lem_in_stacks.h>

enum					e_visitedarray
{
	unvisited_node = 0,
	visited_node = 1
};

enum					e_ways
{
	closed_way = 0,
	open_way,
	selected_way
};

typedef struct			s_graph
{
	struct s_map		**map;
	struct s_queue		**queue;
	uint8_t				*visited;
}						t_graph;

void					ft_update_graph(t_map *map, t_stack *lst);
void					ft_make_directed(t_map *map, t_stack *list);
void					ft_population_distribution(t_map *map, t_stack *s);
int						nbr_optimum_paths(t_map *map, t_stack *stacks, int *p);
uint8_t					ft_depth_first_search(t_graph *g, uint32_t key,
											uint32_t dest, t_stack *list);

#endif
