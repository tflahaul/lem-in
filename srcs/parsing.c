/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:01:27 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/05 17:03:27 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

void				*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	uchar;

	uchar = (unsigned char)c;
	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = uchar;
	return (s);
}

char					*ft_strnew(size_t size)
{
	char				*str;

	if (!(str = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_memset(str, 0, size + 1);
	return (str);
}

char			*ft_strnjoinfree(char const *s1, char const *s2, size_t n)
{
	char		*str;
	char		*ptr;
	char		*tmp;

	if (!s1 || !s2)
		return (NULL);
	tmp = (char *)s1;
	if (!(str = ft_strnew(strlen(s1) + n + 1)))
		return (NULL);
	ptr = str;
	while (*s1)
		*str++ = *s1++;
	while (n-- > 0 && *s2)
		*str++ = *s2++;
	*str = 0;
	free((void *)tmp);
	return (ptr);
}

static int8_t			get_next_line_stdin(char **line)
{
	char				buffer[BUFF_SIZE];
	char				*ptr;
	static char			*string;
	register ssize_t	ret;


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

void					ft_putchar(int c)
{
	write(1, &c, 1);
}

void					ft_putstr(char const *str)
{
	write(1, str, strlen(str));
}

void					ft_putstr_endl(char const *str)
{
	write(1, str, strlen(str));
	ft_putchar('\n');
}

uint8_t					ft_puterror(char const *str, char const *err)
{
	ft_putstr(C_RED);
	ft_putstr(str);
	ft_putstr(C_NONE);
	printf("\t<- %s\n", err);
	return (EXIT_FAILURE);
}

int						ft_isblank(int c)
{
	return (c == ' ' || c == '\t' || c == '-' || c == '+' ? 1 : 0);
}

int						ft_isdigit(int c)
{
	return (c >= '0' && c <= '9' ? 1 : 0);
}

uint8_t					ft_parse_rooms(t_graph *map, char const *buffer)
{
	map->rooms = *buffer;
	ft_putstr_endl(buffer);
	return (EXIT_SUCCESS);
}

uint8_t					ft_parse_connections(t_graph *map, char const *buffer)
{
	map->connections = *buffer;
	ft_putstr_endl(buffer);
	return (EXIT_SUCCESS);
}

uint8_t					ft_parse_ants(t_graph *map, char const *buffer)
{
	uint16_t			index;

	index = 0;
	while (buffer[index])
	{
		if (!ft_isdigit(buffer[index]) && !ft_isblank(buffer[index]))
			return (ft_puterror(buffer, NOTNUM));
		++index;
	}
	if ((map->ants = atoi(buffer)) > UINT16_MAX || map->ants == 0)
		return (ft_puterror(buffer, OUTDOMAIN));
	else
		ft_putstr_endl(buffer);
	return (EXIT_SUCCESS);
}

/*
**	Prend en premier paramètre le nombre de pointeurs à libérer et
**	libère chaque pointeur tour à tour.
*/
uint8_t					ft_variadic_memory_freeing(unsigned int nb, ...)
{
	void				*ptr;
	va_list				args;
	uint8_t				index;

	index = 0;
	va_start(args, nb);
	while (index++ < nb)
		if ((ptr = va_arg(args, void *)) != NULL)
			free(ptr);
	va_end(args);
	return (EXIT_FAILURE);
}

/*
**	Fonction de parsing principale.
*/
uint8_t					ft_parse_std_input(t_graph *map)
{
	char				*buffer;
	register uint8_t	index;
	uint8_t				(*funptr[3])(t_graph *, char const *);

	index = 0;
	funptr[0] = &ft_parse_ants;
	funptr[1] = &ft_parse_rooms;
	funptr[2] = &ft_parse_connections;
	while (get_next_line_stdin(&buffer) > 0)
	{
		if (buffer[0] == '#')
		{
			if (strcmp(buffer, "##start") == 0)
				index = 0;
			else if (strcmp(buffer, "##end") == 0)
				index = 1;
			else
				ft_putstr_endl(buffer);
		}
		else if ((funptr[index])(map, buffer) == EXIT_FAILURE)
			return (ft_variadic_memory_freeing(1, (void *)buffer));
		free((void *)buffer);
	}
	free((void *)buffer);
	return (EXIT_SUCCESS);
}

int						main(void)
{
	t_graph				graph;

	bzero(&graph, sizeof(graph));
	ft_parse_std_input(&graph);
	printf("\n\nANTS = [%u]\n", graph.ants);
	return (EXIT_SUCCESS);
}
