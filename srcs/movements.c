/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:49:35 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/18 18:50:17 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_queue.h>

static void					ft_print_single_ant(uint16_t nb)
{
	ft_putchar('L');
	ft_putnbr_light(nb);
	ft_putchar('-');
}

void						ft_print_movements(t_map *map, void *path, uint64_t nb)
{
	uint64_t				i;
	uint64_t				n;
	uint64_t				ants;
	t_queue					*node;

	ants = 1;
	node = (t_queue *)path;
	while (ants <= map->population + nb)
	{
		i = 1;
		n = ants;
		while (i <= ants)
		{
			i++;
			node = (t_queue *)path;
			while (node != NULL && (n-- > i))
				node = node->next;
			n = ants;
			if (node != NULL && i <= map->population)
			{
				ft_print_single_ant(i);
				ft_putstr(map->hashtab[node->key]->name);
				ft_putchar(' ');
			}
		}
		ants++;
		if (ants <= map->population + nb)
			ft_putchar('\n');
	}
}
