/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_handle_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kankim <kankim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 19:24:07 by kankim            #+#    #+#             */
/*   Updated: 2021/05/14 19:58:40 by kankim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_key(char *env_str)
{
	char	*ret;
	int		i;

	i = 0;
	while (env_str[i] != '=')
		++i;
	ret = ft_strndup(env_str, i);
	return (ret);
}

int		is_exist_env_key(char *key)
{
	int		i;
	char	*tmp;

	i = 0;
	while (g_info.env[i])
	{
		tmp = get_env_key(g_info.env[i++]);
		if (ft_strncmp(tmp, key, ft_strlen(tmp)) == 0)
		{
			free(tmp);
			return (1);
		}
		free(tmp);
	}
	return (0);
}

char	*get_env_val(char *key)
{
	char	*ret;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (g_info.env[i])
	{
		tmp = get_env_key(g_info.env[i]);
		if (ft_strncmp(tmp, key, ft_strlen(tmp)) == 0)
		{
			j = 0;
			while (g_info.env[i][j] != '=')
				++j;
			free(tmp);
			ret = ft_substr(g_info.env[i], j + 1, ft_strlen(g_info.env[i]) - j - 1);
			return (ret);
		}
		++i;
		free(tmp);
	}
	return (0);
}
