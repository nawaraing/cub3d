#include "cub3d.h"

void			ft_put_wall(t_cub *cub, t_dda_data dda, int i, \
		int wall_height)
{
	double		hp;
	t_image		xpm_img;
	int		*xpm_addr;
	int		*img_addr;
	int		wall_start;

	hp = dda.hit_point;
	img_addr = (int *)cub->image.addr;
	if (dda.flag == 0)
		xpm_img = cub->xpm.south_wall;
	else if (dda.flag == 1)
		xpm_img = cub->xpm.north_wall;
	else if (dda.flag == 2)
		xpm_img = cub->xpm.west_wall;
	else
		xpm_img = cub->xpm.east_wall;
	wall_start = -wall_height / 2 + cub->user.horizon;
	xpm_addr = (int *)xpm_img.addr;
	img_addr[dda.w + i * cub->image.sl / 4] = \
		xpm_addr[(i - wall_start) * xpm_img.height / wall_height * \
		xpm_img.sl / 4 + (int)((hp - (int)hp) * xpm_img.width)];
}

void			ft_draw_floor(t_cub *cub, t_dda_data dda, int i)
{
	double		pixel_dist;
	double		xpm[2];
	int		*xpm_addr;
	int		*img_addr;
	int		color;

	pixel_dist = 0.5 * cub->image.height / (i - cub->user.horizon);
	xpm[0] = cub->user.x + dda.ray_vec[0] * pixel_dist;
	xpm[1] = cub->user.y - dda.ray_vec[1] * pixel_dist;
	xpm[0] = (xpm[0] - floor(xpm[0])) * cub->xpm.floor.width;
	xpm[1] = (xpm[1] - floor(xpm[1])) * cub->xpm.floor.height;
	xpm_addr = (int *)cub->xpm.floor.addr;
	img_addr = (int *)cub->image.addr;
	if (xpm_addr == 0)
		color = cub->xpm.floor_color;
	else
		color = xpm_addr[(int)xpm[1] * cub->xpm.floor.sl / 4 + \
			(int)xpm[0]];
	img_addr[dda.w + i * cub->image.sl / 4] = color;
}

void			ft_draw_ceil(t_cub *cub, t_dda_data dda, int i)
{
	double		pixel_dist;
	double		xpm[2];
	int		*xpm_addr;
	int		*img_addr;
	int		color;

	pixel_dist = 0.5 * cub->image.height / (cub->user.horizon - i);
	xpm[0] = cub->user.x + dda.ray_vec[0] * pixel_dist;
	xpm[1] = cub->user.y - dda.ray_vec[1] * pixel_dist;
	xpm[0] = (xpm[0] - floor(xpm[0])) * cub->xpm.ceil.width;
	xpm[1] = (xpm[1] - floor(xpm[1])) * cub->xpm.ceil.height;
	xpm_addr = (int *)cub->xpm.ceil.addr;
	img_addr = (int *)cub->image.addr;
	if (xpm_addr == 0)
		color = cub->xpm.ceil_color;
	else
		color = xpm_addr[(int)xpm[1] * cub->xpm.ceil.sl / 4 + \
			(int)xpm[0]];
	img_addr[dda.w + i * cub->image.sl / 4] = color;
}
