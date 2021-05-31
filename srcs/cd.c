/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:04:13 by yongckim          #+#    #+#             */
/*   Updated: 2021/05/31 17:04:57 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	excute_cd(t_cmd_list *data)
{
	int ret;

	if (!data->arg[1])
		ret = chdir(ft_getenv("HOME", g_info.env));
	else
		ret = chdir(data->arg[1]);
	if (ret == -1)
	{
		ft_error("cd", data->arg[1], strerror(errno), 1);
		return (-1);
	}
	return (1);
}
