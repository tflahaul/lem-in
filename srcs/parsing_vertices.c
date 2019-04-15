/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_vertices.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 18:05:00 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/14 22:15:54 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_bug.h>
#include <lem_in_compiler.h>
#include <lem_in_hash.h>

uint64_t				hash(const char *s)
{
	uint64_t			h;

	h = 0;
	while (*s != '\0')
	{
		h = h * MULTIPLIER + *s;
		s++;
	}
	return (h % MAX_VERTICES);
}

void					set_entry(uint64_t entry, t_map *map, uint64_t hashkey)
{
	if (entry == 1)
		map->start_index = hashkey;
	else if (entry == 2)
		map->end_index = hashkey;
	map->entry_point = 0;
}
/*
**	Récupère l'index de la table où placer le nom de la salle et itère jusqu'à
**	trouver un emplacement vide (si besoin).
*/

static uint8_t			ft_add_to_hashtable(t_map *map, char const *name)
{
	uint8_t				index;
	uint64_t			hashkey;

	index = 0;
	hashkey = hash(name);
	while (hashkey < MAX_VERTICES && map->hashtab[hashkey]->name != NULL)
	{
		if (ft_strcmp(map->hashtab[hashkey++]->name, name) == 0)
			return (ft_puterror(name, DUPLICATE));
		if (UNLIKELY(hashkey == MAX_VERTICES))
			hashkey = index++;
		else if (index > 1)
			return (ft_puterror(name, TOOBIG));
	}
	if (map->entry_point)
		set_entry(map->entry_point, map, hashkey);
	map->hashtab[hashkey]->name = name;
	map->vertices++;
	return (EXIT_SUCCESS);
}

/*
**	Vérification assez générale du bon formattage de la définition des salles.
**	Manque: gestion des coordonnés.
*/

uint8_t					ft_parse_vertices(t_map *map, char const *buffer)
{
	uint16_t			index;
	char				*name;

	index = 0;
	if (UNLIKELY(buffer[0] == 'L'))
		return (ft_puterror(buffer, BADNAME));
	while (ft_isblank(buffer[index]) == 0)
		index++;
	if (buffer[index] != ' ')
		return (ft_puterror(buffer, BADNAME));
	if ((name = ft_strsub(buffer, 0, index)) == NULL)
		return (ft_puterror(buffer, MEMERR));
	if (ft_add_to_hashtable(map, name) == EXIT_FAILURE)
		return (ft_variadic_memory_freeing(1, (void *)name));
	ft_putstr_endl(buffer);
	return (EXIT_SUCCESS);
}
