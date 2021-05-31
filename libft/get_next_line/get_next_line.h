/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 16:42:37 by kankim            #+#    #+#             */
/*   Updated: 2021/05/30 21:13:42 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8192
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft.h"

void		ft_free(char **ptr);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strndup(const char *s1, size_t n);
int			get_next_line(int fd, char **line);
int			control_buf(char **line, char **remainder, char *buf);
int			control_remainder(char **line, char **remainder);

#endif
