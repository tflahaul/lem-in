/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:36:32 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/15 17:07:04 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int64_t						ft_atoi_parsing(char const **string)
{
	int8_t					ng;
	int64_t					nb;

	nb = 0;
	ng = 1;
	while (**string == ' ')
		(*string)++;
	if (**string == '-' || **string == '+')
		ng = 44 - *(*string)++;
	if (!ft_isdigit(**string))
		return (INT64_MAX);
	while (**string >= '0' && **string <= '9' && nb <= INT32_MAX)
		nb = nb * 10 + *(*string)++ - 48;
	if (nb > INT32_MAX || (**string && **string != ' '))
		return (INT64_MAX);
	return (nb * ng);
}
