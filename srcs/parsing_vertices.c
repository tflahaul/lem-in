/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_vertices.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 18:05:00 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/13 20:45:20 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_bug.h>
#include <lem_in_compiler.h>
#include <lem_in_hash.h>

unsigned long			hash(const char *s)
{
	unsigned long		h;
	unsigned const char	*us;

	us = (unsigned const char *)s;
	h = 0;
	while (*us != '\0')
	{
		h = h * MULTIPLIER + *us;
		us++;
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

	hashkey = hash(name);
	while (hashkey < MAX_VERTICES && map->hashtab[hashkey]->name != NULL)
	{
		if (strcmp(map->hashtab[hashkey++]->name, name) == 0)
			return (ft_puterror(name, DUPLICATE));
		if (UNLIKELY(hashkey == MAX_VERTICES - 1))
			hashkey = 0;
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
