/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:41:27 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/16 01:11:12 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int						main(int argc, char **argv)
{
	t_map				map;

	ft_fast_bzero(&map, sizeof(t_map));
	if (ft_initialize_hashtable(&map) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (argc > 1 && !(ft_strcmp("-v", argv[1])))
		map.visual |= VISUAL;
	if (ft_read_std_input(&map) == EXIT_SUCCESS)
		ft_algorithm(&map);
	ft_free_hashtable(map.hashtab);
	return (EXIT_SUCCESS);
}
