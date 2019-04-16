/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 15:41:57 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/16 21:56:00 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_bug.h>
#include <lem_in_compiler.h>

uint8_t					ft_initialize_hashtable(t_map *map)
{
	register uint16_t	idx;

	idx = 0;
	while (idx < MAX_VERTICES)
	{
		if (!(map->hashtab[idx] = (t_vertices *)malloc(sizeof(t_vertices))))
			return (printf("lem-in: %s (hint: %s)\n", MEMERR, MEMFULL));
		map->hashtab[idx]->name = NULL;
		map->hashtab[idx]->prev = NULL;
		map->hashtab[idx]->adjc = NULL;
		idx++;
	}
	return (EXIT_SUCCESS);
}


static inline void		ft_free_adjacency_list(t_edges **head)
{
	t_edges				*ptr;
	t_edges				*node;

	if (head != NULL && *head != NULL)
	{
		node = *head;
		while (node != NULL)
		{
			ptr = node->next;
			free((void *)node);
			node = ptr;
		}
	}
}

void					ft_free_hashtable(t_vertices *hashtab[MAX_VERTICES])
{
	uint16_t			index;

	index = 0;
	while (index < MAX_VERTICES)
	{
		ft_free_adjacency_list(&hashtab[index]->adjc);
		if (hashtab[index]->name != NULL)
			free((void *)hashtab[index]->name);
		free((void *)hashtab[index++]);
	}
}
