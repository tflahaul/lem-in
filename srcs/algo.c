/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 20:51:34 by abrunet           #+#    #+#             */
/*   Updated: 2019/04/16 13:11:21 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_bug.h>
#include <lem_in_queue.h>

uint8_t				ft_BFS(t_map *map, uint8_t *visited)
{
	t_vertices	*ptr;
	t_edges		*tmp;
	t_vertices	*tmp_prev;

	ptr = map->hashtab[map->start_index];
	visited[map->start_index] = 1;
	while (ptr != map->hashtab[map->end_index])
	{
		printf("%s\n", ptr->name);
		tmp = ptr->adjc;
		tmp_prev = ptr;
		while (tmp && visited[tmp->key] == 1)
			tmp = tmp->next;
		if (!tmp)
			return (ft_puterror("", DEADEND));
		ptr = map->hashtab[tmp->key];
		visited[ptr->adjc->key] = 1;
		ptr->prev = tmp_prev;		
	}
	while (ptr)
	{
		printf("%s = key\n", ptr->name);
		ptr = ptr->prev;
	}
	return (EXIT_SUCCESS);
}

/*
**	https://fr.wikipedia.org/wiki/Algorithme_de_parcours_en_largeur
*/
uint8_t				ft_test(t_map *map, uint8_t *visited)
{
	uint64_t		key;
	t_edges			*node;
	t_queue			*queue;

	queue = NULL;
	visited[map->start_index] = 1;
	ft_queue_push(&queue, map->start_index);
	while (queue != NULL)
	{
		key = queue->key;
		queue = ft_queue_pop(&queue);
		node = map->hashtab[key]->adjc;
		while (node != NULL)
		{
			if (visited[node->key] == 0)
			{
				visited[node->key] = 1;
				ft_queue_push(&queue, node->key);
			}
			node = node->next;
		}
		printf("step : %llu\n", key);
	}
	return (EXIT_SUCCESS);
}
