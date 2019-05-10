/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:33:47 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/10 18:00:16 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>

static inline uint64_t	ft_abs(int64_t nb)
{
	return ((nb < 0) ? -nb : nb);
}

/*
**	Formule implémentée:	P/N...
**
**	Ici le problème vient de l'équation qui ajoute une certaine proportion de
**	fourmis à chaque nouveau chemin étudié (ex: 3 chemins +18% de fourmis, 4
**	chemins +24% de fourmis, 5 chemins +30% de fourmis...). -- la somme des
**	ratios est supérieure à 1 -- Le résultat de tout ça c'est que sur les
**	petites cartes avec assez peu de fourmis les solutions trouvées peuvent
**	paraître correctes mais sur les grosses cartes (superbig - 480 fourmis),
**	même si le calcul du nombre d'étapes est bon, la solution trouvée est
**	toujours croissante de part l'augmentation du nombre de fourmis. Par
**	exemple, sur `superbig`, une augmentation de 24% du nombre de fourmis,
**	ça fait environ 115 nouvelles fourmis... et sur les solutions qui utilisent
**	beaucoup de chemins il est pas impossible de doubler le nombre de départ.
**	C'est moche.
**
**	Exemple pratique pour 3 chemins:
**	Chemin:					1		2		3
**	Proportion:				50%		25%		25%
**	Proportion inverse:		50%		75%		75%		(+100%)
**
**	!! Attention au cas à une seule fourmie !!
*/

static uint32_t			ft_compute_steps(t_map *map, t_stack *ptr, uint32_t nb)
{
	uint32_t			step;
	uint32_t			ratio;
	register uint16_t	index;

	step = 0;
	ratio = map->population / nb;
	if (nb == 1)
		return (map->population + ptr->size - 1);
	else if (LIKELY((ptr = ptr->next) != NULL))
	{
		index = 0;
		step = ratio + ptr->size - 1;
		while (++index < (uint16_t)nb && LIKELY((ptr = ptr->next) != NULL))
			step += ft_abs(step - (ratio + ptr->size - 1));
	}
	return (step);
}

uint16_t				ft_population_distribution(t_map *map, t_stack *stacks)
{
	uint32_t			tmp;
	uint32_t			steps;
	register uint16_t	index;

	index = 2;
	steps = ft_compute_steps(map, stacks, 1);
	while (index <= map->start_edges)
	{
		tmp = ft_compute_steps(map, stacks, index);
		if (tmp > steps)
			return (index);
		else
		{
			steps = tmp;
			index++;
		}
	}
	return (index - 1);
}
