/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 23:15:36 by abrunet           #+#    #+#             */
/*   Updated: 2019/05/17 21:24:30 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_bug.h>
#include <lem_in_compiler.h>

static t_edges		*make_node(uint32_t hashkey)
{
	t_edges			*new;

	if (!(new = (t_edges *)malloc(sizeof(t_edges))))
		return (NULL);
	new->key = hashkey;
	new->way = OPEN;
	new->next = NULL;
	return (new);
}

uint8_t				add_connection(uint32_t hash1, uint32_t hash2, t_map *map)
{
	t_edges			*new;
	t_edges			*tmp;

	if (!(new = make_node(hash2)))
		return (EXIT_FAILURE);
	if (!map->hashtab[hash1]->adjc)
		map->hashtab[hash1]->adjc = new;
	else
	{
		tmp = map->hashtab[hash1]->adjc;
		while (tmp != NULL)
		{
			if (UNLIKELY(tmp->key == hash2))
			{
				free((void *)new);
				return (ft_puterror(map->hashtab[hash2]->name, DUPLINK));
			}
			if (!tmp->next)
			{
				tmp->next = new;
				return (EXIT_SUCCESS);
			}
			tmp = tmp->next;
		}
	}
	return (EXIT_SUCCESS);
}
