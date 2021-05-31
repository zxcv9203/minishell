/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 19:56:22 by yongckim          #+#    #+#             */
/*   Updated: 2021/05/30 17:09:23 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_env(char **envp)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (*(envp + i))
	{
		j = i + 1;
		while (*(envp + j))
		{
			if (ft_strcmp(*(envp + i), *(envp + j)) > 0)
			{
				tmp = *(envp + i);
				*(envp + i) = *(envp + j);
				*(envp + j) = tmp;
			}
			j++;
		}
		i++;
	}
}

static int	env_print(char *env)
{
	int i;
	int equal;

	i = 0;
	equal = 0;
	while (env[i])
	{
		if (env[i] == '"' || env[i] == '\\')
			ft_putstr_fd("\\", 1);
		write(1, &env[i], 1);
		if (env[i] == '=')
		{
			equal = 1;
			ft_putstr_fd("\"", 1);
		}
		i++;
	}
	return (equal);
}

static void	export_print(char **envp)
{
	int i;
	int equal;

	i = 0;
	sort_env(envp);
	while (*(envp + i))
	{
		equal = 0;
		ft_putstr_fd("declare -x ", 1);
		equal = env_print(envp[i]);
		if (equal)
			ft_putstr_fd("\"", 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

int			excute_export(t_cmd_list *list)
{
	char	**cp_envp;

	cp_envp = 0;
	if (!(*(list->arg + 1)))
	{
		cp_envp = g_info.env;
		export_print(cp_envp);
	}
	else
		export_env(list);
	return (1);
}
