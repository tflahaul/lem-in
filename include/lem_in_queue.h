/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_queue.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:46:39 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/21 15:30:02 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_QUEUE_H
# define LEM_IN_QUEUE_H

# include <stdint.h>
# include <lem_in_list.h>

typedef struct			s_queue
{
	t_listhead			list;
	uint32_t			key;
	uint32_t			ant;
}						t_queue;

t_queue					*ft_queue_node(uint32_t key);

void					ft_queue_push(t_queue **queue, uint32_t key);
void					ft_queue_append(t_queue **head, uint32_t key);
uint8_t					ft_drain_queue(t_queue **head);
t_queue					*ft_queue_pop(t_queue **queue);
t_queue					*list_last_node(t_queue *head);

#endif
