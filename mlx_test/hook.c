#include "../minilibx_mms_20200219/mlx.h"

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_data;

int		ft_key_hook_close(int keycode, t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	return (0);
}

int		main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, 1920, 1080, "42 mlx");
	mlx_key_hook(data.win_ptr, ft_key_hook_close, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
