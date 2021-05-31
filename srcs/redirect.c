/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 17:36:51 by yongckim          #+#    #+#             */
/*   Updated: 2021/05/31 22:38:40 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd_list	*loop_redir(t_cmd_list *list)
{
	if ((list->flag == REDIRECTION_A ||
			list->flag == REDIRECTION_R) && (list->next &&
				(list->next->flag == REDIRECTION_R ||
					list->next->flag == REDIRECTION_A)))
	{
		close(list->redir_out);
		list = list->next;
	}
	else if (list->flag == REDIRECTION_L &&
				(list->next && list->next->flag == REDIRECTION_L))
	{
		close(list->redir_in);
		list = list->next;
	}
	return (list);
}

void				redirect_desc(t_cmd_list *list)
{
	if (list->flag == REDIRECTION_A || list->flag == REDIRECTION_R)
	{
		dup2(list->redir_out, STDOUT_FILENO);
		close(list->redir_out);
	}
	else if (list->flag == REDIRECTION_L)
	{
		dup2(list->redir_in, STDIN_FILENO);
		close(list->redir_in);
	}
}

t_cmd_list			*create_file(t_cmd_list *list, t_cmd_list *origin)
{
	if (list->flag == REDIRECTION_R)
		list->redir_out = open(list->next->arg[0],
			O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (list->flag == REDIRECTION_A)
		list->redir_out = open(list->next->arg[0],
			O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (list->flag == REDIRECTION_L)
		list->redir_in = open(list->next->arg[0], O_RDONLY);
	if (list->redir_out == -1 || list->redir_in == -1)
	{
		ft_error(list->next->arg[0], 0, strerror(errno), 1);
		list->stat = -1;
		return (list);
	}
	if (list->next->arg[1])
		origin->arg = append_args(list->next, origin);
	list = loop_redir(list);
	return (list);
}

static t_cmd_list	*other_redir_check(t_cmd_list *list,
										int *flag, t_cmd_list *origin)
{
	if (list->next && list->flag != list->next->flag &&
		(list->next->flag >= REDIRECTION_L &&
			list->next->flag <= REDIRECTION_A))
		*flag = 1;
	while ((list->next && list->next->flag == REDIRECTION_L) &&
			(list->next->next && list->next->next->flag == REDIRECTION_L))
	{
		if (*flag != 2)
			list = create_file(list->next, origin);
		else
			list = create_file(list, origin);
		*flag = 2;
	}
	while (list->next &&
			(list->next->flag >= REDIRECTION_R &&
				list->next->flag <= REDIRECTION_A) &&
					list->next->next)
	{
		if (*flag != 2)
			list = create_file(list->next, origin);
		else
			list = create_file(list, origin);
		*flag = 2;
	}
	return (list);
}

t_cmd_list			*redirect_cmd(t_cmd_list *list,
									t_cmd_list *origin, t_path *path)
{
	int flag;

	flag = 0;
	list = create_file(list, origin);
	if (list->redir_out == -1 || list->redir_in == -1)
	{
		while (list->next)
			list = list->next;
		return (list);
	}
	if (origin && path)
	{
		redirect_desc(list);
		list = other_redir_check(list, &flag, origin);
		if (flag == 1)
			list = redirect_cmd(list->next, origin, path);
		else if (flag == 2)
			list = redirect_cmd(list, origin, path);
		origin = echo_option_check(origin);
		excute_func(origin, path, flag);
	}
	dup2(path->save_fd[1], STDOUT_FILENO);
	dup2(path->save_fd[0], STDIN_FILENO);
	return (list);
}
