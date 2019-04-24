/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_stacks.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 16:03:49 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/24 16:49:43 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_STACKS_H
# define LEM_IN_STACKS_H

# include <lem_in_queue.h>

typedef struct				s_stack
{
	uint64_t				size;
	struct s_queue			*path;
	struct s_stack			*next;
}							t_stack;

void						ft_free_stacks(t_stack **head);
void						ft_print_movements(t_map *map, t_stack *list);
uint64_t					ft_push_path_to_stack(t_map *map, t_stack **stack);

#endif
