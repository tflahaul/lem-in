/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:41:27 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/15 14:49:51 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <lem_in.h>

int						main(void)
{
	t_map				map;
	uint32_t			paths;

	bzero(&map, sizeof(t_map));
	if (ft_initialize_hashtable(&map) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (ft_read_std_input(&map, &paths) == EXIT_FAILURE)
	{
		ft_free_hashtable(map.hashtab);
		return (EXIT_FAILURE);
	}
//	for (int i = 0; i < MAX_VERTICES; i += 4)
//	{
//		printf("%s\t%s\t", map.hashtab[i]->name, map.hashtab[i + 1]->name);
//		printf("%s\t%s\n", map.hashtab[i + 2]->name, map.hashtab[i + 3]->name);
//	}
//	print_hashtab(&map);
	ft_free_hashtable(map.hashtab);
	return (EXIT_SUCCESS);
}
