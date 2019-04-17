/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 20:51:34 by abrunet           #+#    #+#             */
/*   Updated: 2019/04/17 19:18:52 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_bug.h>
#include <lem_in_queue.h>

static inline uint8_t	ft_backtrack(t_vertices *ptr, t_queue **queue, uint32_t paths)
{
	uint32_t	ind;
	t_vertices	*tmp;
	
	ind = 0;
	while (ind < paths)
	{
		printf("%s = key\n", ptr->name);
		tmp = &ptr->end_paths[ind];
		while (tmp != NULL)
		{
			printf("%s = key\n", tmp->name);
			tmp = tmp->prev;
		}
		printf("\n");
		ind++;
	}
	return (ft_drain_queue(queue));
}

uint8_t					add_path_to_end(t_vertices *ptr, t_vertices *end, uint32_t paths)
{
	static uint32_t		ind;

	end->end_paths[ind] = *ptr;
	ind++;
	if (ind > paths)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);

}

uint8_t					ft_breadth_first_search(t_map *map, uint8_t *visited, uint32_t paths)
{
	uint64_t			key;
	t_edges				*node;
	t_queue				*queue;

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
			if (visited[node->key] == 0 && (visited[node->key] = 1))
			{
				map->hashtab[node->key]->prev = map->hashtab[key];
				ft_queue_push(&queue, node->key);
			}
			if (node->next && node->next->key == map->end_index)
				if (add_path_to_end(map->hashtab[key], map->hashtab[map->end_index], paths) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			node = node->next;
		}
	}
	return (ft_backtrack(map->hashtab[map->end_index], &queue, paths));
}
