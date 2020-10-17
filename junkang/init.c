#include "cub3d.h"

# define WIN_WIDTH 600
# define WIN_HEIGHT 400
# define USER_X 4.5
# define USER_Y 1.54
# define USER_RADIAN 90

void		ft_init_cub(t_cub *cub)
{
	cub->image.width = WIN_WIDTH;
	cub->image.height = WIN_HEIGHT;
	cub->user.x = USER_X;
	cub->user.y = USER_Y;
	cub->user.radian = USER_RADIAN;
	cub->user.horizon = WIN_HEIGHT / 2;
	cub->sprite_pos[0][0] = 2.5;
	cub->sprite_pos[0][1] = 2.5;

	cub->sprite_pos[1][0] = 2.5;
	cub->sprite_pos[1][1] = 4.5;

	cub->sprite_pos[2][0] = 3.5;
	cub->sprite_pos[2][1] = 3.5;

	
	cub->sprite_cnt = 3;

	
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


void		ft_init_map(t_cub *cub)
{
	int	**map;
	int	size = 6;

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
}
