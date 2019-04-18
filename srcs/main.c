/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:41:27 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/18 14:43:50 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <lem_in.h>
#include <lem_in_queue.h>

static inline uint16_t	ft_magic_formula(t_map *map, t_queue *q, uint8_t nb)
{
	return ((map->population / nb) + ft_queue_size(q));
}

int32_t					ft_get_number_of_steps(t_map *map, t_stack *list, uint16_t nb)
{
	int32_t				steps;
	uint16_t			index;

	steps = 0;
	index = 0;
	while (list != NULL && index++ < nb)
	{
		if (list->path && steps == 0)
			steps = ft_magic_formula(map, list->path, nb);
		else
			steps += ABS(steps - ft_magic_formula(map, list->path, nb));
		list = list->next;
	}
	return (ABS(steps));
}

void					ft_select_best_path(t_map *map, t_stack *list)
{
	uint16_t			nb;
	uint16_t			tmp;
	uint16_t			min;

	nb = 1;
	list = list->next;
	min = ft_get_number_of_steps(map, list, nb++);
	list = list->next->next;
	while (list != NULL)
	{
		tmp = 0;
		min = MIN(min, ft_get_number_of_steps(map, list, nb));
		nb++;
		while (tmp++ < nb && list != NULL)
			list = list->next;
	}
	printf("\nBEST PATH TAKES %d STEPS\n", min);
}

t_stack					*ft_initialize_path_list(void)
{
	t_stack				*list;

	if ((list = (t_stack *)malloc(sizeof(t_stack))) == NULL)
		return (NULL);
	list->path = NULL;
	list->next = NULL;
	return (list);
}

t_stack					*ft_stack_append(t_stack **head)
{
	t_stack				*tmp;
	t_stack				*node;

	if ((node = ft_initialize_path_list()) != NULL)
	{
		tmp = *head;
		if (tmp == NULL)
			*head = node;
		else
		{
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = node;
		}
	}
	return (node);
}

uint8_t					ft_add_path_to_list(t_map *map, t_stack *list)
{
	t_stack				*path;
	t_vertices			*node;

	path = ft_stack_append(&list);
	while (list != NULL && list != path)
		list = list->next;
	node = map->hashtab[map->end_index];
	while (node != NULL)
	{
		ft_queue_push(&list->path, node->key);
		node = node->prev;
	}
	return (EXIT_SUCCESS);
}
/*
void					print_path(t_map *map)
{
	static uint8_t		ind;
	t_vertices			*tmp;
	t_vertices			*ptr;

	ptr = map->hashtab[map->end_index];
	tmp = &ptr->end_paths[ind];
	printf("%s\n", ptr->name);
	while (tmp)
	{
		printf("%s\n", tmp->name);
		tmp = tmp->prev;
	}
	ind++;
}
*/
int						main(void)
{
	t_map				map;
	t_stack				*list;
	uint32_t			paths;
	uint8_t				visited[MAX_VERTICES];

	bzero(&map, sizeof(t_map));
	if (ft_initialize_hashtable(&map) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	ft_memset(visited, 0, MAX_VERTICES);
	if (ft_read_std_input(&map, &paths) == EXIT_FAILURE)
	{
		ft_free_hashtable(map.hashtab);
		return (EXIT_FAILURE);
	}
	list = ft_initialize_path_list();
	while (ft_breadth_first_search(&map, visited) == EXIT_SUCCESS)
	{
		ft_add_path_to_list(&map, list);
		ft_memset(visited, 0, MAX_VERTICES);
	}
	ft_select_best_path(&map, list);
	ft_free_hashtable(map.hashtab);
	return (EXIT_SUCCESS);
}
