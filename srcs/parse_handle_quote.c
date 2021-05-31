/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_handle_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kankim <kankim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 19:12:30 by kankim            #+#    #+#             */
/*   Updated: 2021/05/28 17:38:53 by kankim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_env_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c >= '9') || c == '_')
		return (1);
	return (0);
}

void	handle_exit_status(char **cmdline, int s, int *i)
{
	char *tmp;

	tmp = ft_itoa(g_info.exit_status);
	remove_str(cmdline, s - 1, s + 1);
	*i = s + ft_strlen(tmp) - 2;
	insert_str(cmdline, tmp, s - 1);
}

void	check_env(char **cmdline, int *i)
{
	int		start;
	char	*env_key;

	// $으로 시작하는 환경변수 이름 가져오기
	start = ++(*i);
	while ((*cmdline)[*i] && is_env_char((*cmdline)[*i]))
		++(*i);
	// $ 다음에 환경변수로 입력 가능한 문자가 없으면
	if ((*cmdline)[start] == '?')
	{
		handle_exit_status(cmdline, start, i);
		return ;
	}
	// if (start == *i)
	// 	return ;
	env_key = ft_substr(*cmdline, start, *i - start);
	// 해당 이름의 env존재하면
	if (is_exist_env_key(env_key) == 1)
	{
	//		해당 값 cmdline에 삽입
		remove_str(cmdline, start - 1, *i);
		insert_str(cmdline, get_env_val(env_key), start - 1);
		*i = start + ft_strlen(get_env_val(env_key)) - 2;
	}
	// 존재하지 않으면
	else
	{
	// 		$으로 시작하는 문자열 cmdline에서 삭제
		remove_str(cmdline, start - 1, *i);
		*i = start;
	}
}

void	handle_escape(char **cmdline, int *i)
{
	// note : ""안에서는 \다음 문자가 $ ` " \ 중 하나일때만 작동하며, \는 제거됨
	char c;

	c = (*cmdline)[*i + 1];
	// \다음 문자가 $ ` " \ 중 하나이면
	if (c == '$' || c == '`' || c == '"' || c == '\\')
	{
	//		\는 출력하지 않고 \다음 문자만 출력
		// remove_str(cmdline, *i, *i + 1);	// \문자 삭제
		(*i) += 1;
	}
	// 아니면
	else
	{
	//		\출력
		++(*i);
	}
}

void	handle_escape_without_quote(char **cmdline, int *i)
{
	if ((*cmdline)[*i + 1] == 0)
	{
		if (!g_info.syntax_flag)
			g_info.syntax_flag = ERROR_B_SLASH;
		++(*i);
		return ;
	}
	if ((*cmdline)[*i] == '\\')
		*i += 2;
	else
		remove_str(cmdline, *i, *i + 1);
}

void	handle_quote_at_arg_cnt(char **cmdline, int *i)
{
	char c;
	int start;

	start = *i;
	c = (*cmdline)[*i];
	if (c == '\'')
	{
		while ((*cmdline)[++(*i)] != c)	// 해당 문자가 c가 아닌 동안 글자 수 카운트
			if ((*cmdline)[*i] == 0)	// 다음 따옴표가 나오기 전에 문장이 끝나면 에러
			{
				if (!g_info.syntax_flag)
					g_info.syntax_flag = ERROR_QUOTE;
				return ;
			}
	}
	else if (c == '\"')
	{
		while ((*cmdline)[++(*i)] != c)	// 해당 문자가 c가 아닌 동안 글자 수 카운트
		{
			if ((*cmdline)[*i] == 0)	// 다음 따옴표가 나오기 전에 문장이 끝나면 에러
			{
				if (!g_info.syntax_flag)
					g_info.syntax_flag = ERROR_QUOTE;
				return ;
			}
			if ((*cmdline)[*i] == '$')	
				check_env(cmdline, i);
			if ((*cmdline)[*i] == '\\')	
				handle_escape(cmdline, i);
		}
	}
	remove_str(cmdline, *i, *i + 1);		// 마지막 따옴표 제거
	remove_str(cmdline, start, start + 1);	// 처음 따옴표 제거
	// ++(*i);	// while 문이 종료되면 i는 c와 같은 문자인 인덱스 이므로 다음 인덱스가 되도록 증가
}

void	handle_quote_at_arg_len(char *cmdline, int *i)
{
	char c;
	char c2;

	c = cmdline[*i];
	if (c == '"')
	{
		while (cmdline[++(*i)] != c)	// 해당 문자가 c가 아닌 동안 글자 수 카운트
		{
			if (cmdline[*i] == 0)	// 다음 따옴표가 나오기 전에 문장이 끝나면 에러
			{
				if (!g_info.syntax_flag)
					g_info.syntax_flag = ERROR_QUOTE;
				return ;
			}
			if (cmdline[*i] == '\\')
			{
				c2 = cmdline[*i + 1];
				if (c2 == '`' || c2 == '$' || c2 == '"' || c2 == '\\')
					*i += 1;
			}
		}
	}
	else
	{
		while (cmdline[++(*i)] != c)
			if (cmdline[*i] == 0)	// 다음 따옴표가 나오기 전에 문장이 끝나면 에러
			{
				if (!g_info.syntax_flag)
					g_info.syntax_flag = ERROR_QUOTE;
				return ;
			}
	}
	++(*i);	// while 문이 종료되면 i는 c와 같은 문자인 인덱스 이므로 다음 인덱스가 되도록 증가
}