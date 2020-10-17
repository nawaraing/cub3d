#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include "../minilibx_mms_20200219/mlx.h"
# include "../minilibx_opengl_20191021/mlx.h"

# define PI 3.1415926535897
# define RATIO 0.64940759319

# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define W_KEY 13
# define UP_KEY 126
# define DOWN_KEY 125
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define ESC_KEY 53

# define KEYPRESS_EVENT 2
# define KEYRELEASE_EVENT 3
# define KEYPRESS_MASK (1L<<0)
# define KEYRELEASE_MASK (1L<<1)

# define MOVE_VELO 0.05
# define TURN_VELO 1

# define CEIL "/Users/kangjunhyeon/Desktop/cub3d/junkang/xpm_file/sky_1.xpm"
# define FLOOR "/Users/kangjunhyeon/Desktop/cub3d/junkang/xpm_file/floor_1.xpm"
# define EAST_WALL "/Users/kangjunhyeon/Desktop/cub3d/junkang/xpm_file/wall_1.xpm"
# define WEST_WALL "/Users/kangjunhyeon/Desktop/cub3d/junkang/xpm_file/wall_2.xpm"
# define NORTH_WALL "/Users/kangjunhyeon/Desktop/cub3d/junkang/xpm_file/wall_3.xpm"
# define SOUTH_WALL "/Users/kangjunhyeon/Desktop/cub3d/junkang/xpm_file/wall_4.xpm"
# define OBJECT "/Users/kangjunhyeon/Desktop/cub3d/junkang/xpm_file/sprite_1.xpm"

typedef struct		s_hook_data
{
	int		a;
	int		s;
	int		d;
	int		w;
	int		up;
	int		down;
	int		left;
	int		right;
	int		esc;
}			t_hook_data;

typedef struct		s_user
{
	double		x;
	double		y;

	int		radian;
	int		horizon;
	double		view_angle;
}			t_user;

typedef struct		s_image
{
	void		*img_ptr;
	char		*addr;
	int		width;
	int		height;
	int		bpp;
	int		sl;
	int		endian;
}			t_image;

typedef struct		s_dda_data
{
	int		x;
	int		y;
	double		sidex;		// 초기거리 && 델타누적
	double		sidey;
	double		deltax;		// 누적할 단위거리
	double		deltay;
	int		directx;	// 1 오른쪽	-1 왼쪽
	int		directy;	// 1 아래	-1 위쪽
}			t_dda_data;


typedef struct		s_xpm
{
	t_image		ceil;
	t_image		floor;
	t_image		east_wall;
	t_image		west_wall;
	t_image		north_wall;
	t_image		south_wall;
	t_image		object;
}			t_xpm;

typedef struct		s_cub
{
	void		*mlx_ptr;
	void		*win_ptr;
	int		**map;

	t_image		image;
	t_user		user;
	t_hook_data	hook;
	t_xpm		xpm;
}			t_cub;

void			ft_init_cub(t_cub *cub);
void			ft_init_map(t_cub *cub);

void			ft_dda_draw(t_cub *cub, double ray_vec[2], int w);
t_dda_data		ft_dda_dist(t_cub *cub, double ray_vec[2]);
void			ft_dda(t_cub *cub, t_dda_data *dda_data);
void			ft_draw(t_cub *cub, t_dda_data dda_data, double ray_vec[2], int w);

int			ft_key_press(int keycode, t_cub *cub);
int			ft_key_release(int keycode, t_cub *cub);

#endif
