/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 20:23:18 by abrunet           #+#    #+#             */
/*   Updated: 2019/05/24 13:36:47 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <fcntl.h>
#include <unistd.h>
#include <lem_in_stacks.h>
#include <lem_in_visual.h>

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
/*
uint8_t		write_paths_to_file(t_map *map, t_stack *list)
{
	t_stack		*tmp;
	t_queue		*ptr;
	const char	*name;

	tmp = list;
	write_data(map);
	while (tmp && tmp->ant > 0)
	{
		ptr = tmp->path;
		while (ptr)
		{
			name = map->hashtab[ptr->key]->name;
			if (append_to_file(PATHS, name) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			ptr = ptr->next;
		}
		append_to_file(PATHS, "");
		append_to_file(ANTS, ft_itoa(tmp->ant));
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
*/