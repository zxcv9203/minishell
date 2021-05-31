/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 16:23:39 by yongckim          #+#    #+#             */
/*   Updated: 2021/05/26 22:28:36 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_check(t_cmd_list *data, t_process *ps)
{
	int ret;

	ret = 0;
	(void)ps;
	if (!data->arg)
		return (ret);

	// if (data->flag == PIPE || (data->prev && data->prev->flag == PIPE))
	// 	exec_cmd(data, ps);
	// while (data && (data->flag >= REDIRECTION_L && data->flag <= REDIRECTION_A))
	// 	redirect_cmd(data);
	if (ft_strcmp("echo", *data->arg) == 0)
		ret = excute_echo(data);
	else if (ft_strcmp("cd", *data->arg) == 0)
		ret = excute_cd(data);
	else if (ft_strcmp("pwd", *data->arg) == 0)
		ret = excute_pwd(data);
	else if (ft_strcmp("unset", *data->arg) == 0)
		ret = excute_unset(data);
	else if (ft_strcmp("export", *data->arg) == 0)
		ret = excute_export(data);
	else if (ft_strcmp("env", *data->arg) == 0)
		ret = excute_env(data);
	else if (ft_strcmp("exit", *data->arg) == 0)
		ret = excute_exit(data);
	return (ret);
}

int	find_command(t_cmd_list *list, t_path *path, t_process *ps)
{
	if (!list->arg)
		return (0);
	(void)ps;
	// if (list->flag == PIPE || (list->prev && list->prev->flag == PIPE))
	// 	exec_cmd(list, ps);
	if (ft_strchr(list->arg[0], '/'))
	{
		if (list->arg[0][0] == '/')
			path->cmd = list->arg[0];
		else
			path->cmd = join_path(list->arg[0]);
	}
	else
	{
		path->env = ft_getenv("PATH", g_info.env);
		path->env_list = ft_split(path->env, ':');
		path->cmd = 0;
		while (*path->env_list && !path->cmd)
		{
			if (search_cmd(list->arg[0], *path->env_list))
				path->cmd = dir_append(*path->env_list, list->arg[0]);
			path->env_list++;
		}
	}
	excute_bin(list, path->cmd);
	return (1);
}
int exec_cmd(t_cmd_list *cmd, t_process *ps)
{
	// pid_t pid;
	int ret;
	// int stat;

	ret = 1;
	ret = pipe(cmd->fd);
	if (ret < 0)
		exit(1);
	// pid = fork();
	// if (pid < 0)
	// 	exit(1);
	if (ps->pid == 0)
	{
		if (cmd->flag == PIPE && dup2(cmd->fd[1], 1) < 0)
			return (0);
		if (cmd->prev && cmd->prev->flag == PIPE &&
			dup2(cmd->prev->fd[0], 0) < 0)
			return (0);
		// if (!builtin_check(cmd))
		// 	find_command(cmd, path);

	}
	else
	{

		// if (WIFEXITED(stat))
		// 	ret = WEXITSTATUS(stat);
	}
	return (ret);
}

void *redirect_cmd(t_cmd_list *list)
{
	// t_process ps;

	// if (pipe(list->fd) < 0)
	// 	exit(0);
	// ps.pid = fork();
	// if (ps.pid == CHILD_PROCESS)
	// {

		if (list->flag == REDIRECTION_R)
			list->redir_out = open(list->next->arg[0], O_RDWR | O_CREAT | O_TRUNC, 0644);
		else if (list->flag == REDIRECTION_A)
			list->redir_out = open(list->next->arg[0], O_RDWR | O_CREAT | O_APPEND, 0644);
		else if (list->flag == REDIRECTION_L)
			list->redir_in = open(list->next->arg[0], O_RDONLY);
		// if (list->redir_in < 0 || list->redir_out < 0)
		// 	exit(1) ;
		if (list->next &&
			(list->next->flag == REDIRECTION_R || list->next->flag == REDIRECTION_A))
		{
			close(list->redir_out);
			redirect_cmd(list->next);
			exit(0);
		}
		// if (list->next && list->next->next && list->next->flag == REDIRECTION_L)
		// {
		// 	close(list->redir);
		// 	redirect_cmd(list->next);
		// 	exit(0);
		// }
		// printf("%s\n", list->arg[0]);
		if (list->redir_out != 1)
		{
			dup2(list->redir_out, STDOUT_FILENO);
			close(list->redir_out);
		}
		else if (list->redir_in != 0)
		{
			dup2(list->redir_in, STDIN_FILENO);
			close(list->redir_in);
		}
		// if (!builtin_check(origin))
		// 	find_command(origin, path);
	// 	exit(0);
	// }
	// else
	// 	ps.wait_pid = waitpid(ps.pid, &ps.pid_stat, 0);
	return (list->next);
}

int excute_cmd(t_cmd_list *list)
{
	t_path		path;
	t_process	ps;

	while (list)
	{
		if (pipe(list->fd) < 0)
			return (0);
		ps.pid = fork();
		if (ps.pid == CHILD_PROCESS)
		{
			if (list->flag == PIPE || (list->prev && list->prev->flag == PIPE))
			{
				if (list->flag == PIPE && dup2(list->fd[1], 1) < 0)
					return (0);
				if (list->prev && list->prev->flag == PIPE && dup2(list->prev->fd[0], 0) < 0)
					return (0);
			}
			if (list->flag >= REDIRECTION_L && list->flag <= REDIRECTION_A)
				redirect_cmd(list);
			if (!list->prev || !(list->prev->flag >= REDIRECTION_L &&
					list->prev->flag <= REDIRECTION_A))
					if (!builtin_check(list, &ps))
						find_command(list, &path, &ps);
			exit(0);
		}
		else
		{
			waitpid(ps.pid, &ps.pid_stat, 0);
			if (list->flag == PIPE || (list->prev && list->prev->flag == PIPE))
			{
				close(list->fd[1]);
				if (!list->next || list->flag == SEMICOLON)
					close(list->fd[0]);
						// if (list->prev && list->prev->flag == PIPE)
		// 	close(list->prev->fd[0]);
			}
		}
		list = list->next;
	}

	return (1);
}
