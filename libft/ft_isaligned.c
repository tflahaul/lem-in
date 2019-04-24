/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isaligned.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:36:25 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/24 15:47:35 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

inline int						ft_isaligned(void *ptr)
{
	return (((size_t)ptr & (sizeof(ptr) - 1)) == 0);
}
