/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 14:44:42 by thflahau          #+#    #+#             */
/*   Updated: 2019/06/05 12:59:16 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_list.h>
#include <lem_in_stacks.h>
#include <lem_in_compiler.h>
#include <lem_in_algorithm.h>

#include <lem_in.h>
#include <stdio.h>

__attribute__((hot))
static inline void			ft_write_path(t_listhead *head, uint8_t *visited)
{
	register t_listhead		*ptr __asm__("eax");

	if (LIKELY(head != NULL))
	{
		ptr = head->next;
		while ((ptr = ptr->next) != head->prev)
			visited[ft_queue_entry(ptr)->key] = visited_node;
	}
}

__attribute__((always_inline))
static inline uint8_t		ft_does_overlap(t_listhead *head, uint8_t *visited)
{
	register t_listhead		*ptr __asm__("eax");

	if (LIKELY(head != NULL))
	{
		ptr = head->next;
		while ((ptr = ptr->next) != head->prev)
			if (visited[ft_queue_entry(ptr)->key] != unvisited_node)
				return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static uint8_t				ft_check_path(t_listhead **tab, t_listhead *new)
{
	uint8_t					visited[MAX_VERTICES];
	register uint16_t		index;

	index = 0;
	ft_fast_bzero(visited, MAX_VERTICES);
	while (LIKELY(tab[index]))
		ft_write_path(&(ft_stack_entry(tab[index++])->path->list), visited);
	if (ft_does_overlap(&(ft_stack_entry(new)->path->list), visited) == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

__attribute__((hot))
static inline void			ft_add_address_to_tab(t_listhead **tab,
													t_listhead *node)
{
	register uint16_t		index;

	index = 0;
	while (tab[index])
		++index;
	tab[index] = node;
}

static inline uint32_t		ft_get_paths_combinations(t_listhead *head,
														uint32_t nb)
{
	t_listhead				*node;
	t_listhead				*position;
	t_listhead				*tab[(MAX_VERTICES >> 1)];

	while (tab[nb - 1] == 0)
	{
		node = head;
		ft_fast_bzero(tab, (MAX_VERTICES >> 1));
		while ((node = node->next) != head)
		{
			position = node;
			while ((position = position->next) != node)
				if (ft_check_path(tab, position) == EXIT_SUCCESS)
					ft_add_address_to_tab(tab, position);
		}
	}
	return (EXIT_SUCCESS);
}

/*
**	- Selectionne combinaison par combinaison
**	- Calcule le nombre d'étapes pour chaque combinaison
**	- A chaque meilleure solution, remplacer l'ancinne
*/

void					ft_keep_best_paths(t_listhead *head)
{
	uint16_t			index;

	index = 2;
	ft_get_paths_combinations(head, index);
}
