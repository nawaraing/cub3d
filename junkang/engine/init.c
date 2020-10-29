#include "cub3d.h"

void		ft_init_hook(t_cub *cub)
{
	cub->hook.a = 0;
	cub->hook.s = 0;
	cub->hook.d = 0;
	cub->hook.w = 0;
	cub->hook.up = 0;
	cub->hook.down = 0;
	cub->hook.left = 0;
	cub->hook.right = 0;
}

void		ft_init_map(t_cub *cub)
{
	for (int i = 0; i < MAX_MAP_NUM; i++)
		for (int j = 0; j < MAX_MAP_NUM; j++)
			cub->map[i][j] = 0;
	cub->map_h = 0;
}

void		ft_init_img_and_addr(t_cub *cub)
{
	int		mainDisplayId;

	mainDisplayId = CGMainDisplayID();
	cub->image.width = CGDisplayPixelsWide(mainDisplayId);
	cub->image.height = CGDisplayPixelsHigh(mainDisplayId);
	cub->xpm.floor.img_ptr = 0;
	cub->xpm.ceil.img_ptr = 0;
	cub->xpm.north_wall.img_ptr = 0;
	cub->xpm.south_wall.img_ptr = 0;
	cub->xpm.east_wall.img_ptr = 0;
	cub->xpm.west_wall.img_ptr = 0;
	cub->xpm.sprite.img_ptr = 0;
	cub->xpm.floor.addr = 0;
	cub->xpm.ceil.addr = 0;
	cub->xpm.north_wall.addr = 0;
	cub->xpm.south_wall.addr = 0;
	cub->xpm.east_wall.addr = 0;
	cub->xpm.west_wall.addr = 0;
	cub->xpm.sprite.addr = 0;
	cub->xpm.floor_color = 0;
	cub->xpm.ceil_color = 0;
}

int		ft_init_cub(t_cub *cub, int argc, char *argv[])
{
	if (argc > 3 || argc < 2)
		return (0);
	cub->mlx_ptr = mlx_init();
	ft_init_map(cub);
	ft_init_hook(cub);
	ft_init_img_and_addr(cub);
	for (int i = 0; i < MAX_SP_NUM; i++)
		for (int j = 0; j < 2; j++)
			cub->sprite_pos[i][j] = 0;
	cub->sprite_cnt = 0;
	cub->user.radian = -1;
	if (ft_parse_file(cub, argv[1]) == -1)
	{
		write(1, "Error\n", 6);
		return (-1);
	}
	cub->user.horizon = cub->image.height / 2;
	return (1);
}
