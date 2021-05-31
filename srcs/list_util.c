/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 20:13:40 by kankim            #+#    #+#             */
/*   Updated: 2021/05/30 22:01:33 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_list	*new_node(t_node_info info)
{
	t_cmd_list	*ret;
	int i;

	ret = (t_cmd_list *)ft_calloc(1, sizeof(t_cmd_list));
	ret->arg = (char **)ft_calloc(info.arg_cnt + 1, sizeof(char *));
	i = -1;
	while (++i < info.arg_cnt)
	{
		info.arg = info.arg->next;
		ret->arg[i] = ft_strndup(info.arg->data, ft_strlen(info.arg->data));
	}
	ret->argc = info.arg_cnt - 1;
	ret->flag = info.token_flag;
	ret->next = 0;
	ret->prev = 0;
	return (ret);
}

void	push_back(t_cmd_list *head, t_node_info info)
{
	t_cmd_list	*add_node;
	t_cmd_list	*idx;
	t_cmd_list	*tmp;

	add_node = new_node(info);
	tmp = head;
	while (tmp->next != 0)
		tmp = tmp->next;
	tmp->next = add_node;
	add_node->prev = tmp;
}

t_arg_list	*new_arg_node(char *arg)
{
	t_arg_list *ret;

	ret = (t_arg_list *)ft_calloc(1, sizeof(t_arg_list));
	ret->data = arg;
	ret->next = 0;
	return (ret);
}

void	push_arg_back(t_arg_list *head, char *str)
{
	t_arg_list *tmp;
	t_arg_list *new;

	new = new_arg_node(str);
	tmp = head;
	while (tmp->next != 0)
		tmp = tmp->next;
	tmp->next = new;
}
