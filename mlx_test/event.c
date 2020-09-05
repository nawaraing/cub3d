#include "../minilibx_mms_20200219/mlx.h"
#include <stdio.h>

typedef struct	s_vars {
	void	*mlx_ptr;
	void	*win_ptr;
}		t_vars;


int		press_key(int keycode, t_vars *vars)
{
	if (keycode == 53)
		mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
	printf("ketcode : %d\n", keycode);
	return (0);
}

int		enter_win(int keycode, t_vars *vars)
{
	keycode = 0;
	vars = 0;
	printf("Hello\n");
	return (0);
}

int		leave_win(int keycode, t_vars *vars)
{
	keycode = 0;
	vars = 0;
	printf("bye\n");
	return (0);
}

int		main(void)
{
	t_vars	vars;

	vars.mlx_ptr = mlx_init();
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, 1152, 720, "event exxercise");
	mlx_hook(vars.win_ptr, 2, 1L<<0, press_key, &vars);
	mlx_hook(vars.win_ptr, 7, 1L<<4, enter_win, &vars);
	mlx_hook(vars.win_ptr, 8, 1L<<5, leave_win, &vars);
	mlx_loop(vars.mlx_ptr);
	return (0);
}
