/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:04:23 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/13 18:07:06 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdio.h>
# include <libft.h>
# include <string.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdarg.h>

# define MAX_VERTICLES	4096

typedef struct			s_verticles
{
	int32_t				x;
	int32_t				y;
	char const			*name;
	struct s_verticles	*next;
}						t_verticles;

typedef struct			s_map
{
	uint32_t			population;
	uint32_t			start_edges;
	uint32_t			end_edges;
	uint16_t			verticles;
	uint16_t			edges;
	struct s_verticles	*hashtab[MAX_VERTICLES];
}						t_map;

uint8_t					ft_puterror(char const *str, char const *err);

/*
**	Parsing
*/
uint8_t					ft_read_std_input(t_map *map);
uint8_t					ft_parse_verticles(t_map *node, char const *buffer);

/*
**	Memory
*/
void					ft_free_hashtable(t_verticles *hashtab[MAX_VERTICLES]);
uint8_t					ft_initialize_hashtable(t_map *map);

#endif
