#include <lem_in.h>
#include <lem_in_queue.h>
#include <lem_in_stacks.h>
void			print_tmp(t_stack *list, t_map *map)
{
	t_queue		*node;

	node = list->path;
	while (node)
	{
		printf("%s\n", map->hashtab[node->key]->name);
		node = node->next;
	}
}

uint32_t		get_overlap_size(t_map *map)
{
	t_vertices *ptr;
	uint32_t	count;

	ptr = map->hashtab[map->end_index];
	count = 0;
	while ((ptr = ptr->prev))
		count++;
	return (count);
}

uint8_t			split_path(t_stack *list, t_map *map)
{
	uint32_t	overlap;
	uint64_t	ants;
	uint64_t	sum;
	
	overlap = get_overlap_size(map);
	ants = map->population;
	sum = ants + (list->size - 1) - 1;
	if (sum > ants / 2 + overlap)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

t_stack			*get_overlap_path(t_stack *list, t_map *map)
{
	t_stack		*tmp;
	t_queue		*node;

	tmp = list;
	while (tmp->next)
	{
		node = tmp->path;
		while (node)
		{
			if (node->key == map->overlap.next_key)
			{
//				print_tmp(tmp, map);
				if (split_path(tmp, map) == EXIT_SUCCESS)
					return (tmp);
				return (NULL);
			}
			node = node->next;
		}
		tmp = tmp->next;
	}
	return (NULL);	
}
