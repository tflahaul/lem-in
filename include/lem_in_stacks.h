/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_stacks.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 16:03:49 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/17 18:30:02 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_STACKS_H
# define LEM_IN_STACKS_H

# include <lem_in.h>
# include <lem_in_queue.h>

typedef struct				s_stack
{
	uint64_t				ant;
	uint64_t				size;
	struct s_queue			*path;
	struct s_stack			*next;
}							t_stack;

void						ft_print_movements(t_map *map, t_stack *list);
uint8_t						ft_free_stacks(t_stack **head);
uint8_t						ft_path_checker(t_map *map, t_queue *node);
uint8_t						write_paths_to_file(t_map *map, t_stack *list);
uint32_t					ft_push_path_to_stack(t_map *map, t_stack **stack);
uint64_t					ft_last_path_length(t_stack *list);
uint64_t					ft_list_size(t_stack *list);
t_stack						*ft_stack_pop(t_stack **head);

#endif
