#include "cub3d.h"


void		ft_set_cub(t_cub *cub)
{
	cub->user.horizon = cub->image.height / 2;
}

void		ft_init_cub(t_cub *cub)
{

	for (int i = 0; i < 500; i++)
		for (int j = 0; j < 500; j++)
			cub->map[i][j] = 0;
	cub->map_h = 0;

	cub->hook.a = 0;
	cub->hook.s = 0;
	cub->hook.d = 0;
	cub->hook.w = 0;
	cub->hook.up = 0;
	cub->hook.down = 0;
	cub->hook.left = 0;
	cub->hook.right = 0;

	cub->xpm.floor_color = 0;
	cub->xpm.ceil_color = 0;

	for (int i = 0; i < 200; i++)
		for (int j = 0; j < 2; j++)
			cub->sprite_pos[i][j] = 0;
	cub->sprite_cnt = 0;
	
	
}
/*	
	cub->xpm.ceil.img_ptr = mlx_xpm_file_to_image(cub->mlx_ptr, CEIL, \
			&(cub->xpm.ceil.width), &(cub->xpm.ceil.height));
	cub->xpm.ceil.addr = mlx_get_data_addr(cub->xpm.ceil.img_ptr, \
			&(cub->xpm.ceil.bpp), &(cub->xpm.ceil.sl), &(cub->xpm.ceil.endian));

	cub->xpm.floor.img_ptr = mlx_xpm_file_to_image(cub->mlx_ptr, FLOOR, \
			&(cub->xpm.floor.width), &(cub->xpm.floor.height));
	cub->xpm.floor.addr = mlx_get_data_addr(cub->xpm.floor.img_ptr, \
			&(cub->xpm.floor.bpp), &(cub->xpm.floor.sl), &(cub->xpm.floor.endian));

	cub->xpm.east_wall.img_ptr = mlx_xpm_file_to_image(cub->mlx_ptr, EAST_WALL, \
			&(cub->xpm.east_wall.width), &(cub->xpm.east_wall.height));
	cub->xpm.east_wall.addr = mlx_get_data_addr(cub->xpm.east_wall.img_ptr, \
			&(cub->xpm.east_wall.bpp), &(cub->xpm.east_wall.sl), &(cub->xpm.east_wall.endian));

	cub->xpm.west_wall.img_ptr = mlx_xpm_file_to_image(cub->mlx_ptr, WEST_WALL, \
			&(cub->xpm.west_wall.width), &(cub->xpm.west_wall.height));
	cub->xpm.west_wall.addr = mlx_get_data_addr(cub->xpm.west_wall.img_ptr, \
			&(cub->xpm.west_wall.bpp), &(cub->xpm.west_wall.sl), &(cub->xpm.west_wall.endian));

	cub->xpm.north_wall.img_ptr = mlx_xpm_file_to_image(cub->mlx_ptr, NORTH_WALL, \
			&(cub->xpm.north_wall.width), &(cub->xpm.north_wall.height));
	cub->xpm.north_wall.addr = mlx_get_data_addr(cub->xpm.north_wall.img_ptr, \
			&(cub->xpm.north_wall.bpp), &(cub->xpm.north_wall.sl), &(cub->xpm.north_wall.endian));

	cub->xpm.south_wall.img_ptr = mlx_xpm_file_to_image(cub->mlx_ptr, SOUTH_WALL, \
			&(cub->xpm.south_wall.width), &(cub->xpm.south_wall.height));
	cub->xpm.south_wall.addr = mlx_get_data_addr(cub->xpm.south_wall.img_ptr, \
			&(cub->xpm.south_wall.bpp), &(cub->xpm.south_wall.sl), &(cub->xpm.south_wall.endian));

	cub->xpm.sprite.img_ptr = mlx_xpm_file_to_image(cub->mlx_ptr, SPRITE, \
			&(cub->xpm.sprite.width), &(cub->xpm.sprite.height));
	cub->xpm.sprite.addr = mlx_get_data_addr(cub->xpm.sprite.img_ptr, \
			&(cub->xpm.sprite.bpp), &(cub->xpm.sprite.sl), &(cub->xpm.sprite.endian));
}
*/
/*
void		ft_init_map(t_cub *cub)
{
	int	*map[500];
	int	size = MAP_SIZE;

//	sprite
	cub->sprite_pos[0][0] = 2.5;
	cub->sprite_pos[0][1] = 2.5;

	cub->sprite_pos[1][0] = 2.5;
	cub->sprite_pos[1][1] = 4.5;

	cub->sprite_pos[2][0] = 3.5;
	cub->sprite_pos[2][1] = 3.5;

	cub->sprite_cnt = 3;

	map = (int **)malloc(sizeof(int *) * size);
	for (int i = 0; i < size; i++)
	{
		map[i] = (int *)malloc(sizeof(int) * size);
		for (int j = 0; j < size; j++)
		{
			map[i][j] = 0;
		}
	}
	for (int i = 0; i < size - 1; i++)
	{
		map[i][0] = 1;
		map[0][size - 1 - i] = 1;
		map[size - 1 - i][size - 1] = 1;
		map[size - 1][i] = 1;
	}
	cub->map = map;
*/
