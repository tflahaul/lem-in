/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 17:19:26 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/17 00:30:45 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <lem_in_stacks.h>

inline uint64_t				ft_abs(int64_t nb)
{
	return ((nb < 0) ? -nb : nb);
}

uint64_t					ft_list_size(t_stack *list)
{
	uint64_t				length;

	length = 0;
	while (list != NULL && ++length)
		list = list->next;
	return (length);
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
