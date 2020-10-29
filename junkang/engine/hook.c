#include "cub3d.h"

int		ft_key_press(int keycode, t_cub *cub)
{
	if (keycode == A_KEY)
		cub->hook.a = 1;
	else if (keycode == W_KEY)
		cub->hook.w = 1;
	else if (keycode == S_KEY)
		cub->hook.s = 1;
	else if (keycode == D_KEY)
		cub->hook.d = 1;
	else if (keycode == UP_KEY)
		cub->hook.up = 1;
	else if (keycode == DOWN_KEY)
		cub->hook.down = 1;
	else if (keycode == LEFT_KEY)
		cub->hook.left = 1;
	else if (keycode == RIGHT_KEY)
		cub->hook.right = 1;
	return (0);
}
	

int		ft_key_release(int keycode, t_cub *cub)
{
	if (keycode == A_KEY)
		cub->hook.a = 0;
	else if (keycode == W_KEY)
		cub->hook.w = 0;
	else if (keycode == S_KEY)
		cub->hook.s = 0;
	else if (keycode == D_KEY)
		cub->hook.d = 0;
	else if (keycode == UP_KEY)
		cub->hook.up = 0;
	else if (keycode == DOWN_KEY)
		cub->hook.down = 0;
	else if (keycode == LEFT_KEY)
		cub->hook.left = 0;
	else if (keycode == RIGHT_KEY)
		cub->hook.right = 0;
	else if (keycode == ESC_KEY)
		exit(0);
	return (0);
}

int			ft_exit(t_cub *cub)
{
	cub = 0;
	exit(0);
	return (0);
}
