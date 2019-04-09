#include <libft.h>

int						ft_isaligned(void *ptr)
{
	return (((size_t)ptr & (sizeof(ptr) - 1)) == 0);
}
