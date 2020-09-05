#include "main.h"
#include <stdio.h>

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
			if ((x - i) * (x - i) + (y - j) * (y - j) <= r * r)
				my_mlx_pixel_put(img, i, j, color);
	}
	return ;
}

int			ft_key_press(int keycode, t_cub *cub)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		cub->keyboard.up = 1;
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		cub->keyboard.left = 1;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		cub->keyboard.down = 1;
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		cub->keyboard.right = 1;
	return (0);
}

int			ft_key_release(int keycode, t_cub *cub)
{
	if (keycode == KEY_ESC)
		exit(0);
	else if (keycode == KEY_W || keycode == KEY_UP)
		cub->keyboard.up = 0;
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		cub->keyboard.left = 0;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		cub->keyboard.down = 0;
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		cub->keyboard.right = 0;
	return (0);
}

int			ft_main_loop(t_cub *cub)
{
	if (cub->keyboard.up == 1)
		cub->circle.y -= 1;
	else if (cub->keyboard.down == 1)
		cub->circle.y += 1;
	else if (cub->keyboard.left == 1)
		cub->circle.x -= 1;
	else if (cub->keyboard.right == 1)
		cub->circle.x += 1;
	ft_draw_circle(&cub->img, cub->circle.x, cub->circle.y, 10, 0x00FF0000);
	mlx_put_image_to_window(cub->ptr.mlx, cub->ptr.win, cub->img.img, 0, 0);
	return (0);
}

void			ft_init_circle(t_circle *circle)
{
	circle->x = WIN_WIDTH / 2;
	circle->y = WIN_HEIGHT / 2;
}

int			main(void)
{
	t_cub		cub;

	cub.ptr.mlx = mlx_init();
	cub.ptr.win = mlx_new_window(cub.ptr.mlx, WIN_WIDTH, WIN_HEIGHT, "getting_start");
	cub.img.img = mlx_new_image(cub.ptr.mlx, WIN_WIDTH, WIN_HEIGHT);
	cub.img.addr = mlx_get_data_addr(cub.img.img, &cub.img.bits_per_pixel, &cub.img.line_length, &cub.img.endian);
	mlx_hook(cub.ptr.win, 2, 1L<<0, ft_key_press, &cub);
	mlx_hook(cub.ptr.win, 3, 1L<<1, ft_key_release, &cub);
	ft_init_circle(&cub.circle);
	mlx_loop_hook(cub.ptr.mlx, ft_main_loop, &cub);
	mlx_loop(cub.ptr.mlx);
	return (0);
}
