/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:50:32 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/22 06:39:02 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_compiler.h>
#include <lem_in_queue.h>
#include <stdlib.h>

inline t_queue			*ft_queue_node(uint32_t key)
{
	t_queue				*node;

	if (UNLIKELY((node = (t_queue *)malloc(sizeof(t_queue))) == NULL))
		return (NULL);
	node->key = key;
	node->ant = 0;
	return (node);
}
