#include "cub3d.h"

void			ft_move(t_cub *cub, double camera_vec[2])
{
	t_hook_data		hk;
	double			next_x = 0.0, next_y = 0.0;

	hk = cub->hook;
	if (hk.w && !hk.a && !hk.s && !hk.d)
	{
		next_x = cub->user.x + MOVE_VELO * camera_vec[0];
		next_y = cub->user.y - MOVE_VELO * camera_vec[1];
	}
	else if (!hk.w && !hk.a && hk.s && !hk.d)
	{
		next_x = cub->user.x - MOVE_VELO * camera_vec[0];
		next_y = cub->user.y + MOVE_VELO * camera_vec[1];
	}
	else if (!hk.w && hk.a && !hk.s && !hk.d)
	{
		next_x = cub->user.x + MOVE_VELO * -camera_vec[1];
		next_y = cub->user.y - MOVE_VELO * camera_vec[0];;
	}
	else if (!hk.w && !hk.a && !hk.s && hk.d)
	{
		next_x = cub->user.x - MOVE_VELO * -camera_vec[1];
		next_y = cub->user.y + MOVE_VELO * camera_vec[0];;
	}
	if (!(cub->map[(int)next_y][(int)next_x]))
	{
		cub->user.x = next_x;
		cub->user.y = next_y;
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
	else if (cub->user.horizon > cub->image.height) cub->user.horizon = cub->image.height;
}
