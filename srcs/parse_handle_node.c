/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_handle_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 19:26:02 by kankim            #+#    #+#             */
/*   Updated: 2021/05/31 17:59:42 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			init_node_info(t_node_info *ret)
{
	ret->arg = new_arg_node("head");
	ret->arg_cnt = 0;
	ret->token_flag = 0;
}

void	remove_node_arg_list(t_arg_list *node)
{
	t_arg_list *tmp;

	tmp = node->next;
	free(node->next->data);
	node->next = node->next->next;
	free(tmp);
}

void	free_node_info(t_node_info *target)
{
	t_arg_list	*tmp;

	free(target->arg_len);
	tmp = target->arg->next;
	free(target->arg);
	target->arg = tmp;
	while (target->arg != 0)
	{
		tmp = tmp->next;
		free(target->arg->data);
		free(target->arg);
		target->arg = tmp;
	}
}

void	free_cmdlist(t_cmd_list *cmdlist)
{
	t_cmd_list *tmp;
	int i;

	tmp = cmdlist;
	while (tmp != 0)
	{
		tmp = tmp->next;
		i = 0;
		while (cmdlist->arg[i])
		{
			if (!cmdlist->arg[i])
				break ;
			free(cmdlist->arg[i++]);
		}
		free(cmdlist->arg);
		free(cmdlist);
		cmdlist = tmp;
	}
}
