/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:41:27 by thflahau          #+#    #+#             */
/*   Updated: 2019/06/16 17:00:52 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int						main(int argc, char const **argv)
{
	t_map				map;

	ft_memset(&map, 0, sizeof(t_map));
	if (ft_initialize_hashtable(&map) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (argc > 1)
	{
		if (ft_strcmp("-v", argv[1]) == 0)
			map.visual |= VISUAL;
		else
		{
			ft_print_usage(argv[0]);
			return (ft_free_hashtable(map.hashtab));
		}
	}
	if (ft_read_std_input(&map) == EXIT_FAILURE && map.vertices < 2)
		return (ft_free_hashtable(map.hashtab));
	else if (map.start_index && map.end_index)
		ft_algorithm(&map);
	return (ft_free_hashtable(map.hashtab));
}
