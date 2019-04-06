/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:01:27 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/06 17:54:24 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../include/lme_in_bug.h"
#include "../include/lem_in_compiler.h"

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

/*
**	char *string -> leak
*/
__hot_function
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



__pure_function
static inline int		ft_isprintable(int c)
{
	return (c > 31 && c < 127 ? 1 : 0);
}

__pure_function
static inline int		ft_isblank(int c)
{
	return (c == ' ' || c == '\t' || c == '-' ? 1 : 0);
}

__pure_function
static inline int		ft_isdigit(int c)
{
	return (c >= '0' && c <= '9' ? 1 : 0);
}



void					ft_putchar(int c)
{
	write(1, &c, 1);
}

void					ft_putstr(char const *str)
{
	write(1, str, strlen(str));
}

void					ft_putnstr(char const *str, uint8_t n)
{
	register uint8_t	index;

	index = 0;
	if (!str || unlikely(!str[0]))
		ft_putchar(' ');
	else
	{
		while (likely(index < n) && str[index] != 0)
		{
			ft_putchar(ft_isprintable(str[index]) ? str[index] : '.');
			++index;
		}
	}
}

void				ft_putstr_endl(char const *str)
{
	write(1, str, strlen(str));
	ft_putchar('\n');
}

uint8_t				ft_puterror(char const *str, char const *err)
{
	ft_putstr(C_RED);
	ft_putnstr(str, 20);
	ft_putstr(C_NONE);
	printf("\t<- %s\n", err);
	return (EXIT_FAILURE);
}




uint8_t				ft_parse_verticles(__unused t_graph *map, char const *buffer)
{
	ft_putstr_endl(buffer);
	return (EXIT_SUCCESS);
}

uint8_t				ft_parse_edges(__unused t_graph *map, __unused char const *buffer)
{
	return (EXIT_FAILURE);
}

uint8_t				ft_parse_ants(t_graph *map, char const *buffer)
{
	uint16_t		index;

	index = 0;
	if (!buffer || !buffer[0])
		return (ft_puterror(NULL, EMPTYLINE));
	while (buffer[index])
	{
		if (!ft_isdigit(buffer[index]) && !ft_isblank(buffer[index]))
			return (ft_puterror(buffer, NONNUM));
		++index;
	}
	if ((map->ants = atoi(buffer)) > UINT16_MAX || map->ants == 0)
		return (ft_puterror(buffer, OUTDOMAIN));
	else
		ft_putstr_endl(buffer);
	return (EXIT_SUCCESS);
}




void				ft_handle_start_and_end(char const *buffer)
{
	char			*line;

	get_next_line_stdin(&line);
	ft_putstr_endl(buffer);
	free((void *)line);
}

/*
**	Prend en premier paramètre le nombre de pointeurs à libérer et
**	libère chaque pointeur tour à tour.
*/
uint8_t				ft_variadic_memory_freeing(unsigned int nb, ...)
{
	void			*ptr;
	va_list			args;
	uint8_t			index;

	index = 0;
	va_start(args, nb);
	while (index++ < nb)
		if ((ptr = va_arg(args, void *)) != NULL)
			free(ptr);
	va_end(args);
	return (EXIT_FAILURE);
}

/*
**	Grossss !
*/
uint8_t				ft_funptr_index(char const *buffer)
{
	uint8_t			space_count;
	uint8_t			minus_count;

	space_count = 0;
	minus_count = 0;
	if (buffer == NULL)
		return (0);
	while (*buffer)
	{
		if (*buffer == ' ')
			++space_count;
		else if (*buffer == '-')
			++minus_count;
		++buffer;
	}
	if (minus_count == 1)
		return (1);
	if (space_count == 2)
		return (2);
	return (0);
}

/*
**	Analyse la chaine 'buffer' retournée par get_next_line afin de savoir si
**	on a affaire à une définition de salle, de tube ou du nombre de fourmis
**	avant de dispatcher à la fonction correspondante.
*/
uint8_t				ft_tokenize_buffer(t_graph *graph, char const *buffer)
{
	static uint8_t	index;
	uint8_t			(*funptr[3])(t_graph *, char const *);

	funptr[0] = &ft_parse_ants;
	funptr[1] = &ft_parse_edges;
	funptr[2] = &ft_parse_verticles;
	if (!buffer || !buffer[0])
		return (ft_puterror(NULL, EMPTYLINE));
	if (buffer[0] == '#')
	{
		if (strcmp(buffer, "##start") == 0 || strcmp(buffer, "##end") == 0)
			ft_handle_start_and_end(buffer);
		else
			ft_putstr_endl(buffer);
	}
	else if (index == 0)
		return ((funptr[index++])(graph, buffer));
	else if ((index = ft_funptr_index(buffer)) != 0)
	{
		if ((funptr[index])(graph, buffer) == EXIT_FAILURE)
			return (ft_puterror(buffer, UNKCOMM));
	}
	else
		return (ft_puterror(buffer, UNKCOMM));
	return (EXIT_SUCCESS);
}

/*
**	Fonction de récupération de l'entrée std.
*/
uint8_t				ft_read_std_input(t_graph *graph)
{
	char			*buffer;

	buffer = NULL;
	while (get_next_line_stdin(&buffer) > 0)
	{
		if (ft_tokenize_buffer(graph, buffer) == EXIT_FAILURE)
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
	ft_read_std_input(&graph);
	return (EXIT_SUCCESS);
}
