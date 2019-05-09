#include <lem_in.h>
#include <fcntl.h>
#include <unistd.h>
#include <lem_in_stacks.h>

uint8_t		append_to_file(char const *file, char const *s)
{
	int fd;

	fd = (access(file, F_OK) != -1) ? open(file, O_APPEND | O_RDWR, 0666) : open(file, O_CREAT | O_APPEND | O_RDWR, 0666);
	if (fd < 0)
		return (EXIT_FAILURE);
	ft_putendl_fd(s, fd);
	close(fd);
	return (EXIT_SUCCESS);

}

uint8_t		write_paths_to_file(t_map *map, t_stack *list)
{
	t_stack *tmp;
	t_queue *ptr;

	tmp = list;
	while (tmp)
	{
		ptr = tmp->path;
		while (ptr)
		{
			if (append_to_file("../visual/paths.txt", map->hashtab[ptr->key]->name) == EXIT_FAILURE)
				   return (EXIT_FAILURE);	
			ptr = ptr->next;
		}
		append_to_file("../visual/paths.txt", "");
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
