/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:17:21 by junkang           #+#    #+#             */
/*   Updated: 2020/10/30 19:46:56 by junkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_draw_sprite(t_cub *cub, double camera[2],\
			double *dist_to_wall)
{
	double		sp_vec_size_posx_dist[MAX_SP_NUM][5];
	int			valid_sp_cnt;
	int			i;

	ft_valid_sprite(cub, camera, sp_vec_size_posx_dist, &valid_sp_cnt);
	ft_sort(sp_vec_size_posx_dist, valid_sp_cnt);
	ft_get_size_posx_dist(cub, sp_vec_size_posx_dist, valid_sp_cnt, camera);
	i = -1;
	while (++i < valid_sp_cnt)
		ft_put_sprite(cub, sp_vec_size_posx_dist[i], dist_to_wall);
}

static void	ft_draw_background(t_cub *cub, t_dda_data dda,\
			double *dist_to_wall)
{
	int		wall_height;
	int		wall_start;
	int		i;

	ft_dda_dist(cub, &dda);
	ft_dda(cub, &dda);
	ft_hit_point(cub, &dda);
	if (dda.sidex < dda.sidey)
		dist_to_wall[dda.w] = dda.sidex;
	else
		dist_to_wall[dda.w] = dda.sidey;
	wall_height = (int)(cub->image.height / dist_to_wall[dda.w]);
	wall_start = -wall_height / 2 + cub->user.horizon;
	i = -1;
	while (++i < cub->image.height)
	{
		if (i >= wall_start && i <= wall_height / 2 + cub->user.horizon)
			ft_put_wall(cub, dda, i, wall_height);
		else if (i < wall_start)
			ft_draw_ceil(cub, dda, i);
		else
			ft_draw_floor(cub, dda, i);
	}
}

void		ft_put_image(t_cub *cub, double camera[2])
{
	int			w;
	t_dda_data	dda_data;
	double		*dist_to_wall;

	dist_to_wall = (double *)malloc(sizeof(double) * cub->image.width);
	w = -1;
	while (++w < cub->image.width)
	{
		dda_data.ray_vec[0] = camera[0] + camera[1] * \
			(2 * w - cub->image.width) * RATIO / \
			cub->image.width;
		dda_data.ray_vec[1] = camera[1] - camera[0] * \
			(2 * w - cub->image.width) * RATIO / \
			cub->image.width;
		dda_data.w = w;
		ft_draw_background(cub, dda_data, dist_to_wall);
	}
	ft_draw_sprite(cub, camera, dist_to_wall);
	free(dist_to_wall);
}
