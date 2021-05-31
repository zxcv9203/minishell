/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 20:59:39 by yongckim          #+#    #+#             */
/*   Updated: 2021/05/31 22:36:08 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	excute_exit(t_cmd_list *data)
{
	long long	exit_code;
	int			ret;

	exit_code = 0;
	if (data->argc > 1)
	{
		ft_putstr_fd("exit\n", 1);
		ft_error("exit", 0, "too many arguments", 1);
		return (-1);
	}
	ft_putstr_fd("exit\n", 1);
	ret = ft_llrange(data->arg[1]);
	if (ret > 0)
		ret = ft_atoll(data->arg[1], &exit_code);
	g_info.exit_status = exit_code % 256;
	if (!ret)
	{
		ft_error("exit", data->arg[1], "numeric argument required", 255);
		exit(g_info.exit_status);
	}
	exit((unsigned long long)(exit_code % 256));
}
