#include "cub3d.h"
#include <stdio.h>				//

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

void			ft_hit_point(t_cub *cub, t_dda_data *dda_data)
{
	t_dda_data	dda;
	double		hit_point;

	dda = *dda_data;
	if (dda.sidex > dda.sidey)
	{
		if (dda.directy > 0)
			dda.flag = 0;
		else
			dda.flag = 1;
		hit_point = (dda.ray_vec[1] == 0) ? cub->user.x : cub->user.x + \
			   (cub->user.y - dda.y - dda.flag) * dda.ray_vec[0] / dda.ray_vec[1];
	}
	else
	{
		if (dda.directx > 0)
			dda.flag = 2;
		else
			dda.flag = 3;
		hit_point = (dda.ray_vec[0] == 0) ? cub->user.y : cub->user.y - \
			   (dda.x - cub->user.x + (dda.flag - 2)) * dda.ray_vec[1] / dda.ray_vec[0];
	}
	dda.hit_point = hit_point;
	*dda_data = dda;
}

void			ft_put_wall(t_cub *cub, t_dda_data dda_data, int i, int wall_height)
{
	double		hp;
	t_image		xpm_img;
	int		*xpm_addr;
	int		*img_addr;
	int		wall_start;

	hp = dda_data.hit_point;
	img_addr = (int *)cub->image.addr;
	if (dda_data.flag == 0)
		xpm_img = cub->xpm.south_wall;
	else if (dda_data.flag == 1)
		xpm_img = cub->xpm.north_wall;
	else if (dda_data.flag == 2)
		xpm_img = cub->xpm.west_wall;
	else
		xpm_img = cub->xpm.east_wall;
	wall_start = -wall_height / 2 + cub->user.horizon;
	xpm_addr = (int *)xpm_img.addr;
	img_addr[dda_data.w + i * cub->image.sl / 4] = xpm_addr[(i - wall_start) * xpm_img.height / wall_height * xpm_img.sl / 4 + (int)((hp - (int)hp) * xpm_img.width)];
}

void			ft_ceil_floor_draw(t_cub *cub, t_dda_data dda_data, int i)
{
	double		pixel_dist;
	t_image		xpm_img;
	double		xpm[2];
	int		*xpm_addr;
	int		*img_addr;

	if (cub->user.horizon < i)
	{
		pixel_dist = 0.5 * cub->image.height / (i - cub->user.horizon);
		xpm_img = cub->xpm.floor;
	}
	else
	{
		pixel_dist = 0.5 * cub->image.height / (cub->user.horizon - i);
		xpm_img = cub->xpm.ceil;
	}
	xpm[0] = cub->user.x + dda_data.ray_vec[0] * pixel_dist;
	xpm[1] = cub->user.y - dda_data.ray_vec[1] * pixel_dist;
	xpm[0] = (xpm[0] - floor(xpm[0])) * xpm_img.width;
	xpm[1] = (xpm[1] - floor(xpm[1])) * xpm_img.height;
	xpm_addr = (int *)xpm_img.addr;
	img_addr = (int *)cub->image.addr;
	img_addr[dda_data.w + i * cub->image.sl / 4] = xpm_addr[(int)(xpm[1]) * xpm_img.sl / 4 + (int)xpm[0]];
}

void			ft_draw_wall(t_cub *cub, t_dda_data dda_data, double *dist_to_wall)
{
	double		hit_point;
	double		minn;
	int		wall_height;
	int		wall_start;
	int		*img_addr;

	ft_dda_dist(cub, &dda_data);
	ft_dda(cub, &dda_data);
	ft_hit_point(cub, &dda_data);
	hit_point = dda_data.hit_point;
	if (dda_data.sidex < dda_data.sidey)
		minn = dda_data.sidex;
	else
		minn = dda_data.sidey;
	dist_to_wall[dda_data.w] = minn;
	wall_height = (int)(cub->image.height / minn);
	wall_start = -wall_height / 2 + cub->user.horizon;
	img_addr = (int *)cub->image.addr;
	for (int i = 0; i < cub->image.height; i++)
	{
		if (i >= wall_start && i <= wall_height / 2 + cub->user.horizon)
			ft_put_wall(cub, dda_data, i, wall_height);
		else ft_ceil_floor_draw(cub, dda_data, i);
	}
}

