/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 13:30:22 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/22 03:25:32 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_list.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct		s_list
{
	t_listhead		list;
	int				value;
}					t_list;

static void			ft_delete_list(t_listhead *head)
{
	t_list			*ptr;
	t_listhead		*node;
	t_listhead		*next;

	node = head->next;
	next = node->next;
	while (node != head)
	{
		if ((ptr = LIST_ENTRY(node, t_list, list)) != NULL)
			free((void *)ptr);
		node = next;
		next = node->next;
	}
}

int					main(int argc, char **argv)
{
	t_list			*tmp;
	t_listhead		*pos, *q;
	unsigned int	i = 0;

	t_list			ourlist;
	ft_list_head_init(&ourlist.list);
	while (i < 5)
	{
		if ((tmp = (t_list *)malloc(sizeof(t_list))) == NULL)
			return (-1);
		tmp->value = i++;
		ft_list_push(&(tmp->list), &(ourlist.list));
	}

	pos = (&ourlist.list)->next;
	while (pos != (&ourlist.list))
	{
		tmp = LIST_ENTRY(pos, t_list, list);
		printf("[%d]\n", tmp->value);
		pos = pos->next;
	}

	ft_delete_list(&ourlist.list);
	return (0);
}
