#include "../minilibx_mms_20200219/mlx.h"
#include <stdio.h>

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_data;

int		ft_mouse_hook_print_pos(int button, int x, int y, t_data *data)
{
	static int xx = 0, yy = 0;

	printf("mouse moves <%d, %d>\n", x - xx, y - yy);
	xx = x;
	yy = y;
	return (0);
}

int		main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, 1920, 1080, "42 mlx");
	mlx_mouse_hook(data.win_ptr, ft_mouse_hook_print_pos, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
