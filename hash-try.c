#include <stdio.h>
#include <stdlib.h>
#define MULTIPLIER (37)
#define	SIZE (4000)

typedef struct	s_list
{
	unsigned long hash;
	struct s_list *next;
}				t_list;

t_list			*make_node(unsigned long hash, t_list *list)
{
	t_list *new;

	if (!(new = malloc(sizeof(t_list))))
		return (NULL);
	new->hash = hash;
	new->next = list;
	return (new);
}

t_list			*add_node(unsigned long hash, t_list *list)
{
	t_list *new;

	if (!(new = make_node(hash, list)))
		return (NULL);
	list = new;
	return (list);
}

int				look_for_duplicate(t_list *list, char *line)
{
	t_list 			*tmp;
	unsigned long 	dup;
	int				count;

	count = 0;
	tmp = list->next;
	dup = list->hash;
	while (tmp)
	{
		if (tmp->hash == dup)
			count++;
		tmp = tmp->next;
	}
	if (count)
		printf("%s = %lu for %d times\n", line, list->hash, count);
	return (count);
}

unsigned long	hash(const char *s)
{
	unsigned long h;
	unsigned const char *us;
	/* cast s to unsigned const char * */
	/* this ensures that elements of s will be treated as having values >= 0 */
	us = (unsigned const char *) s;
 	h = 0;
	while(*us != '\0') 
	{
		h = h * MULTIPLIER + *us;
		us++;
	} 
	return h;
}

int		main(int argc, char **argv)
{
	FILE 	*file;
	char 	line[16];
	t_list 	*list;
	t_list 	*tmp;
	int		dup;

	list = NULL;
	file = fopen(argv[1], "r");
	dup = 0;
	while (fgets(line, sizeof(line), file))
	{
//		printf("%s = line\n", line);
		list = add_node(hash(line) % SIZE, list);
		if (list->next)
			dup += look_for_duplicate(list, line);
	}
	tmp = list;
/*	while (tmp)
	{
		printf("%lu\n", tmp->hash);
		tmp = tmp->next;
	}*/
	printf("%d = dup\n", dup);
	return (0);	
}
