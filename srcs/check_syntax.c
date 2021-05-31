/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 21:00:21 by kankim            #+#    #+#             */
/*   Updated: 2021/05/30 20:50:08 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 에러 없으면 1리턴
int		check_rdir(t_cmd_list *cmdlist)
{
	if (cmdlist->flag == REDIRIN || cmdlist->flag == REDIROUT
		|| cmdlist->flag == REDIRAP)
	{
		if (!cmdlist->next || !cmdlist->next->arg)
		{
			printf("bash: syntax error near unexpected token `newline'\n");
			return (0);
		}
	}
	return (1);
}
// 에러 없으면 1리턴
int		check_colon(t_cmd_list *cmdlist)
{
	if (cmdlist->flag == SEMICOLON)
	{
		// 첫 인자에 플래그가 세미콜론이고 인자가 없을때 ;
		// 첫 인자에 플래그가 세미콜론이고 인자가 없고 두번째 인자의 플래그가 세미콜론이고 인자가 없을때 ;;
		// 첫 인자에 플래그가 세미콜론이고 인자가 있지만 두번째 인자의 플래그가 세미콜론이고 인자가 없을때 echo a ;;
		if (!cmdlist->arg || !*cmdlist->arg)
		{
			if (cmdlist->next && cmdlist->next->flag == SEMICOLON &&
				(!cmdlist->next->arg || !*cmdlist->next->arg))
				printf("bash: syntax error near unexpected token `;;'\n");
			else
				printf("bash: syntax error near unexpected token `;'\n");
			return (0);
		}
		else
		{
			if (cmdlist->next && cmdlist->next->flag == SEMICOLON &&
				(!cmdlist->next->arg || !*cmdlist->next->arg))
			{
				printf("bash: syntax error near unexpected token `;;'\n");
				return (0);
			}
		}
	}
	return (1);
}
// 에러 없으면 1리턴
int		check_pipe(t_cmd_list *cmdlist)
{
	if (cmdlist->flag == PIPE)
	{
		if (!cmdlist->arg || !*cmdlist->arg)
		{
			if (cmdlist->next && cmdlist->next->flag == PIPE &&
				(!cmdlist->next->arg || !*cmdlist->next->arg))
				printf("bash: syntax error near unexpected token `||'\n");
			else
				printf("bash: syntax error near unexpected token `|'\n");
			return (0);
		}
		else
		{
			if (cmdlist->next && cmdlist->next->flag == PIPE &&
				(!cmdlist->next->arg || !*cmdlist->next->arg))
				{
					printf("bash: syntax error near unexpected token `||'\n");
					return (0);
				}
		}
	}
	return (1);
}
// 에러 없으면 1리턴
int		check_syntax_flag(t_cmd_list *cmdlist)
{
	t_cmd_list *tmp;

	tmp = cmdlist;
	while (tmp)
	{
		if (!check_rdir(tmp))
			return (0);
		else if (!check_colon(tmp))
			return (0);
		else if (!check_pipe(tmp))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
// 에러 없으면 1리턴
int		check_syntax(t_cmd_list *cmdlist)
{
	if (g_info.syntax_flag)
	{
		if (g_info.syntax_flag == ERROR_B_SLASH)
			printf("bash: syntax error at backslash\n");
		else if (g_info.syntax_flag == ERROR_QUOTE)
			printf("bash: syntax error at quote\n");
		else if (g_info.syntax_flag == ERROR_RDIR_O)
			printf("bash: syntax error near unexpected token `>'\n");
		else if (g_info.syntax_flag == ERROR_RDIR_I)
			printf("bash: syntax error near unexpected token `<'\n");
		else if (g_info.syntax_flag == ERROR_RDIR_A)
			printf("bash: syntax error near unexpected token `>>'\n");
		return (0);
	}
	else if (check_syntax_flag(cmdlist))
		return (1);
	return (0);
}
