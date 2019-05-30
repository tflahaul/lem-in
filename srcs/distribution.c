/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:33:47 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/30 18:42:33 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <lem_in_stacks.h>
#include <lem_in_visual.h>
#include <lem_in_compiler.h>

static inline int	func2(int pop, int diff, int paths)
{
	return ((pop + diff) / paths + 1);
}

int					nbr_optimum_paths(t_map *map, t_listhead *head, int *path)
{
	int				size;
	int				diff;
	int				sum;
	int32_t			var;
	t_listhead		*tmp;

	diff = 0;
	var = map->population;
	tmp = head->next;
	size = ft_stack_entry(tmp)->size - 2;
	while (tmp->next != head->prev)
	{
		diff += ft_stack_entry(tmp)->size - size - 2;
		sum = func2(map->population, diff, ++(*path));
		if (sum > var)
		{
			ft_stack_entry(head)->ant = var;
			return ((*path -= 1));
		}
		tmp = tmp->next;
		var = sum;
	}
	ft_stack_entry(head)->ant = var;
	if (*path == 2 && var == sum)
		ft_stack_entry(head)->ant -= 1;
	return (*path);
}

void				ants_sup(uint32_t population, int32_t sum, t_listhead *head)
{
	int32_t			diff;
	t_listhead		*node;

	while (sum > (int32_t)population)
	{
		node = head->next;
		while (node->next != head && ft_stack_entry(node->next)->ant > 0)
			node = node->next;
		diff = sum - population;
		if (((int32_t)(ft_stack_entry(node)->ant) - diff) < 0)
		{
			sum -= ft_stack_entry(node)->ant;
			diff = ft_abs(ft_stack_entry(node)->ant - diff);
			ft_stack_entry(node)->ant = 0;
		}
		else
		{
			ft_stack_entry(node)->ant -= diff;
			sum -= diff;
		}
	}
}
#include <stdio.h>

void				ants_to_path(uint32_t ants,
									int *sum,
									int pop,
									t_listhead *head)
{
	int32_t			tmp;
	t_stack			*node;
	t_listhead		*ptr;

	ptr = head;
	tmp = (int32_t)ants;
	ft_stack_entry(ptr)->ant = ants;
	while ((ptr = ptr->next) != head && tmp > 0 && *sum <= pop)
	{
		node = ft_stack_entry(ptr);
		if ((tmp = ants - (node->size - ft_stack_entry(head->next)->size) - 2) > 0)
		{
			if (head->next == ptr \
				&& node->size == ft_stack_entry(head->next)->size - 2 \
				&& pop % 2)
				tmp -= 1;
			node->ant = tmp;
			*sum += tmp;
		}
	}
}

void				ft_population_distribution(t_map *map, t_stack *stacks)
{
	int32_t			sum;
	uint32_t		ants;

	ants = stacks->ant;
	stacks = ft_stack_entry(stacks->list.next);
	sum = ants;
	if (&(stacks->list) != stacks->list.prev)
	{
		ants_to_path(ants, &sum, map->population, &(stacks->list));
		ants_sup(map->population, sum, &(stacks->list));
	}
	else
		stacks->ant = map->population;
	if (!!(map->visual & VISUAL))
		write_paths_to_file(map, &(stacks->list));
	t_listhead *ptr = &stacks->list;
	while ((ptr = ptr->next) != &stacks->list)
		printf("=-=-= %u =-=-=\n", ft_stack_entry(ptr)->ant);
}
