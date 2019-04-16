/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_queue.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:46:39 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/16 21:32:44 by abrunet          ###   ########.fr       */
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

void					ft_queue_push(t_queue **queue, uint64_t key);
uint8_t					ft_drain_queue(t_queue **head);
t_queue					*ft_queue_pop(t_queue **queue);

#endif
