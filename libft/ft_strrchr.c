/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 16:32:16 by abrunet           #+#    #+#             */
/*   Updated: 2019/04/17 20:43:01 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strrchr(const char *str, int c)
{
	char			*tmp;

	tmp = NULL;
	while (*str)
	{
		if (*str == c)
			tmp = (char *)str;
		str++;
	}
	if (*str == c)
		tmp = (char *)str;
	return (tmp);
}
