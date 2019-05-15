/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 12:59:15 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/14 16:21:39 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NULL			(void *)0

#define __unused		__attribute__((unused))
#define __cold			__attribute__((cold))

#define __likely(x)		__builtin_expect(!!(x), 1)
#define __unlikely(x)	__builtin_expect(!!(x), 0)

#include <string.h>
#include <stdlib.h>

#define __list_entry(ptr, type, member)					\
	((type *)((char *)(ptr)-(uint64_t)(&((type *)0)->member)))

typedef struct			s_listhead {
	struct s_listhead	*next;
	struct s_listhead	*prev;
}						t_listhead;

typedef struct			s_lst {
	char				*name;
	t_listhead			list;
}						t_lst;

__cold
static inline void		ft_init_list_head(t_listhead *list) {
	list->next = list;
	list->prev = list;
}

static inline void		ft_list_add(t_listhead *new, t_listhead *prev, t_listhead *next) {
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

static inline void		ft_list_add_tail(t_listhead *new, t_listhead *head) {
	ft_list_add(new, head, head->next);
}

__attribute__((hot))
static t_lst			*ft_make_list(char const **argv, t_listhead *head) {
	t_lst				*node;

	while (++argv != NULL)
	{
		if (__unlikely((node = (t_lst *)malloc(sizeof(t_lst))) == NULL))
			return (NULL);
		node->name = (char *)argv[0];
		ft_list_add_tail(&node->list, head);
	}
	return (node);
}

#include <stdio.h>
static void				ft_display_list(t_listhead *head) {
	t_listhead			*tmp;

	tmp = head->next;
	while (tmp != head)
	{
		printf("%s\n", __list_entry(head, t_lst, list)->name);
		tmp = tmp->next;
	}
}

int						main(__unused int argc, char const **argv)
{
	t_lst				*list;
	t_listhead			head;

	ft_init_list_head(&head);
	if (__likely((list = ft_make_list(argv, &head)) != NULL))
		ft_display_list(&head);
	return (0);
}
