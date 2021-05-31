/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 16:23:14 by yongckim          #+#    #+#             */
/*   Updated: 2021/05/15 18:01:48 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long ft_atoll(char *s, long long *n)
{
	int minus;

	minus = 1;
	while (*s == '\t' || *s == '\n' || *s == '\v' ||
			*s == '\f' || *s == '\r' || *s == ' ')
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			minus *= -1;
		s++;
	}
	while (*s)
	{
		if (!ft_isnum(*s))
			return (0);
		*n = *n * 10 + *s - '0';
		s++;
	}
	*n *= minus;
	return (1);
}
