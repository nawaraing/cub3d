#include "cub3d.h"
#include <stdio.h>				//

t_dda_data		ft_dda_dist(t_cub *cub, double ray_vec[2])
{
	t_dda_data	dda_data;

	dda_data.x = (int)cub->user.x;
	dda_data.y = (int)cub->user.y;
	dda_data.deltax = 1 / fabs(ray_vec[0]);
	dda_data.deltay = 1 / fabs(ray_vec[1]);
	if (ray_vec[0] < 0)
	{
		dda_data.directx = -1;
		dda_data.sidex = (cub->user.x - dda_data.x) * dda_data.deltax;
	}
	else
	{
		dda_data.directx = 1;
		dda_data.sidex = (1 + dda_data.x - cub->user.x) * dda_data.deltax;
	}
	if (ray_vec[1] < 0)
	{
		dda_data.directy = 1;
		dda_data.sidey = (1 + dda_data.y - cub->user.y) * dda_data.deltay;
	}
	else
	{
		dda_data.directy = -1;
		dda_data.sidey = (cub->user.y - dda_data.y) * dda_data.deltay;
	}
//	printf("%d %d %f %f\n", dda_data.x, dda_data.y, cub->user.x, cub->user.y);
//	printf("%f %f %f %f\n", dda_data.sidex, dda_data.sidey, dda_data.deltax, dda_data.deltay);
	return (dda_data);
}

void			ft_dda(t_cub *cub, t_dda_data *dda_data)
{
//	printf("direct x: %d\ty: %d\n", dda_data.directx, dda_data.directy);
	while (1)
	{
		if (dda_data->sidex > dda_data->sidey)
		{
			dda_data->y += dda_data->directy;
//			printf("!!%f %f %d %d\n", dda_data->sidex, dda_data->sidey, dda_data->x, dda_data->y);
			if (1 == cub->map[dda_data->y][dda_data->x])
				break ;
			dda_data->sidey += dda_data->deltay;
		}
		else
		{
			dda_data->x += dda_data->directx;
//			printf("!!%f %f %d %d\n", dda_data->sidex, dda_data->sidey, dda_data->x, dda_data->y);
			if (1 == cub->map[dda_data->y][dda_data->x])
				break ;
			dda_data->sidex += dda_data->deltax;
		}
	}
//	printf("\n");
}

double			ft_hit_point(t_cub *cub, t_dda_data dda_data, double ray_vec[2], double *minn, int *flag)
{
	double		hit_point;

	if (dda_data.sidex > dda_data.sidey)
	{
		(*minn) = dda_data.sidey;
		if (dda_data.directy > 0)
			*flag = 0;
		else
			*flag = 1;
		hit_point = (ray_vec[1] == 0) ? cub->user.x : cub->user.x + \
			   (cub->user.y - dda_data.y - *flag) * ray_vec[0] / ray_vec[1];
	}
	else
	{
		(*minn) = dda_data.sidex;
		if (dda_data.directx > 0)
			*flag = 2;
		else
			*flag = 3;
		hit_point = (ray_vec[0] == 0) ? cub->user.y : cub->user.y - \
			   (dda_data.x - cub->user.x + (*flag - 2)) * ray_vec[1] / ray_vec[0];
	}
	return (hit_point);
}

void			ft_draw(t_cub *cub, t_dda_data dda_data, double ray_vec[2], int w)
{
	int		wall_height;
	int		flag;
	double		minn;
	double		hit_point;
	int		wall_start;
	int		wall_end;
	int		*temp;
	int		*temp2;

//	printf("%f %f %d %d\n", dda_data.sidex, dda_data.sidey, dda_data.x, dda_data.y);
	hit_point = ft_hit_point(cub, dda_data, ray_vec, &minn, &flag);
//	printf("x: %f, y: %f\n", cub->user.x, cub->user.y);
//	printf("minn : %f\n", minn);				//
	wall_height = (int)(cub->image.height / minn);
	wall_start = -wall_height / 2 + cub->user.horizon;
	wall_end = wall_height / 2 + cub->user.horizon;
//	printf("test height: %d\n", wall_height);		//
	for (int i = 0; i < cub->image.height; i++)
	{
		temp = (int *)cub->image.addr;
		if (i >= wall_start && i <= wall_end)
		{
			t_image		ttt;
			if (flag == 0)
				ttt = cub->xpm.south_wall;
			else if (flag == 1)
				ttt = cub->xpm.north_wall;
			else if (flag == 2)
				ttt = cub->xpm.west_wall;
			else
				ttt = cub->xpm.east_wall;
			temp2 = (int *)ttt.addr;
			temp[w + i * cub->image.sl / 4] = temp2[(i - wall_start) * ttt.height / wall_height * ttt.sl / 4 + (int)((hit_point - (int)hit_point) * ttt.width)];
		}
		else
			temp[w + i * cub->image.sl / 4] = 0;
	}
}

