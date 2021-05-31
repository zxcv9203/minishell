/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 20:17:12 by yongckim          #+#    #+#             */
/*   Updated: 2021/05/29 17:02:12 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	excute_pwd(void)
{
	char	*pwd;

	pwd = 0;
	pwd = getcwd(pwd, 0);
	if (!pwd)
	{
		ft_error("pwd", 0, strerror(errno), 1);
		return (-1);
	}
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	free(pwd);
	return (1);
}
