/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 15:41:57 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/21 13:21:42 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_bug.h>
#include <lem_in_compiler.h>

uint8_t					ft_initialize_hashtable(t_map *map)
{
	register uint16_t	idx;

	idx = 0;
	if (UNLIKELY(MAX_VERTICES > UINT16_MAX))
		return (ft_printf(C_RED"lem-in: %s"C_NONE, EMAXVERT));
	while (idx < MAX_VERTICES)
	{
		if (!(map->hashtab[idx] = (t_vertices *)malloc(sizeof(t_vertices))))
			return (ft_printf("lem-in: %s (hint: %s)\n", MEMERR, MEMFULL));
		ft_memset(map->hashtab[idx], 0, sizeof(t_vertices));
		idx++;
	}
	return (EXIT_SUCCESS);
}

static void				ft_free_adjacency_list(t_edges **head)
{
	t_edges				*ptr;
	t_edges				*node;

	if (LIKELY(head != NULL && *head != NULL))
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
	register uint16_t	index;

	index = 0;
	while (index < MAX_VERTICES)
	{
		ft_free_adjacency_list(&hashtab[index]->adjc);
		if (LIKELY(hashtab[index]->name != NULL))
			free((void *)hashtab[index]->name);
		free((void *)hashtab[index++]);
	}
}
