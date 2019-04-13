/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:41:27 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/13 17:59:30 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/lem_in.h"

int						main(void)
{
	t_map				map;

	bzero(&map, sizeof(t_map));
	if (ft_initialize_hashtable(&map) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	ft_read_std_input(&map);
	for (int i = 0; i < 50; ++i)
		printf("%s\n", map.hashtab[i]->name);
	ft_free_hashtable(map.hashtab);
	return (EXIT_SUCCESS);
}
