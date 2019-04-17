/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:41:27 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/18 00:25:05 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <lem_in.h>
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

int						main(void)
{
	t_map				map;
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
	map.hashtab[map.end_index]->end_paths = malloc(sizeof(t_vertices) * (paths + 3));
	ft_memset(map.hashtab[map.end_index]->end_paths, (int)NULL, paths); 
	print_hashtab(&map);
	while (ft_breadth_first_search(&map, visited) == EXIT_SUCCESS)
	{	
		printf("\n==== PATH =====\n");
		print_path(&map);
		print_hashtab(&map);
		ft_memset(visited, 0, MAX_VERTICES);
	}
	ft_free_hashtable(map.hashtab);
	return (EXIT_SUCCESS);
}
