/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 20:23:18 by abrunet           #+#    #+#             */
/*   Updated: 2019/05/26 13:52:14 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in_visual.h>
#include <lem_in_stacks.h>
#include <lem_in.h>
#include <unistd.h>
#include <fcntl.h>

uint8_t		append_to_file(char const *file, char const *s)
{
	int fd;

	fd = (access(file, F_OK) != -1) ? open(file, O_APPEND | O_RDWR, 0666)
		: open(file, O_CREAT | O_APPEND | O_RDWR, 0666);
	if (fd < 0)
		return (EXIT_FAILURE);
	ft_putendl_fd(s, fd);
	close(fd);
	return (EXIT_SUCCESS);
}

uint8_t		write_data(t_map *map)
{
	append_to_file(DATA, ft_itoa(map->population));
	append_to_file(DATA, ft_itoa(map->vertices));
	append_to_file(DATA, map->hashtab[map->start_index]->name);
	append_to_file(DATA, map->hashtab[map->end_index]->name);
	return (EXIT_SUCCESS);
}

uint8_t		write_paths_to_file(t_map *map, t_listhead *head)
{
	t_queue		*lst;
	t_stack		*tmp;
	t_listhead	*ptr;
	t_listhead	*node;

	node = head;
	write_data(map);
	while ((node = node->next) != head && ft_stack_entry(node)->ant > 0)
	{
		tmp = ft_stack_entry(node);
		ptr = &(tmp->path->list);
		while ((ptr = ptr->next) != &(tmp->path->list))
		{
			lst = ft_queue_entry(ptr);
			if (append_to_file(PATHS, map->hashtab[lst->key]->name) == 1)
				return (EXIT_FAILURE);
		}
		append_to_file(PATHS, "");
		append_to_file(ANTS, ft_itoa(tmp->ant));
	}
	return (EXIT_SUCCESS);
}
