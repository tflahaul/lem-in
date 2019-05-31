/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 17:19:26 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/24 14:07:47 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <lem_in_stacks.h>
#include "../libft/libft.h"

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
