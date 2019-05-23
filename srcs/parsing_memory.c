/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 12:20:22 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/23 12:43:15 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_list.h>
#include <lem_in_parsing.h>
#include <lem_in_compiler.h>
#include <stdlib.h>
#include "../libft/libft.h"

inline t_input			*ft_make_node(char *buffer)
{
	t_input				*node;

	if (UNLIKELY((node = (t_input *)malloc(sizeof(t_input))) == NULL))
		return (NULL);
	node->buffer = buffer;
	return (node);
}

inline uint8_t			ft_parsing_panic(t_listhead *head, char const *str)
{
	t_input				*ptr;
	t_listhead			*node;
	t_listhead			*next;

	if (LIKELY(str != NULL))
		free((void *)str);
	node = head->next;
	next = node->next;
	while (node != head)
	{
		if (LIKELY((ptr = LIST_ENTRY(node, t_input, list)) != NULL))
		{
			free((void *)ptr->buffer);
			free((void *)ptr);
		}
		node = next;
		next = node->next;
	}
	return (EXIT_FAILURE);
}

inline uint8_t			ft_free_lines(t_listhead *head)
{
	t_listhead			*node;
	t_listhead			*next;

	node = head->next;
	next = node->next;
	while (node != head)
	{
		free((void *)LIST_ENTRY(node, t_input, list));
		node = next;
		next = node->next;
	}
	return (EXIT_SUCCESS);
}

inline void				ft_safe_print_and_free(t_listhead *head)
{
	t_input				*ptr;
	t_listhead			*node;
	t_listhead			*next;

	node = head->next;
	next = node->next;
	while (node != head)
	{
		if (LIKELY((ptr = LIST_ENTRY(node, t_input, list)) != NULL))
		{
			ft_putstr_endl_free(ptr->buffer);
			free((void *)ptr);
		}
		node = next;
		next = node->next;
	}
}
