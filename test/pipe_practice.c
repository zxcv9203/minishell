#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	int pi[2];
	pid_t	pid;
	pid_t	wait_pid;
	int		pid_stat;
	char s[100];
	pipe(pi);
	pid = fork();
	if (pid > 0)
	{
		pid_stat = wait(&wait_pid);
		close(pi[1]);
		read(pi[0], s, 100);
		printf("%s\n", s);

	}
	else if (pid == 0)
	{
		close(pi[0]);
		write(pi[1], "asd", 3);
		return (0);
	}
}