#include "../include/lem_in.h"
#include <lem_in_stacks.h>

void			print_paths(t_map *map, void *node)
{
	t_stack		*ptr = (t_stack *)node;

	while (ptr != NULL)
	{
		printf("\n==== PATH [%llu] ====\n", ptr->size);
		while (ptr->path != NULL)
		{
			printf("%s\n", map->hashtab[ptr->path->key]->name);
			ptr->path = ptr->path->next;
		}
		ptr = ptr->next;
	}
}

void	print_hashtab(t_map *map)
{
	int 		ind;
	t_edges 	*tmp;

	ind = -1;
	while (++ind < MAX_VERTICES)
	{
		if (map->hashtab[ind]->name)
		{
			printf("%d : [%s && %llu] ", ind, map->hashtab[ind]->name, map->hashtab[ind]->key);
			tmp = map->hashtab[ind]->adjc;
			while (tmp)
			{
				printf("--> %llu[%lli]", tmp->key, tmp->way);
	  			tmp = tmp->next;
			}
			printf("\n");
		}
	}
}
