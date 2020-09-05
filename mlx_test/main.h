#ifndef MAIN_H
# define MAIN_H
# include "../minilibx_mms_20200219/mlx.h"
# include "../minilibx_opengl_20191021/mlx.h"
# include <stdlib.h>

# define	KEY_W		13
# define	KEY_A		0
# define	KEY_S		1
# define	KEY_D		2
# define	KEY_UP		126
# define	KEY_DOWN	125
# define	KEY_RIGHT	124
# define	KEY_LEFT	123
# define	KEY_ESC		53

# define	WIN_WIDTH	1152
# define	WIN_HEIGHT	720

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_img;

typedef struct	s_ptr
{
	void		*mlx;
	void		*win;
}		t_ptr;


typedef struct	s_keyboard
{
	int		up;
	int		down;
	int		left;
	int		right;
	int		esc;
}		t_keyboard;

typedef struct	s_mouse
{
	int		x;
	int		y;
	int		left;
	int		right;
}		t_mouse;

typedef struct	s_circle
{
	int		x;
	int		y;
}		t_circle;

typedef struct	s_cub
{
	t_img		img;
	t_ptr		ptr;
	t_keyboard	keyboard;
	t_mouse		mouse;
	t_circle	circle;
}		t_cub;

#endif
