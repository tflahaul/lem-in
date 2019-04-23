/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:04:23 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/23 18:12:02 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdio.h>
# include <libft.h>

# define MAX_VERTICES	6000

# define MIN(x, y)		(x < y ? x : y)
# define ABS(x)			(x < 0 ? -x : x)

# undef OPEN
# define OPEN			1
# undef REMOVED
# define REMOVED		0
# undef CLOSED
# define CLOSED			-1

typedef struct			s_edges
{
	int64_t				way;
	uint64_t			key;
	struct s_edges		*next;
}						t_edges;

typedef struct			s_vertices
{
	int32_t				x;
	int32_t				y;
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
	uint32_t			superposition;
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
void					print_hashtab(t_map *map);
uint8_t					ft_initialize_hashtable(t_map *map);

/*
**	link_list
*/
uint8_t					add_connection(uint32_t h1, uint32_t h2, t_map *map);

/*
**	Algorithm
*/
void					ft_algorithm(t_map *map);
uint8_t					ft_breadth_first_search(t_map *map, uint8_t *v);

#endif
