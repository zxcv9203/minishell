/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 17:39:12 by yongckim          #+#    #+#             */
/*   Updated: 2021/05/31 22:39:02 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**calloc_args(t_cmd_list *list, t_cmd_list *origin)
{
	char	**new_arg;
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (origin->arg[j])
		j++;
	while (list->arg[i])
		i++;
	new_arg = (char **)ft_calloc(j + i, sizeof(char *));
	if (!new_arg)
		return (NULL);
	return (new_arg);
}

int			echo_n_check(t_cmd_list *origin, int i)
{
	int j;
	int ret;

	ret = 1;
	j = 2;
	if (ft_strncmp(origin->arg[i], "-n", 2) == 0)
	{
		while (origin->arg[i][j] && origin->arg[i][j] == 'n')
			j++;
		if (origin->arg[i][j] == '\0')
		{
			free(origin->arg[i]);
			origin->arg[i] = 0;
			origin->n_opt = 1;
		}
		else
			ret = 0;
	}
	else
		ret = 0;
	return (ret);
}

char		**option_remove(t_cmd_list *origin, int new, int old)
{
	char	**new_arg;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_arg = ft_calloc(new + 1, sizeof(char *));
	if (!new_arg)
		return (origin->arg);
	while (i < old)
	{
		while (!origin->arg[i] && i < old)
			i++;
		if (i >= old)
			break ;
		new_arg[j++] = ft_strdup(origin->arg[i++]);
	}
	ft_doublefree((void **)origin->arg);
	return (new_arg);
}

t_cmd_list	*echo_option_check(t_cmd_list *origin)
{
	int i;
	int size;
	int del;
	int j;

	if (ft_strcmp("echo", origin->arg[0]) != 0)
		return (origin);
	i = 1;
	size = ft_arrsize(origin->arg);
	del = size;
	while (origin->arg[i])
	{
		if (echo_n_check(origin, i))
		{
			del--;
			i++;
		}
		else
			break ;
	}
	if (del != size)
		origin->arg = option_remove(origin, del, size);
	return (origin);
}

char		**append_args(t_cmd_list *list, t_cmd_list *origin)
{
	char	**new_arg;
	int		i;
	int		j;

	j = 0;
	i = 1;
	new_arg = calloc_args(list, origin);
	if (!new_arg)
		return (NULL);
	while (origin->arg[j])
	{
		new_arg[j] = ft_strdup(origin->arg[j]);
		j++;
	}
	while (list->arg[i])
	{
		new_arg[j] = ft_strdup(list->arg[i]);
		j++;
		i++;
	}
	ft_doublefree((void **)origin->arg);
	origin->arg = 0;
	return (new_arg);
}
