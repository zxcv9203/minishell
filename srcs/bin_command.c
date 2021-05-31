/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 19:30:29 by yongckim          #+#    #+#             */
/*   Updated: 2021/05/31 17:25:41 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_path(char *cmd)
{
	char *pwd;

	pwd = 0;
	pwd = getcwd(pwd, 0);
	pwd = ft_strjoin2(pwd, "/");
	pwd = ft_strjoin2(pwd, cmd);
	return (pwd);
}

int		search_cmd(char *cmd, char *path)
{
	DIR				*dir_ptr;
	struct dirent	*file;

	dir_ptr = opendir(path);
	if (!dir_ptr)
		return (0);
	file = readdir(dir_ptr);
	while (file)
	{
		if (ft_strcmp(cmd, file->d_name) == 0)
		{
			closedir(dir_ptr);
			return (1);
		}
		file = readdir(dir_ptr);
	}
	closedir(dir_ptr);
	return (0);
}

char	*dir_append(char *path, char *cmd)
{
	path = ft_strjoin2(path, "/");
	path = ft_strjoin2(path, cmd);
	return (path);
}

void	excute_bin(t_cmd_list *data, char *path)
{
	if (execve(path, data->arg, g_info.env) < 0)
	{
		if (errno == 14)
		{
			if (!data->prev ||
				(data->prev && !(data->prev->flag >= REDIRECTION_L &&
				data->prev->flag <= REDIRECTION_A)))
				ft_error(data->arg[0], 0, "command not found", 1);
			if (g_info.shell_var)
				g_info.exit_status = 127;
		}
		dup2(1, 2);
	}
}
