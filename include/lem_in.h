/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:04:23 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/15 17:05:38 by thflahau         ###   ########.fr       */
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

# define MAX_VERTICES	8192

typedef struct			s_edges
{
	uint64_t			key;
	struct s_edges		*next;
}						t_edges;

typedef struct			s_vertices
{
	int32_t				x;
	int32_t				y;
	char const			*name;
	struct s_edges		*adjc;
}						t_vertices;

typedef struct			s_map
{
	uint64_t			start_index;
	uint64_t			end_index;
	uint32_t			population;
	uint32_t			start_edges;
	uint32_t			end_edges;
	uint32_t			vertices;
	uint32_t			edges;
	uint32_t			entry_point;
	struct s_vertices	*hashtab[MAX_VERTICES];
}						t_map;

uint8_t					ft_puterror(char const *str, char const *err);

/*
**	Parsing
*/
uint8_t					ft_read_std_input(t_map *map, uint32_t *paths);
uint8_t					ft_parse_edges(t_map *map, char const *buffer);
uint8_t					ft_parse_vertices(t_map *node, char const *buffer);

/*
**	Memory
*/
void					ft_free_hashtable(t_vertices *hashtab[MAX_VERTICES]);
void					print_hashtab(t_map *map);
uint8_t					ft_initialize_hashtable(t_map *map);

/*
 **	Hash
 */
uint64_t				hash(const char *s);

/*
**	link_list
*/
uint8_t					add_connection(uint64_t hash1, uint64_t hash2, t_map *map);

#endif
