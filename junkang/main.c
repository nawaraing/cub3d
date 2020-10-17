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

void			ft_draw(t_cub *cub, t_dda_data dda_data, double ray_vec[2], int w, double *dist_to_wall)
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
	dist_to_wall[w] = minn;
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
		else if (cub->user.horizon < i)
		{
			double	pixel_dist = 0.5 * cub->image.height / (i - cub->user.horizon);
			double	xpm_x = cub->user.x + ray_vec[0] * pixel_dist;
			double	xpm_y = cub->user.y - ray_vec[1] * pixel_dist;
			xpm_x = (xpm_x - floor(xpm_x)) * cub->xpm.floor.width;
			xpm_y = (xpm_y - floor(xpm_y)) * cub->xpm.floor.height;
			temp2 = (int *)cub->xpm.floor.addr;
			temp[w + i * cub->image.sl / 4] = temp2[(int)(xpm_y) * cub->xpm.floor.sl / 4 + (int)xpm_x];
		}
		else
		{
			double	pixel_dist = 0.5 * cub->image.height / (cub->user.horizon - i);
			double	xpm_x = cub->user.x + ray_vec[0] * pixel_dist;
			double	xpm_y = cub->user.y - ray_vec[1] * pixel_dist;
			xpm_x = (xpm_x - floor(xpm_x)) * cub->xpm.ceil.width;
			xpm_y = (xpm_y - floor(xpm_y)) * cub->xpm.ceil.height;
			temp2 = (int *)cub->xpm.ceil.addr;
			temp[w + i * cub->image.sl / 4] = temp2[(int)(xpm_y) * cub->xpm.ceil.sl / 4 + (int)xpm_x];
		}
	}
	
}

