/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:19:01 by yongckim          #+#    #+#             */
/*   Updated: 2021/05/13 19:31:59 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ret_value(char *env)
{
	char	*value;
	int		i;

	i = 0;
	value = env;
	return (value);
}

char		*ft_getenv(const char *name, char **envp)
{
	int 	i;
	int		j;
	char	*value;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] == name[j])
		{
			if (envp[i][j + 1] == '=' && !name[j + 1])
			{
				value = ret_value(&envp[i][j + 2]);
				return (value);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}
