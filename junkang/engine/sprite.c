/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:17:12 by junkang           #+#    #+#             */
/*   Updated: 2020/10/30 19:50:55 by junkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			ft_sort(double vec[MAX_SP_NUM][5], int cnt)
{
	int			i;
	int			j;
	double		tmp[2];

	j = cnt + 1;
	while (--j > 1)
	{
		i = 0;
		while (++i < j)
		{
			if (pow(vec[i - 1][0], 2) + pow(vec[i - 1][1], 2) < \
					pow(vec[i][0], 2) + pow(vec[i][1], 2))
			{
				tmp[0] = vec[i][0];
				tmp[1] = vec[i][1];
				vec[i][0] = vec[i - 1][0];
				vec[i][1] = vec[i - 1][1];
				vec[i - 1][0] = tmp[0];
				vec[i - 1][1] = tmp[1];
			}
		}
	}
}

void			ft_get_size_posx_dist(t_cub *cub,\
				double vec[MAX_SP_NUM][5], int cnt, double camera[2])
{
	int			i;
	double		cross;
	double		sx;
	double		sy;

	i = -1;
	while (++i < cnt)
	{
		vec[i][4] = camera[0] * vec[i][0] + camera[1] * vec[i][1];
		sx = camera[0] - vec[i][0] / vec[i][4];
		sy = camera[1] - vec[i][1] / vec[i][4];
		vec[i][3] = sqrt(pow(sx, 2) + pow(sy, 2));
		cross = camera[0] * vec[i][1] - camera[1] * vec[i][0];
		if (cross < 0)
			vec[i][3] += RATIO;
		else
			vec[i][3] = RATIO - vec[i][3];
		vec[i][3] *= cub->image.width / 2;
		vec[i][3] /= RATIO;
		vec[i][2] = cub->image.height / vec[i][4];
	}
}

void			ft_valid_sprite(t_cub *cub, double camera[2],\
				double vec[MAX_SP_NUM][5], int *sp_cnt)
{
	int			cnt;
	int			i;
	double		sx;
	double		sy;
	double		coss;

	cnt = 0;
	i = 0;
	while (i < cub->sprite_cnt)
	{
		sx = cub->sprite_pos[i][0];
		sy = cub->sprite_pos[i][1];
		sx = (sx - cub->user.x);
		sy = (cub->user.y - sy);
		coss = (camera[0] * sx + camera[1] * sy) / \
				sqrt(pow(sx, 2) + pow(sy, 2));
		if (coss > 0.0000001)
		{
			vec[cnt][0] = sx;
			vec[cnt][1] = sy;
			cnt++;
		}
		i++;
	}
	*sp_cnt = cnt;
}

static int		ft_get_color(t_cub *cub, double vec[5], int w, int h)
{
	int		*xpm_addr;
	int		color;

	xpm_addr = (int *)cub->xpm.sprite.addr;
	color = xpm_addr[(h - cub->user.horizon + (int)(vec[2]) / 2)\
		* cub->xpm.sprite.height / \
		(int)(vec[2]) * cub->xpm.sprite.sl / 4 + \
		(int)(w - vec[3] + vec[2] / 2) * cub->xpm.sprite.width \
		/ (int)(vec[2])];
	return (color);
}

void			ft_put_sprite(t_cub *cub, double vec[5],\
				double *dist_to_wall)
{
	int		*img_addr;
	int		w;
	int		h;
	int		color;

	img_addr = (int *)cub->image.addr;
	w = (int)(vec[3] - vec[2] / 2) - 1;
	while (++w <= vec[3] + vec[2] / 2)
	{
		if (w < 0 || w >= cub->image.width)
			continue ;
		h = cub->user.horizon - vec[2] / 2 - 1;
		while (++h < cub->user.horizon + vec[2] / 2 - 1)
		{
			if (h < 0 || h >= cub->image.height)
				continue ;
			color = ft_get_color(cub, vec, w, h);
			if (color != 0 && vec[4] < dist_to_wall[w])
				img_addr[w + h * cub->image.sl / 4] = color;
		}
	}
}
