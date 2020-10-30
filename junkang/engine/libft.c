/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:32:00 by junkang           #+#    #+#             */
/*   Updated: 2020/10/30 19:22:22 by junkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_atoi(const char *nptr)
{
	unsigned long long		res;
	int						sign;

	res = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	sign = 1;
	if (*nptr == '-')
	{
		nptr++;
		sign = -1;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + (*nptr - '0');
		if (res > LLONG_MAX)
			return (sign == 1 ? -1 : 0);
		nptr++;
	}
	return (sign * (int)res);
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
