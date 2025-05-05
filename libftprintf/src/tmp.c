#include "../include/libft.h"

int		count = 37;

void	*malloc_B(size_t size)
{
	if (--count == 0)
		return (NULL);
	return ((malloc)(size));
}