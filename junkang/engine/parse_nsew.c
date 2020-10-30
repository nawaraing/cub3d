/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_nsew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:21:59 by junkang           #+#    #+#             */
/*   Updated: 2020/10/30 19:50:28 by junkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_parse_north(t_cub *cub, char *buf)
{
	char		*path;
	void		*tmp;

	if (*buf != 'N' || *(buf + 1) != 'O' || !ft_isspace(*(buf + 2)))
		return (-1);
	buf += 2 * sizeof(char);
	while (*buf && ft_isspace(*buf))
		buf++;
	path = ft_strdup(buf);
	tmp = mlx_xpm_file_to_image(cub->mlx_ptr, path, \
			&(cub->xpm.north_wall.width), \
			&(cub->xpm.north_wall.height));
	free(path);
	if (tmp == 0)
		return (-1);
	cub->xpm.north_wall.img_ptr = tmp;
	cub->xpm.north_wall.addr = mlx_get_data_addr(tmp, \
			&(cub->xpm.north_wall.bpp), &(cub->xpm.north_wall.sl),\
			&(cub->xpm.north_wall.endian));
	while (*buf && !ft_isspace(*buf))
		buf++;
	if (*buf)
		return (-1);
	return (1);
}

int			ft_parse_south(t_cub *cub, char *buf)
{
	char		*path;
	void		*tmp;

	if (*buf != 'S' || *(buf + 1) != 'O' || !ft_isspace(*(buf + 2)))
		return (-1);
	buf += 2 * sizeof(char);
	while (*buf && ft_isspace(*buf))
		buf++;
	path = ft_strdup(buf);
	tmp = mlx_xpm_file_to_image(cub->mlx_ptr, path, \
			&(cub->xpm.south_wall.width), \
			&(cub->xpm.south_wall.height));
	free(path);
	if (tmp == 0)
		return (-1);
	cub->xpm.south_wall.img_ptr = tmp;
	cub->xpm.south_wall.addr = mlx_get_data_addr(tmp, \
			&(cub->xpm.south_wall.bpp), &(cub->xpm.south_wall.sl),\
			&(cub->xpm.south_wall.endian));
	while (*buf && !ft_isspace(*buf))
		buf++;
	if (*buf)
		return (-1);
	return (1);
}

int			ft_parse_east(t_cub *cub, char *buf)
{
	char		*path;
	void		*tmp;

	if (*buf != 'E' || *(buf + 1) != 'A' || !ft_isspace(*(buf + 2)))
		return (-1);
	buf += 2 * sizeof(char);
	while (*buf && ft_isspace(*buf))
		buf++;
	path = ft_strdup(buf);
	tmp = mlx_xpm_file_to_image(cub->mlx_ptr, path, \
			&(cub->xpm.east_wall.width), \
			&(cub->xpm.east_wall.height));
	free(path);
	if (tmp == 0)
		return (-1);
	cub->xpm.east_wall.img_ptr = tmp;
	cub->xpm.east_wall.addr = mlx_get_data_addr(tmp, \
			&(cub->xpm.east_wall.bpp), &(cub->xpm.east_wall.sl),\
			&(cub->xpm.east_wall.endian));
	while (*buf && !ft_isspace(*buf))
		buf++;
	if (*buf)
		return (-1);
	return (1);
}

int			ft_parse_west(t_cub *cub, char *buf)
{
	char		*path;
	void		*tmp;

	if (*buf != 'W' || *(buf + 1) != 'E' || !ft_isspace(*(buf + 2)))
		return (-1);
	buf += 2 * sizeof(char);
	while (*buf && ft_isspace(*buf))
		buf++;
	path = ft_strdup(buf);
	tmp = mlx_xpm_file_to_image(cub->mlx_ptr, path, \
			&(cub->xpm.west_wall.width), \
			&(cub->xpm.west_wall.height));
	free(path);
	if (tmp == 0)
		return (-1);
	cub->xpm.west_wall.img_ptr = tmp;
	cub->xpm.west_wall.addr = mlx_get_data_addr(tmp, \
			&(cub->xpm.west_wall.bpp), &(cub->xpm.west_wall.sl),\
			&(cub->xpm.west_wall.endian));
	while (*buf && !ft_isspace(*buf))
		buf++;
	if (*buf)
		return (-1);
	return (1);
}
