/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_stacks.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 16:03:49 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/24 17:57:42 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_STACKS_H
# define LEM_IN_STACKS_H

# ifndef LEM_IN_QUEUE_H
#  include <lem_in_queue.h>
# endif

typedef struct				s_stack
{
	t_listhead				list;
	t_queue					*path;
	uint32_t				size;
	uint32_t				ant;
}							t_stack;

void						ft_print_colored_ant(uint32_t nb, char const *str);
void						ft_free_stacks(t_listhead *head);
t_stack						*ft_stack_node(void);

#endif
