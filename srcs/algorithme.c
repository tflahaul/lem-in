/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithme.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:27:29 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/18 20:16:18 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_queue.h>
#include <lem_in_stacks.h>
#include <lem_in_compiler.h>

void					ft_algorithme(t_map *map)
{
	t_stack				*list;
	uint8_t				index;
	uint8_t				visited[MAX_VERTICES];

	index = 0;
	list = ft_allocate_stack_memory();
	ft_memset(visited, 0, MAX_VERTICES);
	while (ft_breadth_first_search(map, visited) == EXIT_SUCCESS)
	{
		if (LIKELY(index++ != 1))
			ft_push_path_to_stack(map, &list);
		ft_memset(visited, 0, MAX_VERTICES);
	}
	ft_putchar('\n');
	ft_print_movements(map, list->path, list->size);
	ft_free_stacks(&list);
}
