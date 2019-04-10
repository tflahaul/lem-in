/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 19:10:54 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/10 19:11:07 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char					*ft_strchr(char const *s, int ch)
{
	uint32_t			i;

	i = 0;
	if (s != NULL)
		while (s[i])
			if (s[i++] == (unsigned char)ch)
				return ((char *)s);
	return (ch ? NULL : (char *)s);
}
