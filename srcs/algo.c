/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 20:51:34 by abrunet           #+#    #+#             */
/*   Updated: 2019/04/16 22:14:19 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_bug.h>
#include <lem_in_queue.h>

/*
**	https://fr.wikipedia.org/wiki/Algorithme_de_parcours_en_largeur
*/
uint8_t				ft_BFS(t_map *map, uint8_t *visited)
{
	uint64_t		key;
	t_edges			*node;
	t_queue			*queue;
	t_vertices		*ptr; //	test

	queue = NULL;
	visited[map->start_index] = 1;
	ft_queue_push(&queue, map->start_index);
	while (queue != NULL)
	{
		key = queue->key;
		if (key == map->end_index)
		{
			// test
			ptr = map->hashtab[map->end_index];
			while (ptr)
			{
				printf("%s = key\n", ptr->name);
				ptr = ptr->prev;
			}
			// test
			return (ft_drain_queue(&queue)); // end trouvée
		}
		queue = ft_queue_pop(&queue);
		node = map->hashtab[key]->adjc;
		while (node != NULL)
		{
			if (visited[node->key] == 0)
			{
				visited[node->key] = 1;
				map->hashtab[node->key]->prev = map->hashtab[key];
				ft_queue_push(&queue, node->key);
			}
			node = node->next;
		}
	}
	return (EXIT_FAILURE); // pas trouvée
}
