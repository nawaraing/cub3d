#include "cub3d.h"

int			ft_near_by_wall(t_cub *cub, double x, double y)
{
	int		obj;

	obj = cub->map[(int)y][(int)(x + MOVE_VELO)];
	if (obj != 9 && obj != 3)
		return (1);
	obj = cub->map[(int)y][(int)(x - MOVE_VELO)];
	if (obj != 9 && obj != 3)
		return (1);
	obj = cub->map[(int)(y + MOVE_VELO)][(int)x];
	if (obj != 9 && obj != 3)
		return (1);
	obj = cub->map[(int)(y - MOVE_VELO)][(int)x];
	if (obj != 9 && obj != 3)
		return (1);
	return (0);
}

void			ft_move_left_right(t_cub *cub, double camera[2], \
		double *x, double *y)
{
	t_hook_data		hk;
	
	hk = cub->hook;
	if (!hk.w && hk.a && !hk.s && !hk.d)
	{
		*x = cub->user.x + MOVE_VELO * -camera[1];
		*y = cub->user.y - MOVE_VELO * camera[0];
	}
	else if (!hk.w && !hk.a && !hk.s && hk.d)
	{
		*x = cub->user.x - MOVE_VELO * -camera[1];
		*y = cub->user.y + MOVE_VELO * camera[0];
	}
}


void			ft_move_front_back(t_cub *cub, double camera[2], \
		double *x, double *y)
{
	t_hook_data		hk;
	
	hk = cub->hook;
	if (hk.w && !hk.a && !hk.s && !hk.d)
	{
		*x = cub->user.x + MOVE_VELO * camera[0];
		*y = cub->user.y - MOVE_VELO * camera[1];
	}
	else if (!hk.w && !hk.a && hk.s && !hk.d)
	{
		*x = cub->user.x - MOVE_VELO * camera[0];
		*y = cub->user.y + MOVE_VELO * camera[1];
	}
}

void			ft_move(t_cub *cub, double camera[2])
{
	double			next_x;
	double			next_y;

	next_x = cub->user.x;
	next_y = cub->user.y;
	ft_move_left_right(cub, camera, &next_x, &next_y);
	ft_move_front_back(cub, camera, &next_x, &next_y);
	if (!ft_near_by_wall(cub, next_x, next_y))
	{
		cub->user.x = next_x;
		cub->user.y = next_y;
		return ;
	}
}

void			ft_turn(t_cub *cub)
{
	t_hook_data		hk;

	hk = cub->hook;
	if (!hk.up && !hk.down && hk.left && !hk.right)
		cub->user.radian = (cub->user.radian + TURN_VELO) % 360;
	else if (!hk.up && !hk.down && !hk.left && hk.right)
		cub->user.radian = (cub->user.radian - TURN_VELO + 360) % 360;
	else if (hk.up && !hk.down && !hk.left && !hk.right)
		cub->user.horizon += TURN_VELO * 3;
	else if (!hk.up && hk.down && !hk.left && !hk.right)
		cub->user.horizon -= TURN_VELO * 3;
	if (cub->user.horizon < 0) cub->user.horizon = 0;
	else if (cub->user.horizon > cub->image.height) cub->user.horizon = \
		cub->image.height;
}
