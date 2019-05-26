/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_algorithm.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:37:31 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/26 15:07:48 by thflahau         ###   ########.fr       */
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

enum					e_visitedarray {
	selected_node = -1,
	unvisited_node,
	visited_node
};

enum					e_ways {
	closed_way,
	open_way,
	selected_way
};

void					ft_print_movements(t_map *map, t_stack *list);
void					ft_update_graph(t_map *map, t_listhead *head);
void					ft_make_directed(t_map *map, t_listhead *head);

#endif
