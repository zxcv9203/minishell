/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kankim <kankim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 20:41:54 by kankim            #+#    #+#             */
/*   Updated: 2021/05/27 22:01:53 by kankim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				isflag(char *str, int *i)
{
	if (*str == 0)
		return (0);
	if (*str == '<')
	{
		if (*(str + 1) == '<')
		{
			if (!g_info.syntax_flag)
				g_info.syntax_flag = ERROR_RDIR_I;
		}
		return (REDIRIN);
	}
	if (*str == '>')
	{
		if (*(str + 1) == '>')
		{
			if (*(str + 2) == '>')
			{
				if (*(str + 3) == '>')
				{
					if (!g_info.syntax_flag)
						g_info.syntax_flag = ERROR_RDIR_A;
				}
				else
					if (!g_info.syntax_flag)
						g_info.syntax_flag = ERROR_RDIR_O;
			}
			++(*i);
			return (REDIRAP);
		}
		return (REDIROUT);
	}
	if (*str == ';')
		return (SEMICOLON);
	if (*str == '|')
		return (PIPE);
	return (-1);
}

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

