/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 18:02:06 by kankim            #+#    #+#             */
/*   Updated: 2021/05/31 17:19:00 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int		get_cmd_line(char **cmdline)
// {
// 	char	*line;
// 	char	*tmp;
// 	int		flag;

// 	*cmdline = ft_strndup("", 2);
// 	while (1)
// 	{
// 		flag = get_next_line(STDIN, &line);
// 		tmp = ft_strjoin(*cmdline, line);
// 		free(*cmdline);
// 		free(line);
// 		*cmdline = tmp;
// 		if (flag == 0)
// 		{
// 			if (ft_strlen(*cmdline))
// 				continue ;
// 			ft_write("exit\n", STDOUT);
// 		}
// 		break ;
// 	}
// 	return (flag);
// }

// - 입력받은 cmdline에서 flag 조건(리다이렉션, 세미콜론, 파이프, 널)이 나올때까지 인자 갯수, 길이 카운트,
// - " 이나 ' 이 있으면 다음 ", ' 를 만날때까지 읽고 하나의 arg로 저장 및 카운트
// **arg에 카운트한 인자 갯수와 길이를 이용하여 동적할당한 뒤 값 입력
// flag가 널이면 파싱 완료 아니면 위 과정 반복

void	get_env(char **envp)
{
	int		cnt_envp;
	int		i;

	cnt_envp = 0;
	while (envp[cnt_envp])
		cnt_envp++;
	g_info.env = (char **)ft_calloc(cnt_envp + 1, sizeof(char *));
	i = -1;
	while (envp[++i])
		g_info.env[i] = ft_strndup(envp[i], ft_strlen(envp[i]));
}

void	init_g_variable(void)
{
	g_info.history = ft_calloc(1, sizeof(t_history));
	g_info.history->line = 0;
	g_info.history->prev = 0;
	g_info.history->next = 0;
	g_info.tmp_his = ft_calloc(1, sizeof(t_history));
	g_info.tmp_his->line = 0;
	g_info.tmp_his->prev = 0;
	g_info.tmp_his->next = 0;
	tcgetattr(STDIN, &g_info.term.init);
}

int		main(int ac, char **av, char **envp)
{
	char	*cmdline;
	int		flag;

	set_signal();
	get_env(envp);
	// flag = ac;
	// while (flag)
	init_g_variable();
	while (1)
	{
		// 1. 프롬프트 출력
		// 2. 커맨드라인 가져오기
		// flag = get_cmd_line(&cmdline);
		// ft_strtrim(&cmdline);
		prompt(&cmdline);
		tcsetattr(STDIN, TCSANOW, &g_info.term.init);
		if (!cmdline)
			continue ;
		// 3. 파싱
		init_history();
		g_info.syntax_flag = 0;
		parse(&cmdline);
		free(cmdline);
		// cmdline = 0;
		// system("leaks minishell");
	}
	return (0);
}
