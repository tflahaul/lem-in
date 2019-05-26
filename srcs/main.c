/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:41:27 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/26 15:17:54 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int						main(int argc, char const **argv)
{
	t_map				map;

	ft_fast_bzero(&map, sizeof(t_map));
	if (ft_initialize_hashtable(&map) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (argc > 1 && ft_strcmp("-v", argv[1]) == 0)
		map.visual |= VISUAL;
	if (ft_read_std_input(&map) == EXIT_FAILURE && map.vertices < 2)
		return ((int)ft_free_hashtable(map.hashtab));
	ft_algorithm(&map);
	return ((int)ft_free_hashtable(map.hashtab));
}