void			ft_dda_draw(t_cub *cub, double ray_vec[2], int w, double *dist_to_wall)
{
	t_dda_data	dda_data;

	dda_data = ft_dda_dist(cub, ray_vec);
	ft_dda(cub, &dda_data);
	ft_draw(cub, dda_data, ray_vec, w, dist_to_wall);
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

void			ft_sort(double vec[100][2], int cnt)
{
	double		tmp[2];
	for (int j = cnt; j > 1; j--)
	{
		for (int i = 1; i < j; i++)
		{
			if (sqrt(pow(vec[i - 1][0], 2) + pow(vec[i - 1][1], 2)) < sqrt(pow(vec[i][0], 2) + pow(vec[i][1], 2)))
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

void			ft_sprite_screen(t_cub *cub, double vec[100][2], int cnt, double camera_vec[2], double screen_x[100], double sp_size[100])
{
	double		cross, dot_prod;
	double		sx, sy;
	double		tangent = tan(33 * PI / 180);

	for (int i = 0; i < cnt; i++)
	{
		dot_prod = (camera_vec[0] * vec[i][0] + camera_vec[1] * vec[i][1]);
		sx = dot_prod * camera_vec[0] - vec[i][0];
		sy = dot_prod * camera_vec[1] - vec[i][1];
		screen_x[i] = (sqrt(pow(sx, 2) + pow(sy, 2))) / dot_prod;
		cross = camera_vec[0] * vec[i][1] - camera_vec[1] * vec[i][0];
		if (cross < 0)
			screen_x[i] += tangent;
		else
			screen_x[i] = tangent - screen_x[i];
		screen_x[i] *= cub->image.width / 2;
		screen_x[i] /= tangent;
		sp_size[i] = cub->image.height / dot_prod;
	}
}

void			ft_sprite_draw(t_cub *cub, double camera_vec[2], double *dist_to_wall)
{
	double		sx, sy, coss;
	double		use_sp_vec[100][2];
	double		screen_x[100];
	double		use_sp_size[100];
	int		use_sp_cnt;


	dist_to_wall = 0;
	use_sp_cnt = 0;
	for (int i = 0;i < cub->sprite_cnt; i++)
	{
		sx = cub->sprite_pos[i][0];
		sy = cub->sprite_pos[i][1];
		sx = (sx - cub->user.x);
		sy = (cub->user.y - sy);
		coss = (camera_vec[0] * sx + camera_vec[1] * sy) / sqrt(pow(sx, 2) + pow(sy, 2));
		if (coss > 0)
		{
			use_sp_vec[use_sp_cnt][0] = sx;
			use_sp_vec[use_sp_cnt][1] = sy;
			use_sp_cnt++;
		}
	}
	ft_sort(use_sp_vec, use_sp_cnt);
/*
	for (int i = 0; i < use_sp_cnt; i++)
	{
		use_sp_dist[i] = sqrt(pow(use_sp_vec[i][0], 2) + pow(use_sp_vec[i][1], 2));
		printf("dist %d : %f\n", i, use_sp_dist[i]);
	}
*/
	ft_sprite_screen(cub, use_sp_vec, use_sp_cnt, camera_vec, screen_x, use_sp_size);
	/*
	for (int i = 0; i < use_sp_cnt; i++)
	{
//		printf("screen_x [%d] : %f\n", i, screen_x[i]);
		printf("use_sp_size [%d] : %f\n", i, use_sp_size[i]);
	}
	*/
	for (int i = 0; i < use_sp_cnt; i++)
	{
		t_image		screen, xpm;
		int		*screen_add, *xpm_add;
		int		start_sprite, end_sprite;

		screen = cub->image;
		xpm = cub->xpm.sprite;
		screen_add = (int *)screen.addr;
		xpm_add = (int *)xpm.addr;
		start_sprite = screen_x[i] - use_sp_size[i] / 2;
		end_sprite = screen_x[i] + use_sp_size[i] / 2;
		for (int w = 0; w < use_sp_size[i]; w++)
		{
			for (int h = 0; h < use_sp_size[i]; h++)
			{
				if (start_sprite + w <= 0 || start_sprite + w >= cub->image.width)
					break ;
				else if (h - use_sp_size[i] / 2 + cub->user.horizon >= screen.height || h - use_sp_size[i] / 2 + cub->user.horizon < 0)
					continue ;
				int		color = xpm_add[h * xpm.height / (int)use_sp_size[i] * xpm.sl / 4 + w * xpm.width / (int)use_sp_size[i]];
				if (color != 0)
					screen_add[start_sprite + w + (h - (int)use_sp_size[i] / 2 + cub->user.horizon) * cub->image.sl / 4] = color;
			}
		}
	}
}

int			main_loop(t_cub *cub)
{
	double		camera_vec[2];
	double		ray_vec[2];
	int		w;
	double		*dist_to_wall;

	camera_vec[0] = cos((double)cub->user.radian * PI / 180);
	camera_vec[1] = sin((double)cub->user.radian * PI / 180);
	ft_move(cub, camera_vec);
	ft_turn(cub);
	dist_to_wall = (double *)malloc(sizeof(double) * cub->image.width);
	w = -1;
	while (++w < cub->image.width)
	{
		ray_vec[0] = camera_vec[0] + camera_vec[1] * (2 * w - cub->image.width) * RATIO / cub->image.width;
		ray_vec[1] = camera_vec[1] - camera_vec[0] * (2 * w - cub->image.width) * RATIO / cub->image.width;
		ft_dda_draw(cub, ray_vec, w, dist_to_wall);
	}
	/*
	for (int i = 0; i < cub->image.width; i++)
	{
		if (dist_to_wall[i - 1] != dist_to_wall[i])
			printf("%.12f\t", dist_to_wall[i]);
	}
	*/
	ft_sprite_draw(cub, camera_vec, dist_to_wall);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->image.img_ptr, 0, 0);
	return (0);
}

int			main(void)
{
	t_cub		cub;

	cub.mlx_ptr = mlx_init();
	ft_init_map(&cub);
	ft_init_cub(&cub);

	cub.win_ptr = mlx_new_window(cub.mlx_ptr, cub.image.width, cub.image.height, "junkang");
	cub.image.img_ptr = mlx_new_image(cub.mlx_ptr, cub.image.width, cub.image.height);
	cub.image.addr = mlx_get_data_addr(cub.image.img_ptr, &cub.image.bpp, &cub.image.sl, &cub.image.endian);
	mlx_hook(cub.win_ptr, KEYPRESS_EVENT, KEYPRESS_MASK, ft_key_press, &cub);
	mlx_hook(cub.win_ptr, KEYRELEASE_EVENT, KEYRELEASE_MASK, ft_key_release, &cub);
	mlx_loop_hook(cub.mlx_ptr, main_loop, &cub);
	mlx_loop(cub.mlx_ptr);
	return (0);
}
