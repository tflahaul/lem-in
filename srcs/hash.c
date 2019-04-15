/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:19:40 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/15 16:20:38 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_hash.h>
#include <lem_in.h>

uint64_t				hash(const char *s)
{
	uint64_t			h;

	h = 0;
	while (*s != '\0')
	{
		h = h * MULTIPLIER + *s;
		s++;
	}
	return (h % MAX_VERTICES);
}
