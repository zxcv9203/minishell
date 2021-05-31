/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:01:36 by yongckim          #+#    #+#             */
/*   Updated: 2021/05/30 21:13:43 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include "../srcs/minishell.h"
# include "get_next_line/get_next_line.h"

int			ft_strcmp(const char *s1, const char *s2);
size_t		ft_strlen(const char *s1);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strjoin2(char const *s1, char const *s2);
void		*ft_memmove(void *dst, const void *src, size_t len);
long long	ft_atoll(char *s, long long *n);
int			ft_isnum(char c);
int			ft_llrange(char const *s1);
void		ft_putstr_fd(char *s, int fd);
char		*ft_getenv(const char *name, char **envp);
char		*ft_strdup(const char *s1);
void		*ft_memcpy(void *dst, const void *src, size_t n);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
void		ft_doublefree(void **arr);
size_t		ft_arrsize(char **arr);
int			ft_isenv(char c);

#endif
