#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <limits.h>
# include "../minilibx_mms_20200219/mlx.h"
# include "../minilibx_opengl_20191021/mlx.h"
# include "gnl/get_next_line.h"

# include <stdio.h>		//

# define MOVE_VELO 0.05
# define TURN_VELO 1

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
# define EXIT_EVENT 17

# define KEYPRESS_MASK (1L<<0)
# define KEYRELEASE_MASK (1L<<1)

# define PI 3.1415926535897
# define RATIO 0.64940759319		// tan33
# define MAX_SP_NUM 100

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
}			t_hook_data;

typedef struct		s_user
{
	double		x;
	double		y;

	int		radian;
	int		horizon;
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
	double		ray_vec[2];
	int		w;
	int		x;		// 검토하는 블럭
	int		y;
	double		sidex;		// 초기거리 && 델타누적
	double		sidey;
	double		dx;		// 누적할 단위거리
	double		dy;
	int		directx;	// 1 오른쪽	-1 왼쪽
	int		directy;	// 1 아래	-1 위쪽
	int		flag;
	double		hit_point;
}			t_dda_data;

typedef struct		s_xpm
{
	t_image		ceil;
	t_image		floor;
	t_image		east_wall;
	t_image		west_wall;
	t_image		north_wall;
	t_image		south_wall;
	t_image		sprite;
	int		floor_color;
	int		ceil_color;
}			t_xpm;

typedef struct		s_cub
{
	void		*mlx_ptr;
	void		*win_ptr;
	int		map[500][500];
	int		map_h;

	t_image		image;
	t_user		user;
	t_hook_data	hook;
	t_xpm		xpm;

	double		sprite_pos[200][2];
	int		sprite_cnt;
}			t_cub;


//		main
int			main_loop(t_cub *cub);
void			ft_put_image(t_cub *cub, double camera_vec[2]);
int			ft_parse_file(t_cub *cub, const char *file_name);

//		init
int			ft_init_cub(t_cub *cub, int argc, char *argv[]);
void			ft_init_img_and_addr(t_cub *cub);
void			ft_init_map(t_cub *cub);
void			ft_init_hook(t_cub *cub);
//		hook
int			ft_key_press(int keycode, t_cub *cub);
int			ft_key_release(int keycode, t_cub *cub);
//		screenshot
void			ft_screenshot(t_cub *cub);
//		move
void			ft_move(t_cub *cub, double camera_vec[2]);
void			ft_turn(t_cub *cub);
//		libft
size_t			ft_strlen(const char *s);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memset(void *ptr, int value, size_t num);
int			ft_isspace(char c);
int			ft_atoi(const char *nptr);
char			*ft_strdup(const char *s);
int			ft_isnum(char digit);

//		get_next_line
//int			get_next_line(int fd, char **line);

#endif
