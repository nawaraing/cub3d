#include "cub3d.h"

size_t	ft_strlen(const char *s)
{
	size_t	res;

	res = 0;
	while (*(unsigned char *)s++)
		res++;
	return (res);
}

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int		res;

	res = 0;
	while (n--)
	{
		if (*(unsigned char *)s1 != *(unsigned char *)s2)
		{
			res = (int)(*(unsigned char *)s1 - *(unsigned char *)s2);
			break ;
		}
		s1 += sizeof(unsigned char);
		s2 += sizeof(unsigned char);
	}
	return (res);
}

void	*ft_memset(void *ptr, int value, size_t num)
{
	void	*res;

	res = ptr;
	while (num--)
	{
		*(unsigned char *)ptr = (unsigned char)value;
		ptr += sizeof(unsigned char);
	}
	return (res);
}
