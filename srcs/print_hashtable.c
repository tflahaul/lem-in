#include "../include/lem_in.h"

void	print_hashtab(t_map *map)
{
	int ind;

	ind = -1;
	while (++ind < MAX_VERTICES)
	{
		printf("%d --> %s\n", ind, map->hashtab[ind]->name); 
	}
}
