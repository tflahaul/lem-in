/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:49:35 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/28 15:42:14 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_stacks.h>
#include <lem_in_compiler.h>

static inline void			ft_print_single_ant(uint16_t nb, const char *name)
{
	ft_putchar('L');
	ft_putnbr_light(nb);
	ft_putchar('-');
	ft_putstr(name);
	ft_putchar(' ');
}

static inline void			ft_print_stack(t_map *map, t_queue *queue)
{
	while ((queue = queue->next) != NULL)
		if (queue->ant && queue->ant <= map->population)
			ft_print_single_ant(queue->ant, map->hashtab[queue->key]->name);
}

/*
**	Effectue une rotation vers le bas des valeurs (uniquement) de la stack
**	`queue` pour simuler le mouvement des fourmis à travers les salles.
*/

static void					ft_update_stack(t_queue *queue, uint64_t size)
{
	uint16_t				index;
	t_queue					*node;
	uint16_t				ants[size];

	index = 0;
	node = queue;
	while (node != NULL)
	{
		ants[index++] = node->ant;
		node = node->next;
	}
	index = 0;
	while ((queue = queue->next) != NULL)
		queue->ant = ants[index++];
}

/*
**	Affecte une fourmie en haut de chaque stack/chemin. On utilise une
**	variable statique pour ne pas perdre le numéro de la dernière fourmie
**	envoyée.
*/

static inline void			ft_init_movements(t_stack *stack)
{
	static uint64_t			ant;

	while (stack != NULL)
	{
		stack->path->ant = ++ant;
		stack = stack->next;
	}
}

/*
**	Fonction principale pour l'affichage du déplacement des fourmis.
*/

void						ft_print_movements(t_map *map, t_stack *list)
{
	uint32_t				length;
	t_stack					*stacks;

	length = map->population + list->size - 1;
	while (length--)
	{
		stacks = list;
		ft_init_movements(stacks);
		while (stacks != NULL)
		{
			ft_print_stack(map, stacks->path);
			ft_update_stack(stacks->path, stacks->size);
			stacks = stacks->next;
		}
		ft_putchar('\n');
	}
}
