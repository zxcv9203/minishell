/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 16:23:39 by yongckim          #+#    #+#             */
/*   Updated: 2021/05/31 22:38:17 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					builtin_check(t_cmd_list *data)
{
	int ret;

	ret = 0;
	if (!data->arg[0])
		return (ret);
	if (ft_strcmp("echo", *data->arg) == 0)
		ret = excute_echo(data);
	else if (ft_strcmp("cd", *data->arg) == 0)
		ret = excute_cd(data);
	else if (ft_strcmp("pwd", *data->arg) == 0)
		ret = excute_pwd();
	else if (ft_strcmp("unset", *data->arg) == 0)
		ret = excute_unset(data);
	else if (ft_strcmp("export", *data->arg) == 0)
		ret = excute_export(data);
	else if (ft_strcmp("env", *data->arg) == 0)
		ret = excute_env();
	else if (ft_strcmp("exit", *data->arg) == 0)
		ret = excute_exit(data);
	return (ret);
}

int					find_command(t_cmd_list *list, t_path *path)
{
	if (!list->arg[0])
		exit(0);
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

int					excute_func(t_cmd_list *origin, t_path *path, int flag)
{
	t_process	ps;
	int			ret;

	ret = builtin_check(origin);
	if (!flag && !ret)
	{
		ps.pid = fork();
		if (ps.pid == CHILD_PROCESS)
		{
			find_command(origin, path);
			exit(g_info.exit_status);
		}
		else
		{
			ps.wait_pid = waitpid(ps.pid, &ps.pid_stat, 0);
			g_info.exit_status = WEXITSTATUS(ps.pid_stat);
		}
	}
	return (1);
}

static t_cmd_list	*metachar_exec(t_cmd_list *list, t_path *path)
{
	t_cmd_list *origin;

	origin = list;
	while ((list->flag == REDIRECTION_L) &&
			(list->next && list->next->flag == REDIRECTION_L))
	{
		if (list->stat == -1)
			return (list);
		list = create_file(list, origin);
	}
	while ((list->flag >= REDIRECTION_R && list->flag <= REDIRECTION_A) &&
			(list->next && (list->next->flag >= REDIRECTION_R &&
				list->next->flag <= REDIRECTION_A)))
	{
		if (list->stat == -1)
			return (list);
		list = create_file(list, origin);
	}
	if (origin->flag == PIPE || (origin->prev && origin->prev->flag == PIPE))
		exec_pipe(origin, list, path);
	else if ((list->flag >= REDIRECTION_L && list->flag <= REDIRECTION_A))
		list = redirect_cmd(list, origin, path);
	return (list);
}

int					excute_cmd(t_cmd_list *list)
{
	t_path	path;

	path.save_fd[0] = dup(STDIN_FILENO);
	path.save_fd[1] = dup(STDOUT_FILENO);
	while (list)
	{
		list->stat = 0;
		g_info.exit_status = 0;
		if (list->flag || (list->prev && list->prev->flag == PIPE))
			list = metachar_exec(list, &path);
		else
			list->stat = excute_func(list, &path, 0);
		if (list->stat == -1)
			return (0);
		list = list->next;
	}
	return (1);
}
