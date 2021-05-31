/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 16:42:24 by kankim            #+#    #+#             */
/*   Updated: 2021/05/30 22:30:43 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free(char **ptr)
{
	free(*ptr);
	*ptr = 0;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	int		i;
	int		len1;
	int		len2;

	if (!s1 && !s2)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = 0;
	if (!(ret = (char *)malloc((len1 + len2 + 1) * sizeof(char))))
		return (0);
	while (len1--)
		*(ret + i++) = *s1++;
	while (len2--)
		*(ret + i++) = *s2++;
	*(ret + i) = 0;
	return (ret);
}

char	*ft_strndup(const char *s1, size_t n)
{
	char	*str;

	if (!(str = (char *)malloc((n + 1) * sizeof(char))))
		return (0);
	*(str + n) = 0;
	while (n--)
		*(str + n) = *(s1 + n);
	return (str);
}


