/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:17:08 by junkang           #+#    #+#             */
/*   Updated: 2020/10/30 20:13:28 by junkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		ft_init_hook(t_cub *cub)
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

static void		ft_init_map(t_cub *cub)
{
	int		i;
	int		j;

	i = -1;
	while (++i < MAX_MAP_NUM)
	{
		j = -1;
		while (++j < MAX_MAP_NUM)
			cub->map[i][j] = 0;
	}
	cub->map_h = 0;
}

static void		ft_init_img_and_addr(t_cub *cub)
{
	int		displayid;

	displayid = CGMainDisplayID();
	cub->image.width = CGDisplayPixelsWide(displayid);
	cub->image.height = CGDisplayPixelsHigh(displayid);
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

static void		ft_init_sprite(t_cub *cub)
{
	int		i;
	int		j;

	i = -1;
	while (++i < MAX_SP_NUM)
	{
		j = -1;
		while (++j < 2)
			cub->sprite_pos[i][j] = 0;
	}
}

int				ft_init_cub(t_cub *cub, int argc, char *argv[])
{
	int		errnum;

	if (argc > 3 || argc < 2)
	{
		write(1, "Error\n", 6);
		return (-1);
	}
	cub->mlx_ptr = mlx_init();
	ft_init_map(cub);
	ft_init_hook(cub);
	ft_init_img_and_addr(cub);
	ft_init_sprite(cub);
	cub->sprite_cnt = 0;
	cub->user.radian = -1;
	if ((errnum = ft_parse_file(cub, argv[1])) < 0)
	{
		write(1, "Error\n", 6);
		if (errnum == -2)
			write(1, strerror(errno), ft_strlen(strerror(errno)));
		return (-1);
	}
	cub->user.horizon = cub->image.height / 2;
	return (1);
}
