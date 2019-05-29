/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_queue.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:46:39 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/26 12:50:30 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_QUEUE_H
# define LEM_IN_QUEUE_H

# include <stdint.h>

# ifndef LEM_IN_LIST_H
#  include <lem_in_list.h>
# endif

typedef struct			s_queue
{
	t_listhead			list;
	uint32_t			key;
	uint32_t			ant;
}						t_queue;

t_queue					*ft_queue_node(uint32_t key);
t_queue					*ft_queue_entry(t_listhead *ptr);

#endif
