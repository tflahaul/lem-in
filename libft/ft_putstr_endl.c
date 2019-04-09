#include <libft.h>

void				ft_putstr_endl(char const *str)
{
	write(1, str, ft_strlen(str));
	ft_putchar('\n');
}
