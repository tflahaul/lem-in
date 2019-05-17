/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 17:19:26 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/17 18:22:14 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <lem_in_stacks.h>

inline t_queue				*list_last_node(t_queue *head)
{
	if (head != NULL)
		while (head->next != NULL)
			head = head->next;
	return (head);
}

uint64_t					ft_list_size(t_stack *list)
{
	uint64_t				length;

	length = 0;
	while (list != NULL && ++length)
		list = list->next;
	return (length);
}

inline uint8_t				ft_path_checker(t_map *map, t_queue *node)
{
	if (node->key == map->start_index && node->next->key == map->end_index)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

inline void					ft_print_colored_ant(uint32_t nb, char const *name)
{
	char const				*colors[7] = {"\033[38;5;75m", "\033[32m",
							"\033[34m", "\033[38;5;150m", "\033[35m",
							"\033[36m", "\033[38;5;206m"};

	ft_putstr(colors[(nb >> 0x10u) - 1]);
	ft_putchar('L');
	ft_putnbr_light((nb | (nb << 0x10u)));
	ft_putstr("\033[0m");
	ft_putchar('-');
	ft_putstr(name);
	ft_putchar(' ');
}
