/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_stdin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 13:33:54 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/23 17:10:53 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>
#define UNLIKELY(x)			__builtin_expect(!!(x), 0)

int8_t						get_next_line_stdin(char **line)
{
	char					buffer[BUFF_SIZE];
	char					*ptr;
	static char				*string;
	register ssize_t		ret;

	if (!string && !(string = ft_strnew(1)))
		return (-1);
	while (!ft_strchr(string, 0x0a) && (ret = read(0, buffer, BUFF_SIZE)) > 0)
		if (!(string = ft_strnjoinfree(string, buffer, ret)))
			return (-1);
	ret = 0;
	while (string[ret] && string[ret] != 0x0a)
		++ret;
	*line = ft_strndup(string, ret);
	if (string[ret] == 0x0a)
		++ret;
	ptr = string;
	if (UNLIKELY(!(string = ft_strdup(ptr + ret))))
		return (-1);
	free((void *)ptr);
	if (UNLIKELY(ret == 0))
		free((void *)string);
	return (ret > 0 ? 1 : 0);
}
