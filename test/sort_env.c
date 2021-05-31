#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct			s_cmd_list
{
	char				**arg;
	int					argc;
	int					flag;
	struct s_cmd_list	*next;
	struct s_cmd_list	*prev;
}						t_cmd_list;


void	ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	while (*(s + i))
		i++;
	write(fd, s, i);
}


int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

static void	sort_env(char **envp)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	while (*(envp + i))
	{
		j = i + 1;
		while (*(envp + j))
		{
			if (ft_strcmp(*(envp + i),*(envp + j)) > 0)
			{
				tmp = *(envp + i);
				*(envp + i) = *(envp + j);
				*(envp + j) = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	export_print(char **envp)
{
	int i;

	i = 0;
	sort_env(envp);
	while (*(envp + i))
	{
		ft_putstr_fd("declare -x \"", 1);
		ft_putstr_fd(envp[i], 1);
		ft_putstr_fd("\"\n", 1);
		i++;
	}
}

int		excute_export(t_cmd_list list, char **envp)
{
	char **cp_envp;

	cp_envp = envp;
	if (!(*(list.arg + 1)))
		export_print(cp_envp);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	t_cmd_list list;

	list.arg = (char **)malloc(2);
	list.arg[0] = "export";
	list.arg[1] = 0;
	excute_export(list, envp);
}
