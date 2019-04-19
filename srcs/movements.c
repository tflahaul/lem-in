/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:49:35 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/19 03:29:35 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_stacks.h>

/*static void					ft_print_single_ant(uint16_t nb, const char *name)
{
	ft_putchar('L');
	ft_putnbr_light(nb);
	ft_putchar('-');
	ft_putstr(name);
	ft_putchar(' ');
}*/

/*void						ft_print_movements(t_map *map, void *path, uint64_t nb)
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
}*/
t_stack						*get_max_path_node(t_stack *list, uint32_t nb)
{
	uint32_t				ind;
	t_stack					*tmp;

	tmp = list;
	ind = 0;
	while (++ind < nb)
		tmp = tmp->next;
	return (tmp);
}

void						reset_path(t_stack **list, t_stack *set)
{
	t_stack					*tmp;
	t_queue					*node;
	t_queue					*prev;

	tmp = *list;
	while (tmp != set->next)
	{
		node = tmp->path;
		tmp->path = tmp->path->next;
		tmp->save = tmp->path;
		free(node);
		node = tmp->path;
		while (node)
		{
			prev = node;
			node = node->next;
			if (node)
				node->prev = prev;	
		}
		tmp = tmp->next;
	}
}

void						ft_print_movements(t_map *map, void *list, uint32_t nb)
{
	uint64_t				i;
//	uint64_t				key;
	uint64_t				takes;
	t_stack					*tmp;
	t_stack					*set;

	takes = 1;
	set = get_max_path_node(list, nb);
	reset_path((t_stack **)(&list), set);
	tmp = list;
	i = 1;
	while (takes < map->population / nb + set->size - 2)
	{
		takes++;
		ft_putchar('\n');
	}
	printf("%llu = lines\n", takes - 1);
}
