/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_algorithm.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:37:31 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/16 15:26:27 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_ALGORITHM_H
# define LEM_IN_ALGORITHM_H

# include <lem_in.h>
# include <lem_in_stacks.h>

enum
{
	UNVISITED,
	VISITED,
	SELECTED
};

typedef struct				s_graph
{
	struct s_map			*map;
	struct s_queue			**queue;
	uint8_t					*visited;
}							t_graph;

void						ft_make_directed(t_map *map);
void						ft_update_graph(t_map *map, t_stack *lst);
void						ft_update_visited_array(t_stack *s, uint8_t *v);
uint32_t					ft_population_distribution(t_map *map, t_stack *s);
uint32_t                   	nbr_optimum_paths(t_map *map, t_stack *stacks);
uint64_t					ft_abs(int64_t nb);

#endif
