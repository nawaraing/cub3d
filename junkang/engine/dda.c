/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:16:49 by junkang           #+#    #+#             */
/*   Updated: 2020/10/30 19:17:04 by junkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			ft_dda_dist(t_cub *cub, t_dda_data *dda_data)
{
	t_dda_data	dda;

	dda = *dda_data;
	dda.x = (int)cub->user.x;
	dda.y = (int)cub->user.y;
	dda.dx = 1 / fabs(dda.ray_vec[0]);
	dda.dy = 1 / fabs(dda.ray_vec[1]);
	dda.directx = 1;
	dda.directy = 1;
	if (dda.ray_vec[0] < 0)
	{
		dda.directx = -1;
		dda.sidex = (cub->user.x - dda.x) * dda.dx;
	}
	else
		dda.sidex = (1 + dda.x - cub->user.x) * dda.dx;
	if (dda.ray_vec[1] < 0)
		dda.sidey = (1 + dda.y - cub->user.y) * dda.dy;
	else
	{
		dda.directy = -1;
		dda.sidey = (cub->user.y - dda.y) * dda.dy;
	}
	*dda_data = dda;
}

void			ft_dda(t_cub *cub, t_dda_data *dda_data)
{
	while (1)
	{
		if (dda_data->sidex > dda_data->sidey)
		{
			dda_data->y += dda_data->directy;
			if (1 == cub->map[dda_data->y][dda_data->x])
				break ;
			dda_data->sidey += dda_data->dy;
		}
		else
		{
			dda_data->x += dda_data->directx;
			if (1 == cub->map[dda_data->y][dda_data->x])
				break ;
			dda_data->sidex += dda_data->dx;
		}
	}
}

void			ft_hit_point(t_cub *cub, t_dda_data *dda)
{
	double		hit_point;

	if (dda->sidex > dda->sidey)
	{
		if (dda->directy > 0)
			dda->flag = 0;
		else
			dda->flag = 1;
		hit_point = (dda->ray_vec[1] == 0) ? \
			cub->user.x : \
			cub->user.x + (cub->user.y - dda->y - dda->flag) * \
			dda->ray_vec[0] / dda->ray_vec[1];
	}
	else
	{
		if (dda->directx > 0)
			dda->flag = 2;
		else
			dda->flag = 3;
		hit_point = (dda->ray_vec[0] == 0) ? \
			cub->user.y : \
			cub->user.y - (dda->x - cub->user.x + (dda->flag - 2)) \
			* dda->ray_vec[1] / dda->ray_vec[0];
	}
	dda->hit_point = hit_point;
}
