/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:41:27 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/17 19:15:48 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <lem_in.h>

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
	map.hashtab[map.end_index]->end_paths = malloc(sizeof(t_vertices) * paths);
	ft_memset(map.hashtab[map.end_index]->end_paths, (int)NULL, paths); 
	print_hashtab(&map);
	ft_breadth_first_search(&map, visited, paths);
	ft_free_hashtable(map.hashtab);
	return (EXIT_SUCCESS);
}
