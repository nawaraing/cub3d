/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:24:09 by junkang           #+#    #+#             */
/*   Updated: 2020/10/30 19:56:22 by junkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include <limits.h>
# include <CoreGraphics/CGDisplayConfiguration.h>
# include "../mlx/mlx.h"
# include "../gnl/get_next_line.h"
# include <stdio.h>

# define MOVE_VELO			0.05
# define TURN_VELO			1

# define A_KEY				0
# define S_KEY				1
# define D_KEY				2
# define W_KEY				13
# define UP_KEY				126
# define DOWN_KEY			125
# define LEFT_KEY			123
# define RIGHT_KEY			124
# define ESC_KEY			53

# define KEYPRESS_EVENT		2
# define KEYRELEASE_EVENT	3
# define EXIT_EVENT			17

# define PI					3.1415926535897
# define RATIO				0.64940759319
# define MAX_SP_NUM			5
# define MAX_MAP_NUM		500

typedef struct				s_hook_data
{
	int		a;
	int		s;
	int		d;
	int		w;
	int		up;
	int		down;
	int		left;
	int		right;
}							t_hook_data;

typedef struct				s_user
{
	double		x;
	double		y;

	int			radian;
	int			horizon;
}							t_user;

typedef struct				s_image
{
	void		*img_ptr;
	char		*addr;
	int			width;
	int			height;
	int			bpp;
	int			sl;
	int			endian;
}							t_image;

typedef struct				s_dda_data
{
	double		ray_vec[2];
	int			w;
	int			x;
	int			y;
	double		sidex;
	double		sidey;
	double		dx;
	double		dy;
	int			directx;
	int			directy;
	int			flag;
	double		hit_point;
}							t_dda_data;

typedef struct				s_xpm
{
	t_image		ceil;
	t_image		floor;
	t_image		east_wall;
	t_image		west_wall;
	t_image		north_wall;
	t_image		south_wall;
	t_image		sprite;
	int			floor_color;
	int			ceil_color;
}							t_xpm;

typedef struct				s_cub
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			map[500][500];
	int			map_h;

	t_image		image;
	t_user		user;
	t_hook_data	hook;
	t_xpm		xpm;

	double		sprite_pos[200][2];
	int			sprite_cnt;
}							t_cub;

int							main_loop(t_cub *cub);
void						ft_put_image(t_cub *cub, double camera[2]);
void						ft_put_wall(t_cub *cub, t_dda_data dda, int i,\
							int wall_height);
void						ft_draw_floor(t_cub *cub, t_dda_data dda, int i);
void						ft_draw_ceil(t_cub *cub, t_dda_data dda, int i);
void						ft_valid_sprite(t_cub *cub, double camera[2],\
							double vec[MAX_SP_NUM][5], int *sp_cnt);
void						ft_sort(double vec[MAX_SP_NUM][5], int cnt);
void						ft_get_size_posx_dist(t_cub *cub,\
							double vec[MAX_SP_NUM][5], int cnt,\
							double camera[2]);
void						ft_put_sprite(t_cub *cub, double vec[5],\
							double *dist_to_wall);
void						ft_dda(t_cub *cub, t_dda_data *dda_data);
void						ft_dda_dist(t_cub *cub, t_dda_data *dda_data);
void						ft_hit_point(t_cub *cub, t_dda_data *dda);
int							ft_init_cub(t_cub *cub, int argc, char *argv[]);
int							ft_parse_file(t_cub *cub, const char *file_name);
int							ft_parse_render(t_cub *cub, char *buf);
int							ft_parse_sprite(t_cub *cub, char *buf);
int							ft_valid_map(t_cub *cub);
void						ft_parse_map(t_cub *cub, char *buf);
int							ft_parse_north(t_cub *cub, char *buf);
int							ft_parse_south(t_cub *cub, char *buf);
int							ft_parse_east(t_cub *cub, char *buf);
int							ft_parse_west(t_cub *cub, char *buf);
int							ft_parse_floor_ceil(t_cub *cub, char *buf);
int							ft_key_press(int keycode, t_cub *cub);
int							ft_key_release(int keycode, t_cub *cub);
int							ft_exit(t_cub *cub);
void						ft_screenshot(t_cub *cub);
void						ft_turn(t_cub *cub);
void						ft_move(t_cub *cub, double camera_vec[2]);
size_t						ft_strlen(const char *s);
int							ft_memcmp(const void *s1, const void *s2, size_t n);
void						*ft_memset(void *ptr, int value, size_t num);
int							ft_atoi(const char *nptr);
char						*ft_strdup(const char *s);
int							ft_isspace(char c);
int							ft_isnum(char digit);

#endif
