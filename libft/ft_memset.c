/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:54:17 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/10 18:54:18 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void					*ft_memset(void *s, int c, size_t n)
{
	unsigned char		*ptr;
	unsigned char		uchar;

	uchar = (unsigned char)c;
	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = uchar;
	return (s);
}
