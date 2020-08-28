#include "../minilibx_mms_20200219/mlx.h"

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

/*
int		deal_key(int key, void *param)
{
	write(1, "press key\n", 10);
	return (0);
}
*/

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int		main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	data;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1920, 1080, "mlx 42");
//	mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xFFFFFF);
//	mlx_key_hook(win_ptr, deal_key, (void *)0);
	data.img = mlx_new_image(mlx_ptr, 1920, 1080);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	my_mlx_pixel_put(&data, 5, 5, 0xFFFFFF);
	mlx_put_image_to_window(mlx_ptr, win_ptr, data.img, 0, 0);
	mlx_loop(mlx_ptr);
	return (0);
}
