/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_algorithm.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:37:31 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/22 06:38:00 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_ALGORITHM_H
# define LEM_IN_ALGORITHM_H

# include <lem_in.h>

enum					e_visitedarray
{
	unvisited_node,
	visited_node
};

enum					e_ways
{
	closed_way,
	open_way,
	selected_way
};

#endif
