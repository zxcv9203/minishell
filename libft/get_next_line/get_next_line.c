/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 16:40:36 by kankim            #+#    #+#             */
/*   Updated: 2021/05/30 21:04:00 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		control_remainder(char **line, char **remainder)
{
	char	*nl_ptr;
	char	*tmp;

	if ((nl_ptr = ft_strchr(*remainder, '\n')))
	{
		tmp = *line;
		*line = ft_strndup(*remainder, nl_ptr - *remainder);
		ft_free(&tmp);
		tmp = *remainder;
		*remainder = ft_strndup(nl_ptr + 1, ft_strlen(nl_ptr + 1));
		ft_free(&tmp);
		return (1);
	}
	tmp = *line;
	*line = ft_strndup(*remainder, ft_strlen(*remainder));
	ft_free(&tmp);
	ft_free(&*remainder);
	return (0);
}

int		control_buf(char **line, char **remainder, char *buf)
{
	char	*nl_ptr;
	char	*tmp;
	char	*tmp2;

	if ((nl_ptr = ft_strchr(buf, '\n')))
	{
		tmp = ft_strndup(buf, nl_ptr - buf);
		tmp2 = *line;
		*line = ft_strjoin(*line, tmp);
		ft_free(&tmp);
		ft_free(&tmp2);
		tmp = ft_strndup(nl_ptr + 1, ft_strlen(nl_ptr + 1));
		tmp2 = *remainder;
		*remainder = ft_strjoin(*remainder, tmp);
		ft_free(&tmp);
		ft_free(&tmp2);
		ft_free(&buf);
		return (1);
	}
	tmp = *line;
	*line = ft_strjoin(*line, buf);
	ft_free(&tmp);
	return (0);
}

int		get_next_line(int fd, char **line)
{
	int				read_len;
	char			*buf;
	static char		*remainder[OPEN_MAX];

	if (fd < 0 || fd >= OPEN_MAX || !line || BUFFER_SIZE <= 0)
		return (-1);
	*line = ft_strndup("", 1);
	if (remainder[fd] && control_remainder(line, &remainder[fd]))
		return (1);
	if (!(buf = (char *)malloc(BUFFER_SIZE + 1)))
		return (-1);
	while ((read_len = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		*(buf + read_len) = 0;
		if (control_buf(line, &remainder[fd], buf))
			return (1);
	}
	if (read_len < 0)
		ft_free(&*line);
	ft_free(&buf);
	ft_free(&remainder[fd]);
	return (read_len < 0 ? -1 : 0);
}
