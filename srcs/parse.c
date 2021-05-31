/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 20:39:25 by kankim            #+#    #+#             */
/*   Updated: 2021/05/31 18:35:53 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_whitespace(char *str, int *i)
{
	while (ft_isspace(str[*i]) == 1)
		++(*i);
}

void	handle_env_without_quote(char **cmdline, int *i)
{
	int start;
	char *key;
	char *val;

	start = ++(*i);
	while (is_env_char((*cmdline)[*i]))
		++(*i);
	if ((*cmdline)[start] == '?')
	{
		handle_exit_status(cmdline, start, i);
		g_info.shell_var = 1;
		return ;
	}
	if (start == *i)
		return ;
	key = ft_substr(*cmdline, start, *i - start);
	if (is_exist_env_key(key))
	{
		val = get_env_val(key);
		remove_str(cmdline, start - 1, *i);
		insert_str(cmdline, val, start - 1);
	}
	*i = start + ft_strlen(val);
	free(key);
}

void	get_arg_cnt(t_node_info *node, char **cmdline, int i)
{
	int		flag;
	char	c;

	skip_whitespace(*cmdline, &i);
	while ((flag = isflag(&(*cmdline)[i], &i)) == -1)	// 플래그 만나기 전까지 반복, 플래그 기준으로 구분
	{
		while (ft_isspace((*cmdline)[i]) == 0 && ((flag = isflag(&(*cmdline)[i], &i)) == -1))	// 공백, 널이 아니고 문자가 있는동안
		// while ((*cmdline)[i] && ft_isspace((*cmdline)[i]) == 0)	// 공백, 널이 아니고 문자가 있는동안 인덱스 증가, 인자 기준으로 구분
		{
			if ((*cmdline)[i] == '\"' || (*cmdline)[i] == '\'')	// qoute일 경우 다음 quote까지 인덱스 증가
				handle_quote_at_arg_cnt(cmdline, &i);
			else if ((*cmdline)[i] == '\\')	// \일 경우 \다음 한 글자만 출력해야 함
				handle_escape_without_quote(cmdline, &i);
			else if ((*cmdline)[i] == '$')
				handle_env_without_quote(cmdline, &i);
			else	// quote, backslash가 아니면 인덱스 이동
				++i;
		}
		skip_whitespace(*cmdline, &i);
		++node->arg_cnt;
		if (flag == REDIRAP)
			break ;
	}
	node->token_flag = flag;
}

void	get_arg_len(t_node_info *node, char **cmdline, int *i)
{
	int flag;
	int start;
	int j;
	int qoute_cnt;

	node->arg_len = (int *)ft_calloc(node->arg_cnt, sizeof(int));
	j = 0;
	skip_whitespace(*cmdline, i);
	while ((flag = isflag(&(*cmdline)[*i], i)) == -1)
	{
		start = *i;
		qoute_cnt = 0;
		while (ft_isspace((*cmdline)[*i]) == 0 && ((flag = isflag(&(*cmdline)[*i], i)) == -1))	// 공백, 널이 아니고 문자가 있는동안
		{
			if ((*cmdline)[*i] == '\"' || (*cmdline)[*i] == '\'')	// 문자가 quote이면 다음 quote까지 인덱스 이동
			{
				handle_quote_at_arg_len(*cmdline, i);
				++qoute_cnt;
			}
			else	// quote가 아니면 인덱스 이동
				++(*i);
		}
		node->arg_len[j++] = *i - start - 2 * qoute_cnt;	// 문자 길이 입력, 최종 인덱스 - 시작 인덱스 - 따옴표갯수
		char *tmp = (char *)ft_calloc(node->arg_len[j - 1] + 1, sizeof(char)); // 인자가 입력될 공간 확보
		if (flag == 3)
			get_arg(tmp, *cmdline, start, *i - 1);	// insert arg to tmp
		else
			get_arg(tmp, *cmdline, start, *i);	// insert arg to tmp
		push_arg_back(node->arg, tmp);	// 리스트에 인자 입력 (싱글 링크드 리스트)
		skip_whitespace(*cmdline, i);
	}
	if ((*cmdline)[*i])
		++(*i);	// while문이 끝나면 i는 flag위치 이므로
}

void			handle_echo_flag(t_node_info *node)
{
	t_arg_list	*tmp;
	int			i;
	int			opt_zone;

	opt_zone = 1;
	tmp = node->arg->next->next;
	while (tmp && opt_zone)
	{
		// -n
		if (ft_strncmp(tmp->data, "-n", 3) == 0)
		{
			node->n_opt = 1;
			node->arg_cnt--;
			remove_node_arg_list(node->arg->next);
		}
		// -nnnn
		else if (ft_strncmp(tmp->data, "-n", 2) == 0)
		{
			i = 1;
			while (tmp->data[i] && tmp->data[i] == 'n')
				++i;
			if (ft_strlen(tmp->data) == i)
			{
				node->n_opt = 1;
				node->arg_cnt--;
				remove_node_arg_list(node->arg->next);
			}
		}
		else
			opt_zone = 0;
		tmp = tmp->next;
	}
}

void			handle_swung_dash(t_node_info *node)
{
	t_arg_list	*tmp;

	tmp = node->arg->next;
	while (tmp)
	{
		if (ft_strncmp("~", tmp->data, 2) == 0)
		{
			free(tmp->data);
			tmp->data = get_env_val("HOME");
		}
		tmp = tmp->next;
	}
}

t_node_info		get_node_info(char **cmdline, int *i)
{
	t_node_info	ret;

	init_node_info(&ret);
	get_arg_cnt(&ret, cmdline, *i);	// flag까지 인자의 갯수와 플래그를 얻음
	get_arg_len(&ret, cmdline, i);	// flag까지 인자 각각의 길이를 얻어 변수 ret의 t_arg_list arg 변수에 입력
	// 노드를 순회하면서 에코가 있는지 찾고
	// 있으면 에코, 리다이렉션 빼고 노드 순회하면서 처음 나오는 -n -nnnn 형식의 옵션 처리
	if (ret.arg->next && ft_strncmp(ret.arg->next->data, "echo", 5) == 0)
		handle_echo_flag(&ret);
	handle_swung_dash(&ret);
	return (ret);
}

void	parse(char **cmdline)
{
	t_cmd_list	*cmdlist;
	t_node_info	tmp;
	static int			i;

	i = 0;
	while ((*cmdline)[i])	// 한줄 끝까지
	{
		// 첫 인자는 헤드에 노드 입력
		if (i == 0)
		{
			// 플래그 전까지 node 정보 가져옴 : 인자 갯수, 인자의 각 길이, 종료 플래그
			tmp = get_node_info(cmdline, &i);
			// 인자 입력
			cmdlist = new_node(tmp);
		}
		// 헤드노드의 리스트에 노드 입력
		else
		{
			tmp = get_node_info(cmdline, &i);
			push_back(cmdlist, tmp);
		}
		free_node_info(&tmp);
	}

// test print cmdlist
// int cnt_tmp = 0;
// for (t_cmd_list *tmp2 = cmdlist; tmp2 != 0; tmp2 = tmp2->next)
// {
// 	char *flag_str;
// 	if (tmp2->flag == 0)
// 		flag_str = "'null'";
// 	else if (tmp2->flag == 1)
// 		flag_str = "'<'";
// 	else if (tmp2->flag == 2)
// 		flag_str = "'>'";
// 	else if (tmp2->flag == 3)
// 		flag_str = "'>>'";
// 	else if (tmp2->flag == 4)
// 		flag_str = "';'";
// 	else if (tmp2->flag == 5)
// 		flag_str = "'|'";
// 	printf("cmdlist %d, flag : %s\n", ++cnt_tmp, flag_str);
// 	for (int i = 0; i < tmp2->argc + 1; ++i)
// 	{
// 		printf("	parse result %d : |%s|\n", i, tmp2->arg[i]);
// 	}
// }
// test print cmdlist end

	// syntax check
	if (check_syntax(cmdlist))
		excute_cmd(cmdlist);
	// cmdlist free
	if (**cmdline)
		free_cmdlist(cmdlist);
}
