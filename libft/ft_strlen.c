/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:54:51 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/10 19:01:23 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t					ft_strlen(char const *str)
{
	char				*ptr;

	ptr = (char *)str;
	while (*ptr)
		ptr++;
	return (ptr - str);
}
