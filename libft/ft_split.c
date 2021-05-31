/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 19:11:42 by yongckim          #+#    #+#             */
/*   Updated: 2021/05/14 19:11:51 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_size(char *start, char c)
{
	int cnt;

	cnt = 0;
	while (*start && *++start)
	{
		if (*(start - 1) != c && *start == c)
			++cnt;
		if (*start != c && *(start + 1) == 0)
			++cnt;
	}
	return (cnt);
}

static char	*locate_s(char *start, char *s, char c)
{
	if (start == s && *start != c)
		return (start);
	while (*start && *++start)
		if (*start != c && *(start - 1) == c)
			break ;
	return (start);
}

static char	*locate_e(char *end, char c)
{
	while (*end && *++end)
	{
		if (*end != c && *(end + 1) == 0)
			return (end + 1);
		if (*end == c && *(end - 1) != c)
			break ;
	}
	return (end);
}

char		**ft_split(char const *s, char c)
{
	char	**ret;
	char	*start;
	char	*end;
	int		cnt;
	int		i;

	if (!s)
		return (0);
	cnt = count_size((char *)s, c);
	start = locate_s((char *)s, (char *)s, c);
	if (!(ret = (char **)ft_calloc(cnt + 1, sizeof(char *))))
		return (0);
	i = -1;
	while (++i < cnt)
	{
		end = locate_e(start, c);
		if (!(*(ret + i) = (char *)ft_calloc(end - start + 1, sizeof(char))))
			return (0);
		ft_memcpy(*(ret + i), start, end - start);
		start = locate_s(end, (char *)s, c);
	}
	return (ret);
}
