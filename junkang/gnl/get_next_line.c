/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 15:59:53 by junkang           #+#    #+#             */
/*   Updated: 2020/06/26 00:02:14 by junkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		check_line_feed(int fd, char *fd_list[], char **line)
{
	char	*temp;
	int		i;

	i = 0;
	while (fd_list[fd][i] != 0)
	{
		if (fd_list[fd][i] == '\n')
		{
			fd_list[fd][i] = 0;
			*line = ft_strdup(fd_list[fd]);
			temp = ft_strdup(&(fd_list[fd][i + 1]));
			free(fd_list[fd]);
			fd_list[fd] = temp;
			return (1);
		}
		i++;
	}
	return (0);
}

static int		read_fd(int fd, char *fd_list[], char **line)
{
	char	buf[BUFFER_SIZE + 1];
	int		readnum;
	char	*temp;

	while ((readnum = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[readnum] = 0;
		temp = ft_strjoin(fd_list[fd], buf);
		free(fd_list[fd]);
		fd_list[fd] = temp;
		if (check_line_feed(fd, fd_list, line) == 1)
			return (1);
	}
	if (readnum < 0)
		return (-1);
	return (0);
}

static int		check_read_nothing(int fd, char *fd_list[], char **line)
{
	char	buf[BUFFER_SIZE + 1];
	int		readnum;
	char	*temp;

	if ((readnum = read(fd, buf, BUFFER_SIZE)) == 0)
	{
		*line = ft_strdup("");
		return (0);
	}
	else if (readnum < 0)
		return (-1);
	buf[readnum] = 0;
	if (fd_list[fd] == 0)
		fd_list[fd] = ft_strdup("");
	temp = ft_strjoin(fd_list[fd], buf);
	free(fd_list[fd]);
	fd_list[fd] = temp;
	return (1);
}

int				get_next_line(int fd, char **line)
{
	static char *fd_list[1024];
	int			res;

	if (fd < 0 || line == 0 || BUFFER_SIZE <= 0)
		return (-1);
	res = 1;
	if (fd_list[fd] == 0 && (res = check_read_nothing(fd, fd_list, line)) == 0)
		return (0);
	else if (res == -1)
		return (-1);
	if (fd_list[fd] != 0 && check_line_feed(fd, fd_list, line) == 1)
		return (1);
	if (fd_list[fd] == 0)
		fd_list[fd] = ft_strdup("");
	if ((res = read_fd(fd, fd_list, line)) == 1)
		return (1);
	else if (res == -1)
		return (-1);
	*line = ft_strdup(fd_list[fd]);
	free(fd_list[fd]);
	fd_list[fd] = 0;
	return (0);
}
