/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:36:33 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/17 17:55:32 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>

# define BUFF_SIZE	2048

int					ft_printf(char const *arg, ...);
int					ft_isaligned(void *p);
int					ft_isblank(int c);
int					ft_isdigit(int c);
int					ft_is32bits(int64_t nb);
int					ft_isprintable(int c);
int					ft_strcmp(char const *s1, char const *s2);
int					ft_strncmp(char const *s1, char const *s2, size_t n);
void				ft_memset(void *s, int c, size_t n);
void				ft_putchar(int c);
void				ft_memcpy(void *dst, void const *src, size_t n);
void				ft_putnbr_light(uint16_t nb);
void				ft_fast_bzero(void *ptr, size_t size);
void				ft_putnstr(char const *s, uint8_t n);
void				ft_putstr_endl(char const *s);
void				ft_putstr(char const *s);
char				*ft_strchr(char const *s, int c);
char				*ft_strrchr(const char *str, int c);
size_t				ft_strlen(char const *str);
char				*ft_strndup(char const *s, size_t n);
char				*ft_strnew(size_t n);
char				*ft_strdup(char const *s);
char				*ft_strsub(char const *s, size_t i, size_t n);
char				*ft_strnjoinfree(char const *s, char const *p, size_t n);
uint8_t				ft_variadic_freeing(unsigned int nb, ...);
int64_t				ft_atoi_parsing(char const **string);
int64_t				ft_min(int64_t a, int64_t b);
uint64_t			ft_abs(int64_t nb);
uint32_t			ft_word_count(char const *s);
int8_t				get_next_line_stdin(char **str, char **s);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char const *s, int fd);
char				*ft_itoa(int n);

#endif
