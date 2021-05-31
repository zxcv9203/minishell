#include "minishell.h"

// void ascii_art(void)
// {
// 	char	**buf;
// 	int		fd;
// 	char	*line;

// 	buf = malloc(sizeof(char *) * 30);

// 	// get bash img
// 	fd = open("../img/bash", O_RDONLY);
// 	int i = 0;
// 	while (get_next_line(fd, &line))
// 	{
// 		*(buf + i) = line;
// 		// printf("%d	%p	%s\n", i, buf + i, *(buf + i));
// 		// free(line);
// 		++i;
// 	}
// 	*(buf + i) = line;
// 	close(fd);
// 	// printf("%d	%p	%s\n", i, &buf, *(buf + i));
// 	// free(line);

// 	// printf("\n");

// 	// print bash img
// 	for (int j = 0; j < 30; ++j)
// 		printf("%d	%p	%s\n", j, (buf + j), *(buf + j));
// 	int time = 0;
// 	while (time++ < 100000000)
// 		;

// 	// get minishell by line
// 	fd = open("../img/minishell", O_RDONLY);
// 	for (int i = 0; i < 30; ++i)
// 	{
// 		system("clear");
// 		get_next_line(fd, &line);
// 		free(*(buf + i));
// 		*(buf + i) = line;
// 		// free(line);
// 		for (int j = 0; j < 30; ++j)
// 			printf("%s\n", *(buf + j));
// 		time = 0;
// 		while (time++ < 300000000)
// 			;
// 	}
// 	close(fd);

// 	for (int j = 0; j < 30; ++j)
// 		free(*(buf + j));
// 	free(buf);

// 	puts("");
// 	// system("leaks a.out");

// }

void	set_terminal(void)
{
	tcgetattr(STDIN, &g_info.term.set);
	g_info.term.set.c_lflag &= ~ICANON;
	g_info.term.set.c_lflag &= ~ECHO;
	g_info.term.set.c_cc[VMIN] = 1;
	g_info.term.set.c_cc[VTIME] = 0;
	tcsetattr(STDIN, TCSANOW, &g_info.term.set);
	tgetent(NULL, "xterm");
	g_info.term.cm = tgetstr("cm", NULL);
	g_info.term.ce = tgetstr("ce", NULL);
}

void	init_set_cursor(char buf[255], int *read_ret, int *i, int *flag)
{
	write(0, "\033[6n", 4);
	*read_ret = read(0, buf, 254);
	if (*read_ret < 0)
		*read_ret = 0;
	buf[*read_ret] = '\0';
	*i = 0;
	*flag = 0;
}

int		get_nbr_len(int n)
{
	int	ret;

	ret = 0;
	while (n > 0)
	{
		n /= 10;
		ret++;
	}
	return (ret);
}

void	set_cursor(int *col, int *row)
{
	int		i;
	int		flag;
	char	buf[255];
	int		read_ret;

	init_set_cursor(buf, &read_ret, &i, &flag);	// read_ret is 
	while (buf[++i])
	{
		if ('0' <= buf[i] && buf[i] <= '9')
		{
			if (flag == 0)
				*row = ft_atoi(&buf[i]) - 1;
			else
			{
				*col = ft_atoi(&buf[i]) - 1;
				break ;
			}
			flag++;
			i += get_nbr_len(*row) - 1;
		}
	}
}

void	get_max_cursor(void)
{
	struct winsize	w_size;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w_size);
	g_info.cur_max.col = w_size.ws_col;
	g_info.cur_max.col = w_size.ws_col;
}

void	handle_eof(void)
{
	if (!g_info.tmp_his->line || !*g_info.tmp_his->line)	// 현재 입력된 라인이 널 문자이면
	{
		printf("exit\n");
		tcsetattr(STDIN_FILENO, TCSANOW, &g_info.term.init);
		exit(0);
	}
}

void	remove_last_char(void)
{
	const int	len = ft_strlen(g_info.tmp_his->line);
	char		*tmp;
	int			i;

	tmp = (char *)ft_calloc(len, sizeof(char));
	i = -1;
	while (++i < len - 1)
		tmp[i] = g_info.tmp_his->line[i];
	free(g_info.tmp_his->line);
	g_info.tmp_his->line = tmp;
}

