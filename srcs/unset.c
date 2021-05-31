/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 18:25:00 by yongckim          #+#    #+#             */
/*   Updated: 2021/05/31 22:39:51 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**new_delenv(int read_size, int size)
{
	char	**env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	env = ft_calloc(size + 1, sizeof(char *));
	if (!env)
		return (NULL);
	while (i < read_size)
	{
		while (!g_info.env[i] && i < read_size)
			i++;
		if (i >= read_size)
			break ;
		env[j++] = ft_strdup(g_info.env[i++]);
	}
	ft_doublefree((void **)g_info.env);
	return (env);
}

static void		ft_delenv(char *key)
{
	char	*envp_key;
	int		i;

	i = 0;
	while (g_info.env[i])
	{
		envp_key = parse_key(g_info.env[i]);
		if (ft_strcmp(key, envp_key) == 0)
		{
			free(g_info.env[i]);
			g_info.env[i] = 0;
			return ;
		}
		i++;
	}
}

static int		env_check(char *name)
{
	int		i;
	int		j;

	i = 0;
	while (g_info.env[i])
	{
		j = 0;
		while (g_info.env[i][j] && name[j] && g_info.env[i][j] == name[j])
			j++;
		if (name[j] == '\0' &&
			(g_info.env[i][j] == '=' || g_info.env[i][j] == '\0'))
			return (1);
		i++;
	}
	return (0);
}

int				excute_unset(t_cmd_list *list)
{
	int		i;
	char	*key;
	int		arr_len;
	int		del;

	i = 1;
	arr_len = ft_arrsize(g_info.env);
	del = arr_len;
	while (*(list->arg + i))
	{
		if (ft_strchr(list->arg[i], '='))
			ft_error("unset", *(list->arg + i), "not a valid identfier", 1);
		else if (env_check(list->arg[i]))
		{
			key = parse_key(*(list->arg + i));
			ft_delenv(key);
			del--;
		}
		i++;
	}
	if (del != arr_len)
		g_info.env = new_delenv(arr_len, del);
	return (1);
}
