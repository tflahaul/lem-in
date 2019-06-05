/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 12:41:57 by thflahau          #+#    #+#             */
/*   Updated: 2019/06/05 12:46:27 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_compiler.h>
#include <lem_in_list.h>

inline uint64_t				ft_list_size(t_listhead *head)
{
	uint64_t				size;
	t_listhead				*position;

	size = 1;
	if (UNLIKELY(head->prev == head->next))
		return (size);
	position = head;
	while ((position = position->next) != head)
		++size;
	return (size);
}
