/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_queue.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:46:39 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/18 12:38:24 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_QUEUE_H
# define LEM_IN_QUEUE_H

# include <stdint.h>
# include <stdlib.h>

typedef struct			s_queue
{
	uint64_t			key;
	struct s_queue		*next;
}						t_queue;

typedef struct			s_stack
{
	struct s_queue		*path;
	struct s_stack		*next;
}						t_stack;

void					ft_queue_push(t_queue **queue, uint32_t key);
void					ft_queue_append(t_queue **head, uint32_t key);
uint8_t					ft_drain_queue(t_queue **head);
t_queue					*ft_queue_pop(t_queue **queue);
size_t					ft_queue_size(t_queue *head);

#endif
