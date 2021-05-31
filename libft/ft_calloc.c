/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 16:51:38 by yongckim          #+#    #+#             */
/*   Updated: 2021/05/08 17:13:12 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_calloc(size_t count, size_t size)
{
	void *space;

	space = (void *)malloc(count * size);
	if (!space)
		return (NULL);
	ft_bzero(space, count * size);
	return (space);
}
