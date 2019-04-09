#include <libft.h>

void					ft_putnstr(char const *str, uint8_t n)
{
	register uint8_t	index;

	index = 0;
	if (UNLIKELY(!str || !str[0]))
		ft_putchar(' ');
	else
	{
		while (index < n && str[index] != 0)
		{
			ft_putchar(ft_isprintable(str[index]) ? str[index] : '.');
			++index;
		}
	}
}
