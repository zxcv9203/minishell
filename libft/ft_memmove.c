/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 17:43:16 by yongckim          #+#    #+#             */
/*   Updated: 2021/05/12 19:39:24 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*s1;
	char	*s2;

	if (src == dst)
		return (dst);
	s1 = (char *)dst;
	s2 = (char *)src;
	if (s1 < s2)
	{
		while (len--)
			*(s1 + len) = *(s2 + len);
		return (dst);
	}
	while (len--)
		*s1++ = *s2++;
	return (dst);
}
