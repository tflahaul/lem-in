/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_vertices.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 18:05:00 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/13 23:31:09 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_bug.h>
#include <lem_in_compiler.h>
#include <lem_in_hash.h>

unsigned long			hash(const char *name)
{
	unsigned long		h;

	h = 0;
	while (*name != '\0')
	{
		h = h * MULTIPLIER + *name;
		name++;
	}
	return (h % MAX_VERTICES);
}
/*
**	Récupère l'index de la table où placer le nom de la salle et itère jusqu'à
**	trouver un emplacement vide (si besoin).
*/

static inline uint8_t	ft_add_to_hashtable(t_map *map, char const *name)
{
	uint64_t			hashkey;
	
//	printf("entry point = %llu\n", map->entry_point);
	hashkey = hash(name);
	while (hashkey < MAX_VERTICES && map->hashtab[hashkey]->name != NULL)
	{
		if (strcmp(map->hashtab[hashkey++]->name, name) == 0)
			return (ft_puterror(name, DUPLICATE));
		if (UNLIKELY(hashkey == MAX_VERTICES - 1))
			hashkey = 0;
	}
	if (map->entry_point == 1 && !map->start_index)
	{
		map->start_index = hashkey;
		printf("%llu = start\n", map->start_index);
	}
	else if (map->entry_point == 2 && !map->end_index)
	{
		map->end_index = hashkey;
		printf("%llu = end\n", map->end_index);
	}
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
	if (UNLIKELY(ft_isprintable(buffer[0]) == 0 || (buffer[0] == 'L')))
		return (ft_puterror(buffer, BADNAME));
	while (ft_isblank(buffer[index]) == 0)
		index++;
	if (buffer[index] != ' ')
		return (ft_puterror(buffer, BADNAME));
	if ((name = ft_strsub(buffer, 0, index)) == NULL)
		return (ft_puterror(buffer, MEMERR));
	if (ft_add_to_hashtable(map, name) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_putstr_endl(buffer);
	return (EXIT_SUCCESS);
}
