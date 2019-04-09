#include <libft.h>

void					*ft_memset(void *s, int c, size_t n)
{
	unsigned char		*ptr;
	unsigned char		uchar;

	uchar = (unsigned char)c;
	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = uchar;
	return (s);
}
