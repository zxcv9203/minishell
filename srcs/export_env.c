/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 17:11:14 by yongckim          #+#    #+#             */
/*   Updated: 2021/05/30 21:30:47 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*parse_key(char *arg)
{
	int		i;
	int		j;
	char	*key;

	i = 0;
	j = 0;
	if (!ft_isenv(arg[0]) || arg[0] == '=')
	{
		ft_error("export", arg, "not a valid identifier", 1);
		return (NULL);
	}
	while (arg[i] && arg[i] != '=')
		i++;
	key = ft_calloc(i + 1, sizeof(char));
	if (!key)
		return (NULL);
	while (j < i)
	{
		key[j] = arg[j];
		j++;
	}
	return (key);
}

static char	**new_envp(int arr_len)
{
	int		i;
	char	**cp_envp;

	i = 0;
	cp_envp = (char **)ft_calloc(arr_len + 2, sizeof(char *));
	if (!cp_envp)
		return (NULL);
	while (g_info.env[i])
	{
		cp_envp[i] = ft_strdup(g_info.env[i]);
		i++;
	}
	ft_doublefree((void **)g_info.env);
	return (cp_envp);
}

static void	modify_env(char *env, char *key)
{
	int		i;
	char	*env_key;

	i = 0;
	if (!ft_strchr(env, '='))
		return ;
	while (g_info.env[i])
	{
		env_key = parse_key(g_info.env[i]);
		if (ft_strcmp(key, env_key) == 0)
		{
			free(g_info.env[i]);
			g_info.env[i] = ft_strdup(env);
		}
		i++;
		free(env_key);
	}
}

int			export_env(t_cmd_list *list)
{
	int		i;
	int		arr_len;
	char	*key;

	i = 1;
	arr_len = ft_arrsize(g_info.env);
	while (list->arg[i])
	{
		g_info.env = new_envp(arr_len);
		key = parse_key(list->arg[i]);
		if (!key)
		{
			i++;
			continue;
		}
		if (ft_getenv(key, g_info.env))
			modify_env(list->arg[i], key);
		else
			g_info.env[arr_len++] = ft_strdup(list->arg[i]);
		i++;
		free(key);
	}
	return (1);
}
