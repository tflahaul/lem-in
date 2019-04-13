/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 15:41:57 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/13 16:58:34 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../include/lem_in_bug.h"
#include "../include/lem_in_compiler.h"

uint8_t					ft_initialize_hashtable(t_map *map)
{
	register uint16_t	idx;

	idx = 0;
	while (idx < MAX_VERTICLES)
	{
		if (!(map->hashtab[idx] = (t_verticles *)malloc(sizeof(t_verticles))))
			return (printf("lem-in: %s (hint: %s)\n", MEMERR, MEMFULL));
		map->hashtab[idx]->name = NULL;
		map->hashtab[idx]->next = NULL;
		++idx;
	}
	return (EXIT_SUCCESS);
}

static inline void		ft_free_adjacency_list(t_verticles **head)
{
	t_verticles			*node;
	t_verticles			*ptr;

	if (head != NULL && *head != NULL)
	{
		node = *head;
		while (node != NULL)
		{
			if (node->name != NULL)
				free((void *)node->name);
			ptr = node->next;
			free((void *)node);
			node = ptr;
		}
	}
}

void					ft_free_hashtable(t_verticles *hashtab[MAX_VERTICLES])
{
	uint16_t			index;

	index = 0;
	while (index < MAX_VERTICLES)
		ft_free_adjacency_list(&hashtab[index++]);
}
