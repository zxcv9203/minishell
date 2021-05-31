/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kankim <kankim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 16:27:22 by kankim            #+#    #+#             */
/*   Updated: 2021/05/28 16:50:45 by kankim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signal(int signo)
{
	pid_t	pid;
	int		status;
	
	pid = waitpid(-1, &status, WNOHANG);
	if (signo == SIGINT)
	{
		if (pid == -1)	// 자식이 없으면
		{
			ft_write("\nminishell$ ", STDOUT);
			if (g_info.tmp_his->line)
				free(g_info.tmp_his->line);
			g_info.tmp_his->line = 0;
			g_info.exit_status = 1;
		}
		else
		{
			ft_write("\nminishell$ ", STDOUT);
			g_info.exit_status = 130;
		}
	}
	else if (signo == SIGQUIT)
	{
		if (pid != -1) // 자식이 있으면
			ft_write("Quit: 3", STDOUT);
	}
}

void		set_signal(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}