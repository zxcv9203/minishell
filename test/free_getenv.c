#include <stdio.h>
#include <stdlib.h>

static char	*ret_value(char *env)
{
	char	*value;
	int		i;

	i = 0;
	value = env;
	return (value);
}

char		*ft_getenv(const char *name, char **envp)
{
	int i;
	int j;
	char *value;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] == name[j])
		{
			if (envp[i][j + 1] == '=' && !name[j + 1])
			{
				value = ret_value(&envp[i][j + 2]);
				return (value);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}
int ss(void)
{
	char *env;

	env = getenv("USER");
	printf("%s\n", env);
	//free(env);
	return (1);
}
int dd(char **envp)
{
	char *env;

	env = ft_getenv("USER", envp);
	printf("%s\n", env);
	//free(env);
	return (1);
}
int main(int argc, char **argv, char **envp)
{
	ss();
	dd(envp);
	system("leaks a.out");
}
