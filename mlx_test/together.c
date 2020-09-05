#include "../minilibx_mms_20200219/mlx.h"
#include "../minilibx_opengl_20191021/mlx.h"
#include <math.h>

typedef struct  	s_img {
	void		*img;
	char		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}               	t_img;

typedef struct		s_ptr {
	void		*mlx;
	void		*win;
}			t_ptr;


void     	       my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void			ft_draw_circle(t_img *img, int x, int y, int r, int color)
{
	for (int i = x - r; i < x + r; i++)
	{
		for (int j = y - r; j < y + r; j++)
			if (pow(x - i, 2) + pow(y - j, 2) <= r * r)
				my_mlx_pixel_put(img, i, j, color);
	}
	return ;
}

int			ft_win_close(int keycode, t_ptr *ptr)
{
	if (keycode == 53)
		mlx_destroy_window(ptr->mlx, ptr->win);
	return (0);
}	

int			main(void)
{
	t_ptr	ptr;
	t_img	img;

	ptr.mlx = mlx_init();
	ptr.win = mlx_new_window(ptr.mlx, 1152, 720, "getting_start");
	img.img = mlx_new_image(ptr.mlx, 1152, 720);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	ft_draw_circle(&img, 576, 360, 100, 0x00FF0000);
	mlx_put_image_to_window(ptr.mlx, ptr.win, img.img, 0, 0);
	mlx_hook(ptr.win, 3, 1L<<1, ft_win_close, &ptr);
	mlx_loop(ptr.mlx);
	return (0);
}
