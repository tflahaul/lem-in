/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 12:10:11 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/14 12:17:08 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#define UNLIKELY(x)		__builtin_expect(!!(x), 0)

int64_t					ft_atoi_light(char const *str)
{
	uint32_t			nb;
	uint32_t			ng;

	nb = 0;
	ng = 1;
	if (*str == 45)
		ng = *str++ - 46;
	while (*str > 47 && *str < 58)
	{
		nb = nb * 10 + *str++ - 48;
		if (UNLIKELY(nb > INT32_MAX))
			return (UINT16_MAX + 1);
	}
	return (nb * ng);
}
