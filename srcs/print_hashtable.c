#include "../include/lem_in.h"
#include <lem_in_stacks.h>

void	print_hashtab(t_map *map)
{
	int 		ind;
	t_edges 	*tmp;

	ind = -1;
	while (++ind < MAX_VERTICES)
	{
		if (map->hashtab[ind]->name)
		{
			printf("%d : [%s] ", ind, map->hashtab[ind]->name);
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

void				print_paths(t_map *map, t_stack *list)
{
	while (list != NULL)
	{
		printf("\n====== PATH ======\n");
		t_queue			*ptr = list->path;
		while (ptr != NULL)
		{
			printf("%s\n", map->hashtab[ptr->key]->name);
			ptr = ptr->next;
		}
		list = list->next;
	}
}
