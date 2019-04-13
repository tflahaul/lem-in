/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 13:49:18 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/13 14:39:39 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char				*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*ptr;

	if (!s)
		return (NULL);
	if (!(ptr = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = s[i + start];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}
