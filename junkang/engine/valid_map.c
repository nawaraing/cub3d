/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:17:53 by junkang           #+#    #+#             */
/*   Updated: 2020/10/30 19:18:42 by junkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_check_vertical(t_cub *cub, int i, int j, int set)
{
	while (cub->map[i][j] != 1)
	{
		if (!(cub->map[i][j]) || i < 0 || j < 0 || i >= 500 || j >= 500)
			return (-1);
		if (set == 0)
			j++;
		else if (set == 1)
			j--;
		else if (set == 2)
			i++;
		else if (set == 3)
			i--;
	}
	return (1);
}

static int	ft_check_one_user(t_cub *cub)
{
	int		i;
	int		j;
	int		ret;
	int		cnt;

	i = -1;
	while (++i < cub->map_h)
		if (cub->map[i][0])
			break ;
	if (i == cub->map_h)
		return (-1);
	ret = i;
	cnt = 0;
	i--;
	while (++i < cub->map_h)
	{
		j = -1;
		while (cub->map[i][++j])
			if (cub->map[i][j] == 3)
				cnt++;
	}
	if (cnt != 1)
		return (-1);
	return (ret);
}

int			ft_valid_map(t_cub *cub)
{
	int		i;
	int		j;

	if ((i = ft_check_one_user(cub)) == -1)
		return (-1);
	while (++i < cub->map_h)
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (cub->map[i][j] == 1 || cub->map[i][j] == ' ')
				continue ;
			if (ft_check_vertical(cub, i, j, 0) == -1)
				return (-1);
			else if (ft_check_vertical(cub, i, j, 1) == -1)
				return (-1);
			else if (ft_check_vertical(cub, i, j, 2) == -1)
				return (-1);
			else if (ft_check_vertical(cub, i, j, 3) == -1)
				return (-1);
		}
	}
	if (cub->user.radian == -1)
		return (-1);
	return (1);
}
