/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:17:34 by junkang           #+#    #+#             */
/*   Updated: 2020/10/30 19:17:34 by junkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	ft_check_identifier(char *buf)
{
	if (buf[0] == 'R')
		return ('r');
	else if (buf[0] == 'N' && buf[1] == 'O')
		return ('N');
	else if (buf[0] == 'S' && buf[1] == 'O')
		return ('S');
	else if (buf[0] == 'W' && buf[1] == 'E')
		return ('W');
	else if (buf[0] == 'E' && buf[1] == 'A')
		return ('E');
	else if (buf[0] == 'S')
		return ('s');
	else if (buf[0] == 'F')
		return ('f');
	else if (buf[0] == 'C')
		return ('c');
	else if (buf[0] == 0)
		return (0);
	return (-1);
}

static int	ft_parse_identifier(t_cub *cub, char *buf, int id)
{
	static int		cnt = 0;

	if (cnt >= 8)
		return (8);
	if (id == 'r' && ft_parse_render(cub, buf) == -1)
		return (-1);
	else if (id == 'N' && ft_parse_north(cub, buf) == -1)
		return (-1);
	else if (id == 'S' && ft_parse_south(cub, buf) == -1)
		return (-1);
	else if (id == 'W' && ft_parse_west(cub, buf) == -1)
		return (-1);
	else if (id == 'E' && ft_parse_east(cub, buf) == -1)
		return (-1);
	else if (id == 's' && ft_parse_sprite(cub, buf) == -1)
		return (-1);
	else if ((id == 'f' || id == 'c') && \
			ft_parse_floor_ceil(cub, buf) == -1)
		return (-1);
	else if (id == 0)
		return (0);
	else if (id == -1)
		return (-1);
	cnt++;
	return (cnt);
}

static int	ft_iscub(const char *file_name)
{
	while (*file_name)
		file_name++;
	if (ft_memcmp(file_name - 4, ".cub", ft_strlen(".cub")))
		return (-1);
	return (1);
}

int			ft_parse_file(t_cub *cub, const char *file_name)
{
	int			fd;
	int			ret;
	char		*buf;
	char		id;
	int			cnt;

	if ((fd = open(file_name, O_RDONLY)) < 1)
		return (-2);
	if (ft_iscub(file_name) == -1)
		return (-1);
	while ((ret = get_next_line(fd, &buf)) > 0)
	{
		id = ft_check_identifier(buf);
		if (cnt == 8)
			ft_parse_map(cub, buf);
		if ((cnt = ft_parse_identifier(cub, buf, id)) == -1)
			return (-1);
		free(buf);
	}
	free(buf);
	close(fd);
	if (ret == -1 || cnt == -1 || ft_valid_map(cub) == -1)
		return (-1);
	return (1);
}
