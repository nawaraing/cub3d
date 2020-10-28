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

void			ft_put_wall(t_cub *cub, t_dda_data dda, int i, int wall_height)
{
	double		hp;
	t_image		xpm_img;
	int		*xpm_addr;
	int		*img_addr;
	int		wall_start;

	hp = dda.hit_point;
	img_addr = (int *)cub->image.addr;
	if (dda.flag == 0)
		xpm_img = cub->xpm.south_wall;
	else if (dda.flag == 1)
		xpm_img = cub->xpm.north_wall;
	else if (dda.flag == 2)
		xpm_img = cub->xpm.west_wall;
	else
		xpm_img = cub->xpm.east_wall;
	wall_start = -wall_height / 2 + cub->user.horizon;
	xpm_addr = (int *)xpm_img.addr;
	img_addr[dda.w + i * cub->image.sl / 4] = \
		xpm_addr[(i - wall_start) * xpm_img.height / wall_height * \
		xpm_img.sl / 4 + (int)((hp - (int)hp) * xpm_img.width)];
}


void			ft_draw_floor(t_cub *cub, t_dda_data dda, int i)
{
	double		pixel_dist;
	double		xpm[2];
	int		*xpm_addr;
	int		*img_addr;
	int		color;

	pixel_dist = 0.5 * cub->image.height / (i - cub->user.horizon);
	xpm[0] = cub->user.x + dda.ray_vec[0] * pixel_dist;
	xpm[1] = cub->user.y - dda.ray_vec[1] * pixel_dist;
	xpm[0] = (xpm[0] - floor(xpm[0])) * cub->xpm.floor.width;
	xpm[1] = (xpm[1] - floor(xpm[1])) * cub->xpm.floor.height;
	xpm_addr = (int *)cub->xpm.floor.addr;
	img_addr = (int *)cub->image.addr;
	if (xpm_addr == 0)
		color = cub->xpm.floor_color;
	else
		color = xpm_addr[(int)xpm[1] * cub->xpm.floor.sl / 4 + \
			(int)xpm[0]];
	img_addr[dda.w + i * cub->image.sl / 4] = color;
}

void			ft_draw_ceil(t_cub *cub, t_dda_data dda, int i)
{
	double		pixel_dist;
	double		xpm[2];
	int		*xpm_addr;
	int		*img_addr;
	int		color;

	pixel_dist = 0.5 * cub->image.height / (cub->user.horizon - i);
	xpm[0] = cub->user.x + dda.ray_vec[0] * pixel_dist;
	xpm[1] = cub->user.y - dda.ray_vec[1] * pixel_dist;
	xpm[0] = (xpm[0] - floor(xpm[0])) * cub->xpm.ceil.width;
	xpm[1] = (xpm[1] - floor(xpm[1])) * cub->xpm.ceil.height;
	xpm_addr = (int *)cub->xpm.ceil.addr;
	img_addr = (int *)cub->image.addr;
	if (xpm_addr == 0)
		color = cub->xpm.ceil_color;
	else
		color = xpm_addr[(int)xpm[1] * cub->xpm.ceil.sl / 4 + \
			(int)xpm[0]];
	img_addr[dda.w + i * cub->image.sl / 4] = color;
}

void			ft_draw_background(t_cub *cub, t_dda_data dda, double *dist_to_wall)
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

