/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:41:27 by thflahau          #+#    #+#             */
/*   Updated: 2019/06/20 00:03:33 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int						main(__attribute__((unused)) int ac, char const **av)
{
	t_map				map;

	ft_memset(&map, 0, sizeof(t_map));
	if (ft_initialize_hashtable(&map) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (av[1] && ft_strcmp("-v", av[1]) == 0)
		map.visual |= VISUAL;
	if (ft_read_std_input(&map) == EXIT_FAILURE)
		return (ft_free_hashtable(map.hashtab));
	if (ft_is_valid_for_algorithm(&map) == EXIT_SUCCESS)
		ft_algorithm(&map);
	return (ft_free_hashtable(map.hashtab));
}
