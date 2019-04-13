/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:36:33 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/13 14:48:20 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

# define BUFF_SIZE	512

int					ft_isaligned(void *p);
int					ft_isblank(int c);
int					ft_isdigit(int c);
int					ft_isprintable(int c);
void				*ft_memset(void *s, int c, size_t n);
void				ft_putchar(int c);
void				ft_putnstr(char const *s, uint8_t n);
void				ft_putstr_endl(char const *s);
void				ft_putstr(char const *s);
char				*ft_strchr(char const *s, int c);
size_t				ft_strlen(char const *str);
char				*ft_strndup(char const *s, size_t n);
char				*ft_strnew(size_t n);
char				*ft_strdup(char const *s);
char				*ft_strsub(char const *s, unsigned int i, size_t n);
char				*ft_strnjoinfree(char const *s, char const *p, size_t n);
uint8_t				ft_variadic_memory_freeing(unsigned int nb, ...);
uint32_t			ft_word_count(char const *s);
int8_t				get_next_line_stdin(char **s);

#endif