void			ft_sort(double vec[MAX_SP_NUM][5], int cnt)
{
	int		i;
	int		j;
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

void			ft_get_size_posx_dist(t_cub *cub, double vec[MAX_SP_NUM][5], int cnt, double camera[2])
{
	int		i;
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

void			ft_valid_sprite(t_cub *cub, double camera[2], double vec[MAX_SP_NUM][5], int *sp_cnt)
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

int			ft_get_color(t_cub *cub, double vec[5], int w, int h)
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

void			ft_put_sprite(t_cub *cub, double vec[5], double *dist_to_wall)
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

void			ft_draw_sprite(t_cub *cub, double camera[2], double *dist_to_wall)
{
	double		sp_vec_size_posx_dist[MAX_SP_NUM][5];
	int		valid_sp_cnt;
	int		i;

	ft_valid_sprite(cub, camera, sp_vec_size_posx_dist, &valid_sp_cnt);
	ft_sort(sp_vec_size_posx_dist, valid_sp_cnt);
	ft_get_size_posx_dist(cub, sp_vec_size_posx_dist, valid_sp_cnt, camera);
	i = -1;
	while (++i < valid_sp_cnt)
		ft_put_sprite(cub, sp_vec_size_posx_dist[i], dist_to_wall);
}

void			ft_put_image(t_cub *cub, double camera[2])
{
	int		w;
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

int			main_loop(t_cub *cub)
{
	double		camera_vec[2];

	camera_vec[0] = cos((double)cub->user.radian * PI / 180);
	camera_vec[1] = sin((double)cub->user.radian * PI / 180);
	ft_put_image(cub, camera_vec);
	ft_move(cub, camera_vec);
	ft_turn(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, \
			cub->image.img_ptr, 0, 0);
	return (0);
}

int			ft_exit(t_cub *cub)
{
	cub = 0;
	exit(0);
	return (0);
}

char			ft_check_identifier(char *buf)
{
	if (buf[0] == 'R')
		return ('r');
	else if (buf[0] == 'N' && buf[1] == 'O')
		return ('N');
	else if (buf[0] == 'S' && buf[1] == 'O')
		return ('S');
	else if (buf[0] == 'W' && buf[1] == 'E')
		return ('W');
	else if (buf[0] == 'E' && buf[1] == 'A')
		return ('E');
	else if (buf[0] == 'S')
		return ('s');
	else if (buf[0] == 'F')
		return ('f');
	else if (buf[0] == 'C')
		return ('c');
	else if (buf[0] == '\n')
		return (0);
	return (-1);
}

int			ft_parse_render(t_cub *cub, char *buf)
{
	if (*(buf++) != 'R')
		return (-1);
	if (!ft_isspace(*buf))
		return (-1);
	if (cub->image.width > ft_atoi(buf))
		cub->image.width = ft_atoi(buf);
	while (*buf && ft_isspace(*buf))
		buf++;
	while (*buf && ft_isnum(*buf))
		buf++;
	if (cub->image.height > ft_atoi(buf))
		cub->image.height = ft_atoi(buf);
	while (*buf && ft_isspace(*buf))
		buf++;
	if (*buf == 0)
		return (-1);
	while (*buf && ft_isnum(*buf))
		buf++;
	if (*buf)
		return (-1);
	return (1);
}

int			ft_parse_sprite(t_cub *cub, char *buf)
{
	char		*path;
	void		*tmp;

	if (*(buf++) != 'S')
		return (-1);
	if (!ft_isspace(*buf))
		return (-1);
	while (*buf && ft_isspace(*buf))
		buf++;
	path = ft_strdup(buf);
	tmp = mlx_xpm_file_to_image(cub->mlx_ptr, path, \
			&(cub->xpm.sprite.width), \
			&(cub->xpm.sprite.height));
	free(path);
	if (tmp == 0)
		return (-1);
	cub->xpm.sprite.img_ptr = tmp;
	cub->xpm.sprite.addr = mlx_get_data_addr(tmp, \
			&(cub->xpm.sprite.bpp), &(cub->xpm.sprite.sl),\
			&(cub->xpm.sprite.endian));
	while (*buf && !ft_isspace(*buf))
		buf++;
	if (*buf)
		return (-1);
	return (1);
}

int			ft_parse_north(t_cub *cub, char *buf)
{
	char		*path;
	void		*tmp;

	if (*buf != 'N' || *(buf + 1) != 'O' || !ft_isspace(*(buf + 2)))
		return (-1);
	buf += 2 * sizeof(char);
	while (*buf && ft_isspace(*buf))
		buf++;
	path = ft_strdup(buf);
	tmp = mlx_xpm_file_to_image(cub->mlx_ptr, path, \
			&(cub->xpm.north_wall.width), \
			&(cub->xpm.north_wall.height));
	free(path);
	if (tmp == 0)
		return (-1);
	cub->xpm.north_wall.img_ptr = tmp;
	cub->xpm.north_wall.addr = mlx_get_data_addr(tmp, \
			&(cub->xpm.north_wall.bpp), &(cub->xpm.north_wall.sl),\
			&(cub->xpm.north_wall.endian));
	while (*buf && !ft_isspace(*buf))
		buf++;
	if (*buf)
		return (-1);
	return (1);
}

int			ft_parse_south(t_cub *cub, char *buf)
{
	char		*path;
	void		*tmp;

	if (*buf != 'S' || *(buf + 1) != 'O' || !ft_isspace(*(buf + 2)))
		return (-1);
	buf += 2 * sizeof(char);
	while (*buf && ft_isspace(*buf))
		buf++;
	path = ft_strdup(buf);
	tmp = mlx_xpm_file_to_image(cub->mlx_ptr, path, \
			&(cub->xpm.south_wall.width), \
			&(cub->xpm.south_wall.height));
	free(path);
	if (tmp == 0)
		return (-1);
	cub->xpm.south_wall.img_ptr = tmp;
	cub->xpm.south_wall.addr = mlx_get_data_addr(tmp, \
			&(cub->xpm.south_wall.bpp), &(cub->xpm.south_wall.sl),\
			&(cub->xpm.south_wall.endian));
	while (*buf && !ft_isspace(*buf))
		buf++;
	if (*buf)
		return (-1);
	return (1);
}

int			ft_parse_east(t_cub *cub, char *buf)
{
	char		*path;
	void		*tmp;

	if (*buf != 'E' || *(buf + 1) != 'A' || !ft_isspace(*(buf + 2)))
		return (-1);
	buf += 2 * sizeof(char);
	while (*buf && ft_isspace(*buf))
		buf++;
	path = ft_strdup(buf);
	tmp = mlx_xpm_file_to_image(cub->mlx_ptr, path, \
			&(cub->xpm.east_wall.width), \
			&(cub->xpm.east_wall.height));
	free(path);
	if (tmp == 0)
		return (-1);
	cub->xpm.east_wall.img_ptr = tmp;
	cub->xpm.east_wall.addr = mlx_get_data_addr(tmp, \
			&(cub->xpm.east_wall.bpp), &(cub->xpm.east_wall.sl),\
			&(cub->xpm.east_wall.endian));
	while (*buf && !ft_isspace(*buf))
		buf++;
	if (*buf)
		return (-1);
	return (1);
}

int			ft_parse_west(t_cub *cub, char *buf)
{
	char		*path;
	void		*tmp;

	if (*buf != 'W' || *(buf + 1) != 'E' || !ft_isspace(*(buf + 2)))
		return (-1);
	buf += 2 * sizeof(char);
	while (*buf && ft_isspace(*buf))
		buf++;
	path = ft_strdup(buf);
	tmp = mlx_xpm_file_to_image(cub->mlx_ptr, path, \
			&(cub->xpm.west_wall.width), \
			&(cub->xpm.west_wall.height));
	free(path);
	if (tmp == 0)
		return (-1);
	cub->xpm.west_wall.img_ptr = tmp;
	cub->xpm.west_wall.addr = mlx_get_data_addr(tmp, \
			&(cub->xpm.west_wall.bpp), &(cub->xpm.west_wall.sl),\
			&(cub->xpm.west_wall.endian));
	while (*buf && !ft_isspace(*buf))
		buf++;
	if (*buf)
		return (-1);
	return (1);
}

int			ft_parse_path(t_cub *cub, char *buf, char type)
{
	char		*path;
	void		*tmp;
	t_image		*xpm_img;

	if (*buf != '.' || *(buf + 1) != '/')
		return (-1);
	if (type == 'F')
		xpm_img = &(cub->xpm.floor);
	else
		xpm_img = &(cub->xpm.ceil);
	path = ft_strdup(buf);
	tmp = mlx_xpm_file_to_image(cub->mlx_ptr, path, \
			&((*xpm_img).width), &((*xpm_img).height));
	free(path);
	if (tmp == 0)
		return (-1);
	(*xpm_img).img_ptr = tmp;
	(*xpm_img).addr = mlx_get_data_addr(tmp, &((*xpm_img).bpp), \
			&((*xpm_img).sl), &((*xpm_img).endian));
	while (*buf && !ft_isspace(*buf))
		buf++;
	if (*buf)
		return (-1);
	return (1);
}

int			ft_valid_num(int num)
{
	if (num < 0 || num > 255)
		return (-1);
	return (1);
}

int			ft_parse_color(char *buf)
{
	int		color;

	if (!ft_isnum(*buf) || ft_valid_num(ft_atoi(buf)) == -1)
		return (-1);
	color = 0;
	color |= (ft_atoi(buf) << 16);
	while (*buf && ft_isnum(*buf))
		buf++;
	if (*(buf++) != ',' || !ft_isnum(*buf) || \
			ft_valid_num(ft_atoi(buf)) == -1)
		return (-1);
	color |= (ft_atoi(buf) << 8);
	while (*buf && ft_isnum(*buf))
		buf++;
	if (*(buf++) != ',' || !ft_isnum(*buf) || \
			ft_valid_num(ft_atoi(buf)) == -1)
		return (-1);
	color |= ft_atoi(buf);
	while (*buf && ft_isnum(*buf))
		buf++;
	if (*buf)
		return (-1);
	return (color);
}

int			ft_parse_floor_ceil(t_cub *cub, char *buf)
{
	char		type;
	int		color;

	if (*buf != 'F' && *buf != 'C')
		return (-1);
	type = *buf;
	buf++;
	if (!ft_isspace(*buf))
		return (-1);
	while (*buf && ft_isspace(*buf))
		buf++;
	if (*buf == '.' && *(buf + 1) == '/')
	{
		if (ft_parse_path(cub, buf, type) == -1)
			return (-1);
	}
	else
		if ((color = ft_parse_color(buf)) == -1)
			return (-1);
	if (type == 'F')
		cub->xpm.floor_color = color;
	else
		cub->xpm.ceil_color = color;
	return (1);
}

int			ft_parse_identifier(t_cub *cub, char *buf, int id)
{
	static int		cnt = 0;

	if (cnt >= 8)
		return (8);
	if (id == 'r' && ft_parse_render(cub, buf) == -1)
		return (-1);
	else if (id == 'N' && ft_parse_north(cub, buf) == -1)
		return (-1);
	else if (id == 'S' && ft_parse_south(cub, buf) == -1)
		return (-1);
	else if (id == 'W' && ft_parse_west(cub, buf) == -1)
		return (-1);
	else if (id == 'E' && ft_parse_east(cub, buf) == -1)
		return (-1);
	else if (id == 's' && ft_parse_sprite(cub, buf) == -1)
		return (-1);
	else if ((id == 'f' || id == 'c') && \
			ft_parse_floor_ceil(cub, buf) == -1)
		return (-1);
	else if (id == 0)
		return (0);
	else if (id == -1)
		return (-1);
	cnt++;
	return (cnt);
}

void			ft_save_user(t_cub *cub, char c, int i)
{
	if (c == 'E')
		cub->user.radian = 0;
	else if (c == 'N')
		cub->user.radian = 90;
	else if (c == 'W')
		cub->user.radian = 180;
	else if (c == 'S')
		cub->user.radian = 270;
	cub->user.x = (double)i + 0.5;
	cub->user.y = (double)cub->map_h + 0.5;
	cub->map[cub->map_h][i] = 3;
}

void			ft_parse_map(t_cub *cub, char *buf)
{
	int		i;

	i = -1;
	while (*(buf + ++i))
	{
		if (*(buf + i) == '0')
			cub->map[cub->map_h][i] = 9;
		else if (*(buf + i) == '1')
			cub->map[cub->map_h][i] = 1;
		else if (*(buf + i) == '2')
		{
			cub->map[cub->map_h][i] = 2;
			cub->sprite_pos[cub->sprite_cnt][0] = i + 0.5;
			cub->sprite_pos[cub->sprite_cnt][1] = cub->map_h + 0.5;
			cub->sprite_cnt++;
		}
		else if (*(buf + i)  == ' ')
			cub->map[cub->map_h][i] = ' ';
		else
			ft_save_user(cub, *(buf + i), i);
	}
	(cub->map_h)++;
}

int			ft_check_vertical(t_cub *cub, int i, int j, int set)
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

int			ft_check_one_user(t_cub *cub)
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

int			ft_iscub(const char *file_name)
{
	while (*file_name)
		file_name++;
	if (ft_memcmp(file_name - 4, ".cub", ft_strlen(".cub")))
		return (-1);
	return (1);
}

int			ft_parse_file(t_cub *cub, const char *file_name)
{
	int		fd;
	int		ret;
	char		*buf;
	char		id;
	int		cnt;

	if (ft_iscub(file_name) == -1)
		return (-1);
	fd = open(file_name, O_RDONLY);
	id = 0;
	while ((ret = get_next_line(fd, &buf)) > 0)
	{
		id = ft_check_identifier(buf);
		if (cnt == 8)
			ft_parse_map(cub, buf);
		cnt = ft_parse_identifier(cub, buf, id);
		free(buf);
		if (cnt == -1)
			break ;
	}
	free(buf);
	close(fd);
	if (ret == -1 || cnt == -1 || ft_valid_map(cub) == -1)
		return (-1);
	return (1);
}

int			main(int argc, char *argv[])
{
	t_cub		cub;

	if (ft_init_cub(&cub, argc, argv) != 1)
		return (0);
	cub.win_ptr = mlx_new_window(cub.mlx_ptr, cub.image.width, \
			cub.image.height, "junkang");
	cub.image.img_ptr = mlx_new_image(cub.mlx_ptr, cub.image.width, \
			cub.image.height);
	cub.image.addr = mlx_get_data_addr(cub.image.img_ptr, &cub.image.bpp, \
			&cub.image.sl, &cub.image.endian);
	if (argc == 3)
	{
		if (!ft_memcmp(argv[2], "--save", ft_strlen("--save")))
			ft_screenshot(&cub);
		return (0);
	}
	mlx_hook(cub.win_ptr, KEYPRESS_EVENT, KEYPRESS_MASK, \
			ft_key_press, &cub);
	mlx_hook(cub.win_ptr, KEYRELEASE_EVENT, KEYRELEASE_MASK, \
			ft_key_release, &cub);
	mlx_hook(cub.win_ptr, EXIT_EVENT, 0, ft_exit, &cub);
	mlx_loop_hook(cub.mlx_ptr, main_loop, &cub);
	mlx_loop(cub.mlx_ptr);
	return (0);
}
