/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:41:27 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/18 17:47:01 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_queue.h>
#include <lem_in_stacks.h>

int						main(void)
{
	t_map				map;
	uint8_t				visited[MAX_VERTICES];
	t_stack				*list = ft_allocate_stack_memory();

	bzero(&map, sizeof(t_map));
	if (ft_initialize_hashtable(&map) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	ft_memset(visited, 0, MAX_VERTICES);
	if (ft_read_std_input(&map) == EXIT_FAILURE)
	{
		ft_free_hashtable(map.hashtab);
		return (EXIT_FAILURE);
	}
	while (ft_breadth_first_search(&map, visited) == EXIT_SUCCESS)
	{
		ft_push_path_to_stack(&map, &list);
		ft_memset(visited, 0, MAX_VERTICES);
	}
	print_paths(&map, list);
	ft_free_hashtable(map.hashtab);
	ft_free_stacks(&list);
	return (EXIT_SUCCESS);
}
