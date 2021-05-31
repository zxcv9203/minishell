/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 18:03:18 by kankim            #+#    #+#             */
/*   Updated: 2021/05/30 20:42:08 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_PARSE_H
# define SHELL_PARSE_H

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <term.h>
# include "minishell.h"


# define STDIN 			0
# define STDOUT 		1
# define STDERR 		2
// token flag
# define SEMICOLON		0	// ;
# define REDIRIN		1	// <
# define REDIROUT		2	// >
# define REDIRAP		3	// >>
# define PIPE			4	// |
// syntax error code
# define ERROR_B_SLASH	1
# define ERROR_QUOTE	2
# define ERROR_RDIR_O	3
# define ERROR_RDIR_A	4
# define ERROR_RDIR_I	5

# define ERROR_NULL -7
# define ERROR_COLON2 -5
# define ERROR_PIPE2 -4
# define ERROR_COLON -3
# define ERROR_PIPE -2

typedef struct			s_arg_list
{
	char				*data;
	struct s_arg_list	*next;
}						t_arg_list;

typedef struct			s_node_info
{
	t_arg_list			*arg;
	int					arg_cnt;
	int					*arg_len;
	int					token_flag;
	int					n_opt;
}						t_node_info;

typedef struct			s_term
{
	struct termios		set;
	struct termios		init;
	char				*cm;
	char				*ce;

}						t_term;

typedef struct			s_cmd_list
{
	char				**arg;
	int					n_opt;
	int					argc;
	int					flag;
	int					fd[2];
	int					redir_in;
	int					redir_out;
	int					stat;
	struct s_cmd_list	*next;
	struct s_cmd_list	*prev;
}						t_cmd_list;

typedef struct			s_cursor_pos
{
	int					col;
	int					row;
}						t_cursor_pos;

typedef struct			s_history
{
	char 				*line;
	struct s_history	*next;
	struct s_history	*prev;
}						t_history;




// check_syntax
int						check_syntax(t_cmd_list *cmdlist);

// handle_sig
void					set_signal(void);

// list_util;

t_cmd_list				*new_node(t_node_info info);
void					push_back(t_cmd_list *head, t_node_info info);
t_arg_list				*new_arg_node(char *arg);
void					push_arg_back(t_arg_list *head, char *str);

// parse_util
int						isflag(char *str, int *i);
int						ft_isspace(char c);

// parse_handle_env

char					*get_env_key(char *env_str);
int						is_exist_env_key(char *key);
char					*get_env_val(char *key);

// parse_handle_node

void					init_node_info(t_node_info *ret);
void					remove_node_arg_list(t_arg_list *node);
void					free_node_info(t_node_info *target);
void					free_cmdlist(t_cmd_list *cmdlist);

// parse_handle_quote

int						is_env_char(char c);
void					check_env(char **cmdline, int *i);
void					handle_escape(char **cmdline, int *i);
void					handle_quote_at_arg_cnt(char **cmdline, int *i);
void					handle_quote_at_arg_len(char *cmdline, int *i);
void					handle_escape_without_quote(char **cmdline, int *i);
void					handle_exit_status(char **cmdline, int s, int *i);

// parse_manipulate_string

void					get_arg(char *dst, char *cmdline, int s, int e);
void					insert_str(char **dst, char *src, int i);
void					remove_str(char **str, int s, int e);

// parse

void					get_arg_cnt(t_node_info *node, char **cmdline, int i);
void					get_arg_len(t_node_info *node, char **cmdline, int *i);
t_node_info				get_node_info(char **cmdline, int *i);
void					parse(char **cmdline);

// prompt
void					ascii_art(void);
void					prompt(char **cmdline);
void					init_history(void);

// util
void					ft_write(char *buf, int fd);
void					*ft_calloc(size_t count, size_t size);
void					*ft_memcpy(void *dst, const void *src, size_t n);
char					**ft_split(char const *s, char c);
void					ft_strtrim(char **str);
char					*ft_strdup(const char *s1);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memmove(void *dest, const void *src, size_t count);
size_t					ft_strlcpy(char *dst, const char *src, size_t dstsize);
char					*ft_substr(char const *s, unsigned int start, size_t len);
int						ft_strncmp(const char *string1, const char *string2, size_t count);
char					*ft_itoa(int n);
int						ft_atoi(const char *str);
int						ft_putchar(int c);
int						ft_isprint(char c);

#endif
