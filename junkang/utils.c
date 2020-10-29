#include "cub3d.h"

int		ft_isspace(char c)
{
	 if ((c >= 9 && c <= 13) || c == 32)
		 return (1);
	 return (0);
}

int		ft_isnum(char digit)
{
	if (digit < '0' || digit > '9')
		return (0);
	return (1);
}