void			ft_dda_draw(t_cub *cub, double ray_vec[2], int w)
{
	t_dda_data	dda_data;


	dda_data = ft_dda_dist(cub, ray_vec);
	ft_dda(cub, &dda_data);
	ft_draw(cub, dda_data, ray_vec, w);
}

void			ft_move(t_cub *cub, double camera_vec[2])
{
	t_hook_data		hk;
	double			next_x = 0.0, next_y = 0.0;
	double			nn_x = 0.0, nn_y = 0.0;

	hk = cub->hook;
	if (hk.w && !hk.a && !hk.s && !hk.d)
	{
		next_x = cub->user.x + MOVE_VELO * camera_vec[0];
		next_y = cub->user.y - MOVE_VELO * camera_vec[1];
		nn_x = cub->user.x + 2 * MOVE_VELO * camera_vec[0];
		nn_y = cub->user.y - 2 * MOVE_VELO * camera_vec[1];
	}
	else if (!hk.w && !hk.a && hk.s && !hk.d)
	{
		next_x = cub->user.x - MOVE_VELO * camera_vec[0];
		next_y = cub->user.y + MOVE_VELO * camera_vec[1];
		nn_x = cub->user.x - 2 * MOVE_VELO * camera_vec[0];
		nn_y = cub->user.y + 2 * MOVE_VELO * camera_vec[1];
	}
	else if (!hk.w && hk.a && !hk.s && !hk.d)
	{
		next_x = cub->user.x + MOVE_VELO * -camera_vec[1];
		next_y = cub->user.y - MOVE_VELO * camera_vec[0];;
		nn_x = cub->user.x + 2 * MOVE_VELO * -camera_vec[1];
		nn_y = cub->user.y - 2 * MOVE_VELO * camera_vec[0];;
	}
	else if (!hk.w && !hk.a && !hk.s && hk.d)
	{
		next_x = cub->user.x - MOVE_VELO * -camera_vec[1];
		next_y = cub->user.y + MOVE_VELO * camera_vec[0];;
		nn_x = cub->user.x - 2 *MOVE_VELO * -camera_vec[1];
		nn_y = cub->user.y + 2 * MOVE_VELO * camera_vec[0];;
	}
	if (!(cub->map[(int)nn_y][(int)nn_x]))
	{
		cub->user.x = next_x;
		cub->user.y = next_y;
	}
}

void			ft_turn(t_cub *cub)
{
	t_hook_data		hk;
//	if (hk.up && !hk.down && !hk.left && !hk.right)
//		cub->user.radian 
	hk = cub->hook;
	if (!hk.up && !hk.down && hk.left && !hk.right)
		cub->user.radian = (cub->user.radian + TURN_VELO) % 360;
	else if (!hk.up && !hk.down && !hk.left && hk.right)
		cub->user.radian = (cub->user.radian - TURN_VELO + 360) % 360;
//	if (hk.up && !hk.down && !hk.left && !hk.right)
//	if (hk.up && !hk.down && !hk.left && !hk.right)
}

int			main_loop(t_cub *cub)
{
	double		camera_vec[2];
	double		ray_vec[2];
	int		w;

	camera_vec[0] = cos((double)cub->user.radian * PI / 180);
	camera_vec[1] = sin((double)cub->user.radian * PI / 180);
	ft_move(cub, camera_vec);
	ft_turn(cub);
	w = -1;
	while (++w < cub->image.width)
	{
		ray_vec[0] = camera_vec[0] + camera_vec[1] * (2 * w - cub->image.width) * RATIO / cub->image.width;
		ray_vec[1] = camera_vec[1] - camera_vec[0] * (2 * w - cub->image.width) * RATIO / cub->image.width;
		ft_dda_draw(cub, ray_vec, w);
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->image.img_ptr, 0, 0);
	return (0);
}

int			main(void)
{
	t_cub		cub;

	cub.mlx_ptr = mlx_init();
	ft_init_cub(&cub);
	ft_init_map(&cub);

	cub.win_ptr = mlx_new_window(cub.mlx_ptr, cub.image.width, cub.image.height, "junkang");
	cub.image.img_ptr = mlx_new_image(cub.mlx_ptr, cub.image.width, cub.image.height);
	cub.image.addr = mlx_get_data_addr(cub.image.img_ptr, &cub.image.bpp, &cub.image.sl, &cub.image.endian);
	mlx_hook(cub.win_ptr, KEYPRESS_EVENT, KEYPRESS_MASK, ft_key_press, &cub);
	mlx_hook(cub.win_ptr, KEYRELEASE_EVENT, KEYRELEASE_MASK, ft_key_release, &cub);
	mlx_loop_hook(cub.mlx_ptr, main_loop, &cub);
	mlx_loop(cub.mlx_ptr);
	return (0);
}
