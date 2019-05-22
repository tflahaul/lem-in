/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 13:23:19 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/22 06:48:05 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_LIST_H
# define LEM_IN_LIST_H

# include <stdint.h>

/*
**	Cast a member of a structure out to the containing structure
**	Same as the `container_of` macro from the Linux kernel, file
**	`include/linux/kernel.h` L835
*/
# define LIST_ENTRY(ptr, type, member) ({							\
	const typeof(((type *)0)->member) *__mptr = (ptr);				\
	(type *)((char *)__mptr - __builtin_offsetof(type, member));})

typedef struct			s_listhead
{
	struct s_listhead	*next;
	struct s_listhead	*prev;
}						t_listhead;

# ifndef NULL
#  define NULL			(void *)0
# endif

void					ft_list_pop(t_listhead *head);
void					ft_list_init_head(t_listhead *head);
void					ft_list_push(t_listhead *e, t_listhead *head);
void					ft_list_add_tail(t_listhead *e, t_listhead *head);
void					ft_list_add(t_listhead *e, t_listhead *p, t_listhead *n);
uint8_t					ft_list_del(t_listhead *head);

#endif
