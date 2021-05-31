/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llrange.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 18:54:21 by yongckim          #+#    #+#             */
/*   Updated: 2021/05/15 18:01:57 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	minus_range(char const *s1, char const *ull_max,
							char *fill_s1, size_t len)
{
	fill_s1 = ft_calloc(21, sizeof(char));
	if (!fill_s1)
		return (0);
	while (*s1)
	{
		*(fill_s1 + len) = *s1++;
		len++;
	}
	if (ft_strcmp(fill_s1, ull_max) > 0)
		return (0);
	return (1);
}

static int	plus_range(char const *s1, char const *ll_max,
							char *fill_s1, size_t len)
{
	fill_s1 = ft_calloc(20, sizeof(char));
	if (!fill_s1)
		return (0);
	while (*s1)
	{
		*(fill_s1 + len) = *s1++;
		len++;
	}
	if (ft_strcmp(fill_s1, ll_max) > 0)
		return (0);
	return (1);
}

int			ft_llrange(char const *s1)
{
	char	*ll_max;
	char	*mll_max;
	char	*fill_s1;
	size_t	len;
	int		ret;

	if (!s1)
		return (-1);
	fill_s1 = NULL;
	ret = 1;
	len = ft_strlen(s1);
	if (len < 19)
		return (ret);
	ll_max = "9223372036854775807";
	mll_max = "-9223372036854775808";
	if (*s1 == '-')
		ret = minus_range(s1, mll_max, fill_s1, len);
	else
		ret = plus_range(s1, ll_max, fill_s1, len);
	free(fill_s1);
	return (ret);
}
