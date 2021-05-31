/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:46:41 by yongckim          #+#    #+#             */
/*   Updated: 2021/05/29 16:42:19 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	excute_echo(t_cmd_list *data)
{
	int		iter;

	iter = 1;
	if (!(*(data->arg + iter)))
		ft_putstr_fd("\n", 1);
	while (*(data->arg + iter))
	{
		ft_putstr_fd(data->arg[iter], STDOUT_FILENO);
		iter++;
		if (data->arg[iter])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (!data->n_opt)
		ft_putstr_fd("\n", 1);
	return (1);
}
