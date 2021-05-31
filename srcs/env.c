/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 20:35:24 by yongckim          #+#    #+#             */
/*   Updated: 2021/05/29 16:42:14 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	excute_env(void)
{
	int i;

	i = 0;
	while (g_info.env[i])
	{
		if (ft_strchr(g_info.env[i], '='))
		{
			write(1, g_info.env[i], ft_strlen(g_info.env[i]));
			write(1, "\n", 1);
		}
		i++;
	}
	return (1);
}