void	put_backspace(void)
{
	int	col;
	int	row;

	set_cursor(&col, &row);
	if (!g_info.tmp_his->line || !*g_info.tmp_his->line)
		return ;
	col--;
	if (col < 0)
	{
		--row;
		col = g_info.cur_max.col - 1;
	}
	tputs(tgoto(g_info.term.cm, col, row), 1, ft_putchar);
	tputs(g_info.term.ce, 1, ft_putchar);
	remove_last_char();
}

void	press_up(void)
{
	int row;
	int col;

	if (!g_info.tmp_his->prev || !g_info.tmp_his->prev->line)
		return ;
	g_info.tmp_his = g_info.tmp_his->prev;
	set_cursor(&col, &row);
	tputs(tgoto(g_info.term.cm, 11, row), 1, ft_putchar);
	tputs(g_info.term.ce, 1, ft_putchar);
	ft_write(g_info.tmp_his->line, 1);
}

void	press_down(void)
{
	int row;
	int col;

	if (!g_info.tmp_his->next)
		return ;
	g_info.tmp_his = g_info.tmp_his->next;
	set_cursor(&col, &row);
	tputs(tgoto(g_info.term.cm, 11, row), 1, ft_putchar);
	tputs(g_info.term.ce, 1, ft_putchar);
	ft_write(g_info.tmp_his->line, 1);
}

char	*ft_strcjoin(char *str, char c)
{
	char	*ret;
	int		i;

	if (!str)
	{
		ret = (char *)ft_calloc(2, sizeof(char));
		ret[0] = c;
		ret[1] = 0;
	}
	else
	{
		ret = ft_calloc(ft_strlen(str) + 2, sizeof(char));
		i = -1;
		while (str[++i])
			ret[i] = str[i];
		ret[i] = c;
		ret[i + 1] = '\0';
		free(str);
	}
	return (ret);
}

void	print_save_char(char c)
{
	g_info.tmp_his->line = ft_strcjoin(g_info.tmp_his->line, c);
	write(1, &c, 1);
}

void	handle_keycode(int keycode)
{
	if (keycode == 4)
		handle_eof();
	else if (keycode == 127)
		put_backspace();
	else if (keycode == 4283163)
		press_up();
	else if (keycode == 4348699)
		press_down();
	else
	{
		if (ft_isprint((char)keycode))
			print_save_char((char)keycode);
	}
}

void	term_loop(void)
{
	int		c;

	get_max_cursor();
	set_cursor(&g_info.cur.col, &g_info.cur.row);
	c = 0;
	while (read(0, &c, sizeof(c)) > 0)
	{
		if (c == '\n')
		{
			write(1, "\n", 1);
			return ;
		}
		else
			handle_keycode(c);
		c = 0;
	}
}

void	free_tmp_his(void)
{
	t_history *tmp;

	tmp = g_info.tmp_his;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp->next)
	{
		free(tmp->line);
		tmp->line = 0;
		free(tmp->prev);
		tmp->prev = 0;
		tmp = tmp->next;
	}
	free(tmp->line);
	tmp->line = 0;
	free(tmp->prev);
	tmp->prev = 0;
	g_info.tmp_his = tmp;
}

void	push_back_history(t_history *node, char *str)
{
	t_history *new;

	new = (t_history *)ft_calloc(1, sizeof(t_history));
	new->line = ft_strdup(str);
	new->prev = node->prev;
	new->next = node;
	if (node->prev)
		node->prev->next = new;
	node->prev = new;
}

void	copy_history(void)
{
	t_history *tmp;
	t_history *tmp2;

	tmp = g_info.history->prev;
	tmp2 = g_info.tmp_his;
	while (tmp)
	{
		push_back_history(tmp2, tmp->line);
		tmp = tmp->prev;
		tmp2 = tmp2->prev;
	}
}

void	init_history()
{
	// 명령에 사용한 라인 히스토리에 입력
	push_back_history(g_info.history, g_info.tmp_his->line);
	// 템프 히스토리 프리
	free_tmp_his();
	// 히스토리를 템프히스토리에 복사
	copy_history();
}


void	prompt(char **cmdline)
{
	set_terminal();
	ft_write("minishell$ ", STDOUT);
	term_loop();	// 개행이 들어올때 까지 들어온 입력 처리
	if (g_info.tmp_his->line)
		*cmdline = ft_strdup(g_info.tmp_his->line);
	else
		*cmdline = 0;
}