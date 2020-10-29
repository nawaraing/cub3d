#include "cub3d.h"

int			ft_parse_path(t_cub *cub, char *buf, char type)
{
	char		*path;
	void		*tmp;
	t_image		*xpm_img;

	if (*buf != '.' || *(buf + 1) != '/')
		return (-1);
	if (type == 'F')
		xpm_img = &(cub->xpm.floor);
	else
		xpm_img = &(cub->xpm.ceil);
	path = ft_strdup(buf);
	tmp = mlx_xpm_file_to_image(cub->mlx_ptr, path, \
			&((*xpm_img).width), &((*xpm_img).height));
	free(path);
	if (tmp == 0)
		return (-1);
	(*xpm_img).img_ptr = tmp;
	(*xpm_img).addr = mlx_get_data_addr(tmp, &((*xpm_img).bpp), \
			&((*xpm_img).sl), &((*xpm_img).endian));
	while (*buf && !ft_isspace(*buf))
		buf++;
	if (*buf)
		return (-1);
	return (1);
}

int			ft_valid_num(int num)
{
	if (num < 0 || num > 255)
		return (-1);
	return (1);
}

int			ft_parse_color(char *buf)
{
	int		color;

	if (!ft_isnum(*buf) || ft_valid_num(ft_atoi(buf)) == -1)
		return (-1);
	color = 0;
	color |= (ft_atoi(buf) << 16);
	while (*buf && ft_isnum(*buf))
		buf++;
	if (*(buf++) != ',' || !ft_isnum(*buf) || \
			ft_valid_num(ft_atoi(buf)) == -1)
		return (-1);
	color |= (ft_atoi(buf) << 8);
	while (*buf && ft_isnum(*buf))
		buf++;
	if (*(buf++) != ',' || !ft_isnum(*buf) || \
			ft_valid_num(ft_atoi(buf)) == -1)
		return (-1);
	color |= ft_atoi(buf);
	while (*buf && ft_isnum(*buf))
		buf++;
	if (*buf)
		return (-1);
	return (color);
}

int			ft_parse_floor_ceil(t_cub *cub, char *buf)
{
	char		type;
	int		color;

	if (*buf != 'F' && *buf != 'C')
		return (-1);
	type = *buf;
	buf++;
	if (!ft_isspace(*buf))
		return (-1);
	while (*buf && ft_isspace(*buf))
		buf++;
	if (*buf == '.' && *(buf + 1) == '/')
	{
		if (ft_parse_path(cub, buf, type) == -1)
			return (-1);
	}
	else
		if ((color = ft_parse_color(buf)) == -1)
			return (-1);
	if (type == 'F')
		cub->xpm.floor_color = color;
	else
		cub->xpm.ceil_color = color;
	return (1);
}
