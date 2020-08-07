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

void	draw_circle(int x, int y, int r, int color, t_data *data)
{
	for (int i = y - r; i <= y + r; i++)
	{
		for (int j = x - r; j <= x + r; j++)
		{
			if (pow((x - j), 2) + pow((y - i), 2) <= pow(r, 2))
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
	draw_circle(1920 / 2, 1080 / 2 - 200, 270, 0xF0F0, &data);
	mlx_put_image_to_window(mlx_ptr, win_ptr, data.img, 0, 0);
	mlx_loop(mlx_ptr);
	return (0);
}
