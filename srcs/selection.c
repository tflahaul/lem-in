/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 14:44:42 by thflahau          #+#    #+#             */
/*   Updated: 2019/06/03 09:55:32 by thflahau         ###   ########.fr       */
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

	ptr = head->next;
	while ((ptr = ptr->next) != head->prev)
		visited[ft_queue_entry(ptr)->key] = visited_node;
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

/*
**	Check if the combination of paths in the given tab does not overlap.
*/

static uint8_t				ft_check_valid_path(t_listhead **tab)
{
	uint8_t					visited[MAX_VERTICES];
	register uint16_t		index;

	index = 0;
	__builtin_memset(visited, 0, MAX_VERTICES);
	while (tab[index] != NULL)
	{
		ft_write_path(tab[index++], visited);
		if (ft_does_overlap(tab[index], visited) == EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static uint32_t				ft_selection(t_listhead *head, t_listhead *start,
										uint8_t *visited, uint16_t nb)
{
	uint32_t				size;
	t_listhead				*position;

	size = 0;
	position = start;
	while (LIKELY((position = position->next) != head) && nb > 0)
	{
		if (ft_does_overlap(&(ft_stack_entry(position)->path->list), visited))
		{
			ft_write_path(&(ft_stack_entry(position)->path->list), visited);
			size += ft_stack_entry(position)->size;
			--nb;
		}
	}
	return (size);
}

static uint32_t				ft_select_non_overlapping_paths(t_listhead *head,
															uint16_t nb)
{
	register uint32_t		tmp;
	register uint32_t		size;
	t_listhead				*ptr;
	uint8_t					visited[MAX_VERTICES];

	ptr = head;
	tmp = UINT32_MAX;
	__builtin_memset(visited, unvisited_node, MAX_VERTICES);
	while ((ptr = ptr->next) != head)
	{
		size = ft_stack_entry(ptr)->size;
		ft_write_path(&(ft_stack_entry(ptr)->path->list), visited);
		size += ft_selection(head, ptr, visited, nb - 1);
		if (LIKELY(size < tmp))
			tmp = size;
		else
			return ((uint32_t)printf("__size__ = __%u__\n", size));
		__builtin_memset(visited, unvisited_node, MAX_VERTICES);
	}
	return ((uint32_t)printf("__size__ = __%u__\n", size));
}

/*
**	- Selectionne combinaison par combinaison
**	- Calcule le nombre d'étapes pour chaque combinaison
**	- A chaque meilleure solution, stocker
*/

void					ft_keep_best_paths(__unused t_map *map, t_listhead *head)
{
	uint16_t			index;

	index = 3;
	ft_select_non_overlapping_paths(head, index);
}
