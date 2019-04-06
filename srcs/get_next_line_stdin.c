/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_stdin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 13:33:54 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/06 14:25:12 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

int8_t						get_next_line_stdin(char **line)
{
	char					buffer[BUFF_SIZE];
	char					*ptr;
	static char				*string;
	register ssize_t		ret;


	if (!string && !(string = ft_strnew(1)))
		return (-1);
	while (!strchr(string, 0x0a) && (ret = read(0, buffer, BUFF_SIZE)) > 0)
		if (!(string = ft_strnjoinfree(string, buffer, ret)))
			return (-1);
	ret = 0;
	while (string[ret] && string[ret] != 0x0a)
		++ret;
	*line = strndup(string, ret);
	if (string[ret] == 0x0a)
		++ret;
	ptr = string;
	if (!(string = strdup(ptr + ret)))
		return (-1);
	free((void *)ptr);
	return (ret > 0 ? 1 : 0);
}
