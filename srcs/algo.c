/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 20:51:34 by abrunet           #+#    #+#             */
/*   Updated: 2019/04/16 00:03:33 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_bug.h>

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
