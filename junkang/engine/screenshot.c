/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:22:34 by junkang           #+#    #+#             */
/*   Updated: 2020/10/30 19:47:18 by junkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		ft_itoc_put(int num, unsigned char *header)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		*(header + i) = (unsigned char)(num >> (i * 8));
		i++;
	}
}

static void		ft_bmp_header(int fd, int filesize, t_image *img)
{
	unsigned char	*header;

	filesize = 0;
	header = (unsigned char *)malloc(sizeof(unsigned char *) * 54);
	header = (unsigned char *)ft_memset(header, 0, 54);
	header[0] = (unsigned char)'B';
	header[1] = (unsigned char)'M';
	ft_itoc_put(filesize, header + 2);
	ft_itoc_put(54, header + 10);
	ft_itoc_put(40, header + 14);
	ft_itoc_put(img->width, header + 18);
	ft_itoc_put(img->height, header + 22);
	ft_itoc_put(40, header + 14);
	header[26] = (unsigned char)1;
	header[28] = (unsigned char)24;
	write(fd, header, 54);
	free(header);
}

static void		ft_put_pixels(int fd, t_image *img)
{
	int		w;
	int		h;
	int		color;
	int		*addr;

	addr = (int *)img->addr;
	h = 0;
	while (h < img->height)
	{
		w = 0;
		while (w < img->width)
		{
			color = addr[w + (img->height - h - 1) * img->sl / 4];
			write(fd, &color, 3);
			w++;
		}
		h++;
	}
	return ;
}

void			ft_screenshot(t_cub *cub)
{
	int			fd;
	int			filesize;
	double		camera[2];

	camera[0] = cos((double)cub->user.radian * PI / 180);
	camera[1] = sin((double)cub->user.radian * PI / 180);
	ft_put_image(cub, camera);
	filesize = 54 + (3 * cub->image.width * cub->image.height);
	if ((fd = open("shot.bmp", O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, \
					0777)) < 0)
		return ;
	ft_bmp_header(fd, filesize, &(cub->image));
	ft_put_pixels(fd, &(cub->image));
	close(fd);
	return ;
}
