#include "../include/lem_in.h"

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
				printf("--> %llu ", tmp->key);
	  			tmp = tmp->next;
			}
			printf("\n");	
		}
	}
}
