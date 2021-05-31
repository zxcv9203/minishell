/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 16:48:25 by yongckim          #+#    #+#             */
/*   Updated: 2021/05/31 22:36:43 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
*** includes ***
*/
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>

# include "../libft/libft.h"
# include "shell_parse.h"

/*
*** defines ***
*/

# define SUCCESS 1
# define CHILD_PROCESS 0

typedef enum			e_flag
{
	SEMICOL = 0,
	REDIRECTION_L,
	REDIRECTION_R,
	REDIRECTION_A,
	PI
}						t_flag;

/*
*** structs ***
*/

typedef struct			s_process
{
	int					builtin;
	pid_t				pid;
	pid_t				wait_pid;
	int					pid_stat;
	int					fd[2];
}						t_process;

typedef struct			s_path
{
	char				**env_list;
	char				*env;
	char				*cmd;
	int					save_fd[2];
}						t_path;

typedef struct			s_global
{
	char				**env;
	int					exit_status;
	t_term				term;
	t_cursor_pos		cur_max;
	t_cursor_pos		cur;
	t_history			*history;
	t_history			*tmp_his;
	int					syntax_flag;
	int					shell_var;
}						t_global;

t_global				g_info;

/*
*** excute
*/

int						excute_cmd(t_cmd_list *list);
int						excute_func(t_cmd_list *origin,
										t_path *path, int flag);

/*
***	builtin_func
*/

int						builtin_check(t_cmd_list *list);
int						excute_echo(t_cmd_list *data);
int						excute_cd(t_cmd_list *data);
int						excute_env(void);
int						excute_exit(t_cmd_list *data);
int						excute_export(t_cmd_list *data);
int						excute_pwd(void);
int						excute_unset(t_cmd_list *data);

/*
***	execve excute
*/

int						find_command(t_cmd_list *list, t_path *path);
int						search_cmd(char *cmd, char *path);
char					*dir_append(char *path, char *cmd);
void					excute_bin(t_cmd_list *data, char *path);
char					*join_path(char *cmd);

/*
*** environment
*/

char					*parse_key(char *arg);
int						export_env(t_cmd_list *list);

/*
***	error
*/

void					ft_error(char *cmd, char *value,
									char *err, int err_code);

/*
*** PIPE & redirect
*/
void					exec_pipe(t_cmd_list *cmd, t_cmd_list *file,
									t_path *path);
void					redirect_desc(t_cmd_list *list);
char					**append_args(t_cmd_list *list,
										t_cmd_list *origin);
t_cmd_list				*create_file(t_cmd_list *list, t_cmd_list *origin);
t_cmd_list				*redirect_cmd(t_cmd_list *list,
									t_cmd_list *origin, t_path *path);
t_cmd_list				*echo_option_check(t_cmd_list *origin);

/*
*** end ***
*/

#endif
