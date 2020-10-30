/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:33:32 by junkang           #+#    #+#             */
/*   Updated: 2020/10/30 20:13:08 by junkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			main_loop(t_cub *cub)
{
	double		camera_vec[2];

	camera_vec[0] = cos((double)cub->user.radian * PI / 180);
	camera_vec[1] = sin((double)cub->user.radian * PI / 180);
	ft_put_image(cub, camera_vec);
	ft_move(cub, camera_vec);
	ft_turn(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, \
			cub->image.img_ptr, 0, 0);
	return (0);
}

int			main(int argc, char *argv[])
{
	t_cub		cub;

	if (ft_init_cub(&cub, argc, argv) != 1)
		return (0);
	cub.win_ptr = mlx_new_window(cub.mlx_ptr, cub.image.width, \
			cub.image.height, "cub3D");
	cub.image.img_ptr = mlx_new_image(cub.mlx_ptr, cub.image.width, \
			cub.image.height);
	cub.image.addr = mlx_get_data_addr(cub.image.img_ptr, &cub.image.bpp, \
			&cub.image.sl, &cub.image.endian);
	if (argc == 3)
	{
		if (!ft_memcmp(argv[2], "--save", ft_strlen("--save")))
			ft_screenshot(&cub);
		else
			write(1, "Error\n", 6);
		return (0);
	}
	mlx_hook(cub.win_ptr, KEYPRESS_EVENT, 0, ft_key_press, &cub);
	mlx_hook(cub.win_ptr, KEYRELEASE_EVENT, 0, ft_key_release, &cub);
	mlx_hook(cub.win_ptr, EXIT_EVENT, 0, ft_exit, &cub);
	mlx_loop_hook(cub.mlx_ptr, main_loop, &cub);
	mlx_loop(cub.mlx_ptr);
	return (0);
}
