/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 16:05:49 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/24 13:32:54 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_stacks.h>
#include <lem_in_compiler.h>
#include "../libft/libft.h"

inline t_stack				*ft_stack_node(void)
{
	t_stack					*head;

	if (UNLIKELY((head = (t_stack *)malloc(sizeof(t_stack))) == NULL))
		return (NULL);
	ft_memset(head, 0, sizeof(t_stack));
	return (head);
}
