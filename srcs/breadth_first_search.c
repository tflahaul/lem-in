/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breadth_first_search.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:42:42 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/21 02:32:38 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_algorithm.h>

#include <stdio.h>

t_edges			*look_for_neg_edge(t_edges *edge)
{
	t_edges *tmp;

	tmp = edge;
	while (tmp)
	{
		if (tmp->way == -1)
		{
			tmp->way = 2;
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (tmp);
}

void			check_for_doubles(t_map *map)
{
	t_edges			*path;
	t_vertices		*node;
	t_vertices		*prev;
	t_vertices		*tmp;
	int				i;
	int				j;

	i = 0;
	node = map->hashtab[map->end_index];
	tmp = map->hashtab[map->end_index];
	prev = node;
	while ((node = node->prev))
	{		
		i++;
		tmp = map->hashtab[map->end_index];
		j = 0;
		while (tmp != node)
		{
			tmp = tmp->prev;
			++j;
		}
		if (j != i)
		{
			path = map->hashtab[prev->key]->adjc;
			while (path != NULL)
			{
				if (path->key == node->key)
				{
					path->way = closed_way;
					break;
				}
				path = path->next;
			}
			path = map->hashtab[node->key]->adjc;
			while (path != NULL)
			{
				if (path->key == prev->key)
				{
					path->way = closed_way;
					break;
				}
				path = path->next;
			}
			break;
		}
		prev = node;
	}
	prev->prev = NULL;

}

uint8_t				neg_edge_bfs(t_map *map, t_queue **queue, uint8_t *visited, uint32_t key)
{
	t_edges			*v;

	while (*queue != NULL)
	{
		key = (*queue)->key;
		if (key == map->end_index)
			return (ft_drain_queue(queue));
		*queue = ft_queue_pop(queue);
		v = map->hashtab[key]->adjc;
		if ((v = look_for_neg_edge(v)) != NULL && visited[v->key] != 1)
		{
			visited[key] = 0;
			visited[v->key] = 1;
			map->hashtab[v->key]->prev = map->hashtab[key];
			ft_queue_append(queue, v->key);
			if ((neg_edge_bfs(map, queue, visited, v->key)) == EXIT_FAILURE)
				return (neg_edge_bfs(map, queue, visited, key));
			else	
				return (EXIT_SUCCESS);
		}
		v = map->hashtab[key]->adjc;
		while (v != NULL)
		{
			if (v->way == open_way && !visited[v->key] && (visited[v->key] = 1))
			{
				map->hashtab[v->key]->prev = map->hashtab[key];
				ft_queue_append(queue, v->key);
			}
			v = v->next;
		}	
	}
	return (EXIT_FAILURE);
}
#include <stdio.h>
void					print_graph(t_map *map)
{
	register uint16_t	index = 0;

	while (index < MAX_VERTICES)
	{
		if (map->hashtab[index]->name != NULL)
		{
			printf("%s\t", map->hashtab[index]->name);
			t_edges *ptr = map->hashtab[index]->adjc;
			while (ptr != NULL)
			{
				printf("  -> %s(%i)", map->hashtab[ptr->key]->name, ptr->way);
				ptr = ptr->next;
			}
			printf("\n");
		}
		index++;
	}
}

uint8_t			ft_bfs(t_map *map, uint8_t *visited, t_stack **list)
{
	uint32_t		key;
	t_queue			*queue;

	key = map->start_index;
	queue = NULL;
	visited[key] = visited_node;
	ft_queue_push(&queue, key);
	if (neg_edge_bfs(map, &queue, visited, key) == EXIT_SUCCESS)
	{
		printf("#here\n");
		check_for_doubles(map);
		ft_push_path_to_stack(map, list);
		ft_fast_bzero(visited, MAX_VERTICES);
		ft_make_directed(map);
		return (EXIT_SUCCESS);

	}
//	printf("5\n");
	ft_update_graph(map, *list);
	return (EXIT_FAILURE);
}
/*
 ** Basic BFS algorithm, no prioritizing of vertices to visit.
 */

uint8_t				ft_simple_bfs(t_map *map, uint8_t *visited)
{
	uint32_t		key;
	t_edges			*v;
	t_queue			*queue;

	queue = NULL;
	visited[map->start_index] = visited_node;
	ft_queue_push(&queue, map->start_index);
	while (queue != NULL)
	{
		key = queue->key;
		if (key == map->end_index)
			return (ft_drain_queue(&queue));
		queue = ft_queue_pop(&queue);
		v = map->hashtab[key]->adjc;
		while (v != NULL)
		{
			if (v->way == open_way && !visited[v->key] && (visited[v->key] = 1))
			{
				map->hashtab[v->key]->prev = map->hashtab[key];
				ft_queue_append(&queue, v->key);
			}
			v = v->next;
		}
	}
	return (EXIT_FAILURE);
}
