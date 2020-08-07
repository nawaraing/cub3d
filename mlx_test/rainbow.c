#include "../minilibx_mms_20200219/mlx.h"
#include <math.h>
//compile command is 
//
// gcc main.c -lmlx -framework OpenGL -framework AppKit

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int		ft_get_color(int y, int height)
{
	if (y < height / 7

}

void	draw_rainbow(int x, int y, t_data *data)
{
	int		color;

	for (int i = 1080 / 2 - y, i <= 1080 / 2 + y; i++)
	{
		for (int j = 1920 / 2 - x, i <= 1920 / 2 + x, j++)
		{
			color = ft_get_color(i, 2 * y);
			my_mlx_pixel_put(data, j, i, color);
		}
	}
}

int		main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	data;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1920, 1080, "mlx 42");
	data.img = mlx_new_image(mlx_ptr, 1920, 1080);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	draw_rainbow(1920 / 2, 1080 / 2, &data);
	mlx_put_image_to_window(mlx_ptr, win_ptr, data.img, 0, 0);
	mlx_loop(mlx_ptr);
	return (0);
}
