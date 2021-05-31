/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_manipulate_string.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kankim <kankim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 19:15:07 by kankim            #+#    #+#             */
/*   Updated: 2021/05/17 19:30:44 by kankim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_arg(char *dst, char *cmdline, int s, int e)
{
	int		i;
	char	c;

	i = 0;
	c = cmdline[s];
	if (c == '\'')
	{
		while (s < e && cmdline[++s] != '\'')
			dst[i++] = cmdline[s];
	}
	else if (c == '"')
	{
		while (s < e && cmdline[++s] != '"')
		{
			c = cmdline[s + 1];
			if (cmdline[s] == '\\' && (c == '`' || c == '$' || c == '\\' || c == '"'))
				dst[i++] = cmdline[++s];
			else
				dst[i++] = cmdline[s];
		}
	}
	else
	{
		while (s < e)
		{
			c = cmdline[s + 1];
			if (cmdline[s] == '\\' && (c == '`' || c == '$' || c == '\\' || c == '"'))
				dst[i++] = cmdline[++s];
			// else if (cmdline[s] != '\"' && cmdline[s] != '\'')
			// 	dst[i++] = cmdline[s];
			else
				dst[i++] = cmdline[s];
			++s;
		}
	}
}

// dst 문자열의 i인덱스에 src문자열 삽입
// src는 동적할당되어 들어오며 여기서 프리시켜줌
void		insert_str(char **dst, char *src, int i)
{
	char *tmp;
	char *tmp2;
	char *tmp3;

	tmp = ft_strndup(*dst, i);
	tmp2 = ft_strndup(*dst + i, ft_strlen(*dst + i));
	tmp3 = ft_strjoin(tmp, src);
	free(*dst);
	free(src);
	*dst = ft_strjoin(tmp3, tmp2);
	free(tmp);
	free(tmp2);
	free(tmp3);
}

// str문자열의 s인덱스부터 e - 1까지 삭제
void	remove_str(char **str, int s, int e)
{
	char *tmp;
	char *tmp2;

	tmp = ft_strndup(*str, s);
	tmp2 = ft_strndup(*str + e, ft_strlen(*str + e));
	free(*str);
	*str = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
}


