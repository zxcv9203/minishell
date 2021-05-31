#include "minishell.h"

static char **copy_envp(char **envp)
{
	char **copy;
	int i;

	i = 0;
	while (envp[i])
		i++;
	copy = ft_calloc(i + 1, sizeof(char **));
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		i++;
	}
	return (copy);
}

int main(int argc, char **argv, char **envp)
{
	t_cmd_list parse;
	t_cmd_list parse2;
	t_cmd_list parse3;
	t_cmd_list parse4;
	t_cmd_list parse5;
	t_cmd_list parse6;
	t_cmd_list parse7;

	(void)argv;
	(void)argc;

	parse.argc = 2;
	parse.arg = malloc(sizeof(char *) * 14);
	parse.arg[0] = "ls";
	parse.arg[1] = "-al";
	parse.arg[2] = 0;
	parse.arg[3] = 0;
	parse.arg[4] = "";
	parse.arg[5] = 0;
	parse.flag = 0;
	parse.flag = PIPE;
	parse.n_opt = 0;
	parse.next = 0;
	parse.next = &parse2;
	parse.prev = 0;
	parse.redir_out = 1;
	parse.redir_in = 0;

	parse2.argc = 1;
	parse2.arg = malloc(sizeof(char *) * 10);
	parse2.arg[0] = "grep";
	parse2.arg[1] = "d";
	parse2.arg[2] = 0;
	parse2.arg[3] = 0;
	parse2.flag = 0;
	// parse2.flag = REDIRECTION_R;
	parse2.next = 0;
	parse2.prev = &parse;
	// parse2.next = &parse3;
	parse2.fd[0] = 0;
	parse2.redir_out = 1;
	parse2.redir_in = 0;

	parse3.arg = malloc(sizeof(char *) * 10);
	parse3.arg[0] = "tmp2";
	parse3.arg[1] = 0;
	parse3.arg[2] = 0;
	parse3.arg[3] = 0;
	parse3.flag = 0;
	parse3.flag = REDIRECTION_A;
	parse3.prev = &parse2;
	parse3.next = 0;
	parse3.fd[0] = 0;
	parse3.next = &parse4;
	parse3.redir_out = 1;
	parse3.redir_in = 0;

	parse4.arg = malloc(sizeof(char *) * 10);
	parse4.arg[0] = "tmp3";
	parse4.arg[1] = 0;
	parse4.arg[2] = 0;
	parse4.arg[3] = 0;
	parse4.flag = 0;
	// parse4.flag = REDIRECTION_A;
	parse4.prev = &parse3;
	parse4.n_opt = 1;
	parse4.next = 0;
	parse4.redir_out = 1;
	parse4.redir_in = 0;
	// parse4.next = &parse5;

	parse5.arg = malloc(sizeof(char *) * 10);
	parse5.arg[0] = "tmp2";
	parse5.arg[1] = 0;
	parse5.arg[2] = 0;
	parse5.arg[3] = 0;
	parse5.flag = 0;
	parse5.flag = REDIRECTION_R;
	parse5.prev = &parse4;
	parse5.next = 0;
	parse5.next = &parse6;
	parse5.redir_out = 1;
	parse5.redir_in = 0;

	parse6.arg = malloc(sizeof(char *) * 10);
	parse6.arg[0] = "tmp3";
	parse6.arg[1] = 0;
	parse6.arg[2] = 0;
	parse6.arg[3] = 0;
	parse6.flag = 0;
	parse6.flag = 0;
	parse6.prev = &parse5;
	parse6.next = 0;
	// parse6.next = &parse7;
	parse6.redir_out = 1;
	parse6.redir_in = 0;

	parse7.arg = malloc(sizeof(char *) * 10);
	parse7.arg[0] = "tmp5";
	parse7.arg[1] = 0;
	parse7.arg[2] = 0;
	parse7.arg[3] = 0;
	parse7.flag = 0;
	parse7.prev = &parse6;
	parse7.next = 0;
	parse7.redir_out = 1;
	parse7.redir_in = 0;

	g_info.env = copy_envp(envp);

	excute_cmd(&parse);
	// system("leaks minishell");
}
