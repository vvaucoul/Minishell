/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 09:54:38 by mle-faou          #+#    #+#             */
/*   Updated: 2020/11/03 14:04:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define BUFFER_SIZE 1

static int	custom_strlen(char *s, int i)
{
	if (i == 1)
	{
		while (s != NULL && *s != '\0')
		{
			if (*s == '\n')
				return (1);
			s++;
		}
		return (0);
	}
	else
		while (s != NULL && s[i])
			i++;
	return (i);
}

static char	*local_strcat(char *fd_save, char *buf)
{
	int		size;
	char	*new;
	int		i;

	size = custom_strlen(fd_save, 0) + custom_strlen(buf, 0) + 1;
	if (!(new = (char *)malloc(size)))
		return (NULL);
	i = 0;
	while (fd_save != NULL && fd_save[i])
	{
		new[i] = fd_save[i];
		i++;
	}
	if (fd_save != NULL)
		free(fd_save);
	while (buf != NULL && *buf != '\0')
		new[i++] = *buf++;
	new[i] = '\0';
	return (new);
}

static char	*process_line(char **fd_save, int fd, int i)
{
	int		j;
	char	*line;
	char	*tmp;

	while (fd_save[fd] && fd_save[fd][i] != '\n' && fd_save[fd][i] != '\0')
		i++;
	j = 0;
	if (!(line = (char *)malloc(i + 1)))
		return (NULL);
	i = -1;
	while (fd_save[fd] && fd_save[fd][++i] != '\n' && fd_save[fd][i] != '\0')
		line[i] = fd_save[fd][i];
	line[i] = '\0';
	if (!(tmp = NULL) && fd_save[fd] && fd_save[fd][i++] != '\0')
	{
		if (!(tmp = (char *)malloc(custom_strlen(&fd_save[fd][i], 0) + 1)))
			return (NULL);
		while (fd_save[fd][i] != '\0')
			tmp[j++] = fd_save[fd][i++];
		tmp[j] = '\0';
	}
	free(fd_save[fd]);
	fd_save[fd] = tmp;
	return (line);
}

int			ft_get_next_line(int fd, char **line)
{
	char		buf[(BUFFER_SIZE < 1) ? 1 : BUFFER_SIZE + 1];
	int			ret;
	static char	*fd_save[10241];

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1)
		return (-1);
	ret = -1;
	while (custom_strlen(fd_save[fd], 1) == 0 && ret != 0)
	{
		if ((ret = read(fd, buf, BUFFER_SIZE)) == -1)
			return (-1);
		buf[ret] = '\0';
		fd_save[fd] = local_strcat(fd_save[fd], buf);
	}
	*line = process_line(fd_save, fd, 0);
	if (ret == 0)
		return (0);
	return (1);
}
