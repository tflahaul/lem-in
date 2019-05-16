/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:04:23 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/16 16:14:31 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"
# include <lem_in_visual.h>

# define MAX_VERTICES	6000

# define MIN(x, y)		(x < y ? x : y)

# define VISUAL			0x00000001u
# define COLORS			0x00010000u

enum
{
	CLOSED = -1,
	REMOVED = 0,
	OPEN = 1
};

typedef struct			s_edges
{
	int32_t				way;
	uint32_t			key;
	struct s_edges		*next;
}						t_edges;

typedef struct			s_vertices
{
	uint64_t			key;
	char const			*name;
	struct s_edges		*adjc;
	struct s_vertices	*prev;
}						t_vertices;

typedef struct			s_map
{
	uint32_t			start_index;
	uint32_t			end_index;
	uint32_t			population;
	uint32_t			start_edges;
	uint32_t			end_edges;
	uint32_t			vertices;
	uint32_t			entry_point;
	uint32_t			visual;
	struct s_vertices	*hashtab[MAX_VERTICES];
}						t_map;

/*
**	Parsing
*/
uint8_t					ft_read_std_input(t_map *map);
uint8_t					ft_parse_edges(t_map *map, char const *buffer);
uint8_t					ft_parse_vertices(t_map *node, char const *buffer);

/*
**	Memory
*/
void					ft_free_hashtable(t_vertices *hashtab[MAX_VERTICES]);
uint8_t					ft_initialize_hashtable(t_map *map);

/*
**	Linked lists
*/
uint8_t					add_connection(uint32_t h1, uint32_t h2, t_map *map);

/*
**	Algorithm
*/
void					ft_algorithm(t_map *map);
uint8_t					ft_simple_bfs(t_map *map, uint8_t *v);
uint8_t					ft_breadth_first_search(t_map *map, uint8_t *v);
uint64_t				ft_abs(int64_t nb);

/*
**	Visualization
*/
void					ft_print_colored_ant(uint32_t nb, char const *name);
uint8_t					append_to_file(char const *file, char const *s);

#endif
