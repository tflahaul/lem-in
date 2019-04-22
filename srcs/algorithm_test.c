/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 09:59:25 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/22 12:14:48 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Je teste juste des trucs dans ce fichier! Le vrai algo reste dans
**	algorithm.c!
*/

#include <lem_in.h>
#include <lem_in_stacks.h>

void					print_paths(t_map *map, t_stack *list);

/*
**	Regarde si le dernier chemin trouvé est passé par des bouts de
**	chemins dirigés et bloque définitivement ces portions de chemins
**	si c'est le cas.
*/

void					ft_check_for_overlaps(t_map *map, t_stack *stacks)
{
	t_vertices			*node;

	while (stacks->next != NULL)
		stacks = stacks->next;
	node = map->hashtab[map->end_index];
	while ((node = node->prev) != NULL)
	{
		printf("lel\n");
//		if ()
//			node->adjc->way = REMOVED;
	}
}

/*
**	Dirige le dernier chemin trouvé et met les pointeurs `prev` à null
**	dans le même temps. (à voir plus tard si c'est vraiment utile)
*/

void					ft_make_directed(t_map *map)
{
	uint64_t			key;
	t_edges				*ptr;
	t_vertices			*tmp;
	t_vertices			*node;

	key = map->end_index;
	node = map->hashtab[map->end_index];
	while (node != NULL)
	{
		ptr = node->adjc;
		while (ptr != NULL)
		{
			if (ptr->key == key)
				ptr->way = CLOSED;
			ptr = ptr->next;
		}
		key = node->key;
		tmp = node->prev;
		node->prev = NULL;
		node = tmp;
	}
}

/*
**	Trouve uniquement le chemin le plus court, ne fais rien d'autre.
*/

uint8_t					ft_breadth_first_search(t_map *map, uint8_t *visited)
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
		if (key == map->end_index && ft_drain_queue(&queue) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
		queue = ft_queue_pop(&queue);
		node = map->hashtab[key]->adjc;
		while (node != NULL)
		{
			if (node->way == OPEN && !visited[node->key])
			{
				visited[node->key] = 1;
				map->hashtab[node->key]->prev = map->hashtab[key];
				ft_queue_append(&queue, node->key);
			}
			node = node->next;
		}
	}
	ft_drain_queue(&queue);
	return (EXIT_FAILURE);
}

void					ft_algorithm(t_map *map)
{
	t_stack				*list;
	uint8_t				visited[MAX_VERTICES];

	list = ft_allocate_stack_memory();
	ft_memset(visited, 0, MAX_VERTICES);
	while (ft_breadth_first_search(map, visited) == EXIT_SUCCESS)
	{
		ft_memset(visited, 0, MAX_VERTICES);
//		ft_push_path_to_stack(map, &list);
		ft_make_directed(map);
		if (ft_breadth_first_search(map, visited) == EXIT_SUCCESS)
			ft_check_for_overlaps(map, list);
		else	// Plus de chemins possibles
			break ;
	}
//	print_paths(map, list);
	ft_free_stacks(&list);
}
