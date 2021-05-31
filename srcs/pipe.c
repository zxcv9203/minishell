/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 17:31:20 by yongckim          #+#    #+#             */
/*   Updated: 2021/05/31 22:37:06 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_redir(t_cmd_list *file)
{
	if (file->flag == REDIRECTION_R)
		file->redir_out = open(file->next->arg[0],
			O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (file->flag == REDIRECTION_A)
		file->redir_out = open(file->next->arg[0],
			O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (file->flag == REDIRECTION_L)
		file->redir_in = open(file->next->arg[0], O_RDONLY);
	redirect_desc(file);
}

static void	close_pipefd(t_cmd_list *cmd)
{
	close(cmd->fd[1]);
	if (!cmd->next || cmd->flag == SEMICOLON)
		close(cmd->fd[0]);
	if (cmd->prev && cmd->prev->flag == PIPE)
		close(cmd->prev->fd[0]);
}

void		exec_pipe(t_cmd_list *cmd, t_cmd_list *file, t_path *path)
{
	t_process ps;

	if (pipe(cmd->fd) < 0)
		exit(1);
	ps.pid = fork();
	if (ps.pid < 0)
		exit(1);
	if (ps.pid == 0)
	{
		pipe_redir(file);
		if (cmd->flag == PIPE && dup2(cmd->fd[1], STDOUT_FILENO) < 0)
			exit(1);
		else if (cmd->prev && cmd->prev->flag == PIPE &&
					dup2(cmd->prev->fd[0], STDIN_FILENO) < 0)
			exit(1);
		if (!builtin_check(cmd))
			find_command(cmd, path);
		exit(g_info.exit_status);
	}
	else
	{
		waitpid(ps.pid, &ps.pid_stat, 0);
		g_info.exit_status = WEXITSTATUS(ps.pid_stat);
		close_pipefd(cmd);
	}
}
