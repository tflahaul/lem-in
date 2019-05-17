/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_queue.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:46:39 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/17 06:43:03 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_QUEUE_H
# define LEM_IN_QUEUE_H

typedef struct			s_queue
{
	uint32_t			key;
	uint32_t			ant;
	struct s_queue		*next;
}						t_queue;

void					ft_queue_push(t_queue **queue, uint32_t key);
void					ft_queue_append(t_queue **head, uint32_t key);
uint8_t					ft_drain_queue(t_queue **head);
t_queue					*ft_queue_pop(t_queue **queue);

#endif
