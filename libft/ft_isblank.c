#include <libft.h>

int						ft_isblank(int c)
{
	return (c == ' ' || c == '\t' || c == '-' ? 1 : 0);
}
