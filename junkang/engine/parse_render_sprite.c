/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_render_sprite.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:17:38 by junkang           #+#    #+#             */
/*   Updated: 2020/10/30 19:17:47 by junkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_parse_render(t_cub *cub, char *buf)
{
	if (*(buf++) != 'R')
		return (-1);
	if (!ft_isspace(*buf))
		return (-1);
	if (cub->image.width > ft_atoi(buf))
		cub->image.width = ft_atoi(buf);
	while (*buf && ft_isspace(*buf))
		buf++;
	while (*buf && ft_isnum(*buf))
		buf++;
	if (cub->image.height > ft_atoi(buf))
		cub->image.height = ft_atoi(buf);
	while (*buf && ft_isspace(*buf))
		buf++;
	if (*buf == 0)
		return (-1);
	while (*buf && ft_isnum(*buf))
		buf++;
	if (*buf)
		return (-1);
	return (1);
}

int			ft_parse_sprite(t_cub *cub, char *buf)
{
	char		*path;
	void		*tmp;

	if (*(buf++) != 'S')
		return (-1);
	if (!ft_isspace(*buf))
		return (-1);
	while (*buf && ft_isspace(*buf))
		buf++;
	path = ft_strdup(buf);
	tmp = mlx_xpm_file_to_image(cub->mlx_ptr, path, \
			&(cub->xpm.sprite.width), \
			&(cub->xpm.sprite.height));
	free(path);
	if (tmp == 0)
		return (-1);
	cub->xpm.sprite.img_ptr = tmp;
	cub->xpm.sprite.addr = mlx_get_data_addr(tmp, \
			&(cub->xpm.sprite.bpp), &(cub->xpm.sprite.sl),\
			&(cub->xpm.sprite.endian));
	while (*buf && !ft_isspace(*buf))
		buf++;
	if (*buf)
		return (-1);
	return (1);
}
