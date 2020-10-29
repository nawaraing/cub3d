#include "cub3d.h"

void			ft_save_user(t_cub *cub, char c, int i)
{
	if (c == 'E')
		cub->user.radian = 0;
	else if (c == 'N')
		cub->user.radian = 90;
	else if (c == 'W')
		cub->user.radian = 180;
	else if (c == 'S')
		cub->user.radian = 270;
	cub->user.x = (double)i + 0.5;
	cub->user.y = (double)cub->map_h + 0.5;
	cub->map[cub->map_h][i] = 3;
}

void			ft_parse_map(t_cub *cub, char *buf)
{
	int		i;

	i = -1;
	while (*(buf + ++i))
	{
		if (*(buf + i) == '0')
			cub->map[cub->map_h][i] = 9;
		else if (*(buf + i) == '1')
			cub->map[cub->map_h][i] = 1;
		else if (*(buf + i) == '2')
		{
			cub->map[cub->map_h][i] = 2;
			cub->sprite_pos[cub->sprite_cnt][0] = i + 0.5;
			cub->sprite_pos[cub->sprite_cnt][1] = cub->map_h + 0.5;
			cub->sprite_cnt++;
		}
		else if (*(buf + i)  == ' ')
			cub->map[cub->map_h][i] = ' ';
		else
			ft_save_user(cub, *(buf + i), i);
	}
	(cub->map_h)++;
}
