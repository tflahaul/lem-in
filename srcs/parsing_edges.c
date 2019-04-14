/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_edges.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 20:46:10 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/14 19:50:49 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_bug.h>
#include <lem_in_compiler.h>
#include <lem_in_hash.h>

uint64_t				hashn(const char *s, int size)
{
	uint64_t	h;
	int			ind;

	h = 0;
	ind = -1;
	while (++ind < size)
	{
		h = h * MULTIPLIER + *s;
		s++;
	}
	return (h % MAX_VERTICES);
}

t_edges					*make_node(uint64_t hashkey)
{
	t_edges		*new;

	if (UNLIKELY(!(new = malloc(sizeof(t_edges)))))
		return (NULL);
	new->key = hashkey;
	new->next = NULL;
	return (new);
}

uint8_t					add_connection(uint64_t hash1, uint64_t hash2, t_map *map)
{
	t_edges		*new;
	t_edges		*tmp;

	if (UNLIKELY(!(new = make_node(hash2))))
		return (EXIT_FAILURE);
	if (!map->hashtab[hash1]->adjc)
		map->hashtab[hash1]->adjc = new;
	else
	{
		tmp = map->hashtab[hash1]->adjc;
		while (tmp)
		{
			if (tmp->key == hash2)
			{
				free(new);
				return (ft_puterror(map->hashtab[hash2]->name, DUPLINK));
			}
			if (!tmp->next)
			{
				tmp->next = new;
				return (EXIT_SUCCESS);
			}
			tmp = tmp->next;
		}
	}
	return (EXIT_SUCCESS);	
}

uint8_t					get_collision_key(uint64_t *hashkey, t_map *map, char *ptr, const char *buffer)
{
	uint64_t	tmp;

	tmp = *hashkey;
	while (map->hashtab[*hashkey]->name != NULL)
   	{
		if (buffer)
		{
			if ((ft_strncmp(map->hashtab[*hashkey]->name, buffer, ptr - buffer)) == 0)
				return (EXIT_SUCCESS);
		}
		else		
			if ((ft_strcmp(map->hashtab[*hashkey]->name, ptr + 1)) == 0)
				return (EXIT_SUCCESS);	
		(*hashkey)++;
		if (UNLIKELY(*hashkey == MAX_VERTICES))
			*hashkey = 0;
		if (UNLIKELY(*hashkey == tmp))
			return (ft_puterror(buffer, TOOBIG));
	}
	return (ft_puterror(buffer, NOROOM));
}

uint8_t					get_connections(char const *buffer, char *ptr, t_map *map)
{
	uint64_t 	hash1;
	uint64_t	hash2;

	if (!(ptr + 1))
		return (EXIT_FAILURE);
	hash2 = hash(ptr + 1);
	hash1 = hashn(buffer, ptr - buffer);
	if (UNLIKELY((get_collision_key(&hash1, map, ptr, buffer)) == EXIT_FAILURE))
		return (EXIT_FAILURE);	
	if (UNLIKELY((get_collision_key(&hash2, map, ptr, NULL)) == EXIT_FAILURE))
		return (EXIT_FAILURE);	
 	if (add_connection(hash1, hash2, map))
		return (EXIT_FAILURE);
	if (add_connection(hash2, hash1, map))
		return (EXIT_FAILURE);
	print_hashtab(map);
	return (EXIT_SUCCESS);
}

uint8_t					ft_parse_edges(t_map *map, char const *buffer)
{
	uint16_t			index;
	char 				*ptr;

	index = 0;
	if (LIKELY((ptr = strchr(buffer, '-'))))
	{
		if (get_connections(buffer, ptr, map))
			return (EXIT_FAILURE);
	}
	else
		return (ft_puterror(buffer, UNKCOMM));
	ft_putstr_endl(buffer);
	return (EXIT_SUCCESS);
}