void			ft_sort(double vec[100][4], int cnt)
{
	double		tmp[2];
	for (int j = cnt; j > 1; j--)
	{
		for (int i = 1; i < j; i++)
		{
			if (sqrt(pow(vec[i - 1][0], 2) + pow(vec[i - 1][1], 2)) < \
					sqrt(pow(vec[i][0], 2) + pow(vec[i][1], 2)))
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

void			ft_get_size_posx(t_cub *cub, double vec[100][4], int cnt, double camera_vec[2])
{
	double		cross, dot_prod;
	double		sx, sy;

	for (int i = 0; i < cnt; i++)
	{
		dot_prod = (camera_vec[0] * vec[i][0] + camera_vec[1] * vec[i][1]);
		sx = dot_prod * camera_vec[0] - vec[i][0];
		sy = dot_prod * camera_vec[1] - vec[i][1];
		vec[i][3] = (sqrt(pow(sx, 2) + pow(sy, 2))) / dot_prod;
		cross = camera_vec[0] * vec[i][1] - camera_vec[1] * vec[i][0];
		if (cross < 0)
			vec[i][3] += RATIO;
		else
			vec[i][3] = RATIO - vec[i][3];
		vec[i][3] *= cub->image.width / 2;
		vec[i][3] /= RATIO;
		vec[i][2] = cub->image.height / dot_prod;
	}
}

void			ft_valid_sprite(t_cub *cub, double camera_vec[2], double sp_vec[100][4], int *sp_cnt)
{
	int		cnt;
	int		i;
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
		coss = (camera_vec[0] * sx + camera_vec[1] * sy) / sqrt(pow(sx, 2) + pow(sy, 2));
		if (coss > 0)
		{
			sp_vec[cnt][0] = sx;
			sp_vec[cnt][1] = sy;
			cnt++;
		}
		i++;
	}
	*sp_cnt = cnt;
}

void			ft_put_sprite(t_cub *cub, double size, double posx)
{
	int		*img_addr;
	int		*xpm_addr;
	int		color;
	int		w;
	int		h;

	img_addr = (int *)cub->image.addr;
	xpm_addr = (int *)cub->xpm.sprite.addr;
	w = -1;
	while (++w < size)
	{
		h = -1;
		while (++h < size)
		{
			if ((int)(posx - size / 2) + w <= 0 || (int)(posx - size / 2) + w >= cub->image.width)
				break ;
			else if (h - size / 2 + cub->user.horizon >= cub->image.height || h - size / 2 + cub->user.horizon < 0)
				continue ;
			color = xpm_addr[h * cub->xpm.sprite.height / (int)size * cub->xpm.sprite.sl / 4 \
				+ w * cub->xpm.sprite.width / (int)size];
			if (color != 0)
				img_addr[(int)(posx - size / 2) + w + (h - (int)size / 2 + \
						cub->user.horizon) * cub->image.sl / 4] = color;
		}
	}
}

void			ft_draw_sprite(t_cub *cub, double camera_vec[2])
{
	double		sprite_vec_size_posx[100][4];
	int		valid_sp_cnt;
	int		i;

	ft_valid_sprite(cub, camera_vec, sprite_vec_size_posx, &valid_sp_cnt);
	ft_sort(sprite_vec_size_posx, valid_sp_cnt);
	ft_get_size_posx(cub, sprite_vec_size_posx, valid_sp_cnt, camera_vec);
	i = 0;
	while (i < valid_sp_cnt)
	{
		ft_put_sprite(cub, sprite_vec_size_posx[i][2], sprite_vec_size_posx[i][3]);
		i++;
	}
}

void			ft_put_image(t_cub *cub, double camera_vec[2])
{
	int		w;
	t_dda_data	dda_data;
	double		*dist_to_wall;

	dist_to_wall = (double *)malloc(sizeof(double) * cub->image.width);
	w = -1;
	while (++w < cub->image.width)
	{
		dda_data.ray_vec[0] = camera_vec[0] + camera_vec[1] * (2 * w - cub->image.width) * RATIO / cub->image.width;
		dda_data.ray_vec[1] = camera_vec[1] - camera_vec[0] * (2 * w - cub->image.width) * RATIO / cub->image.width;
		dda_data.w = w;
		ft_draw_wall(cub, dda_data, dist_to_wall);
	}
	ft_draw_sprite(cub, camera_vec);
	free(dist_to_wall);
}

int			main_loop(t_cub *cub)
{
	double		camera_vec[2];

	camera_vec[0] = cos((double)cub->user.radian * PI / 180);
	camera_vec[1] = sin((double)cub->user.radian * PI / 180);
	ft_put_image(cub, camera_vec);
	ft_move(cub, camera_vec);
	ft_turn(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->image.img_ptr, 0, 0);
	return (0);
}

int			ft_exit(t_cub *cub)
{
	cub = 0;
	exit(0);
	return (0);
}


int			main(int argc, char *argv[])
{
	t_cub		cub;

//	if (argc > 3 || argc < 2)
//		return (0);			/ error
	cub.mlx_ptr = mlx_init();

//	ft_parse_map(&cub);			/ parse map
	ft_init_map(&cub);			//
	ft_init_cub(&cub);

	cub.win_ptr = mlx_new_window(cub.mlx_ptr, cub.image.width, cub.image.height, "junkang");
	cub.image.img_ptr = mlx_new_image(cub.mlx_ptr, cub.image.width, cub.image.height);
	cub.image.addr = mlx_get_data_addr(cub.image.img_ptr, &cub.image.bpp, &cub.image.sl, &cub.image.endian);
	if (argc == 3 && !ft_memcmp(argv[2], "--save", ft_strlen("--save")))
	{	
		ft_screenshot(&cub);
		return (0);
	}
	mlx_hook(cub.win_ptr, KEYPRESS_EVENT, KEYPRESS_MASK, ft_key_press, &cub);
	mlx_hook(cub.win_ptr, KEYRELEASE_EVENT, KEYRELEASE_MASK, ft_key_release, &cub);
	mlx_hook(cub.win_ptr, EXIT_EVENT, 0, ft_exit, &cub); 
	mlx_loop_hook(cub.mlx_ptr, main_loop, &cub);
	mlx_loop(cub.mlx_ptr);
	return (0);
}
