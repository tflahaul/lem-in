/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_algorithm.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:37:31 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/28 15:26:04 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_ALGORITHM_H
# define LEM_IN_ALGORITHM_H

# include <lem_in.h>
# include <lem_in_queue.h>

# define UNVISITED			0
# define VISITED			1
# define SELECTED			2

typedef struct				s_graph
{
	struct s_map			*map;
	struct s_queue			**queue;
	uint8_t					*visited;
}							t_graph;

#endif
