/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fast_strdup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 19:50:54 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/17 20:24:49 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char					*ft_fast_strdup(char const *str)
{
	char				*tmp;
	char				*ptr;
	uint64_t			size;
	uint32_t			*step_str;
	uint32_t			*step_ptr;

	size = ft_strlen(str);
	if ((ptr = (char *)malloc(sizeof(char) * (size + 1))) == NULL)
		return (NULL);
	tmp = ptr;
	step_str = (uint32_t *)str;
	step_ptr = (uint32_t *)ptr;
	while (size-- && (!ft_isaligned((void *)ptr) || !ft_isaligned((void *)str)))
		*ptr++ = *str++;
	while (size > sizeof(uint32_t))
	{
		*step_ptr++ = *step_str++;
		size -= sizeof(uint32_t);
	}
	ptr = (char *)step_ptr;
	str = (char *)step_str;
	while (size-- > 0)
		*ptr++ = *str++;
	*ptr = 0;
	return (tmp);
}
