#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	int fd[2];
	char buff[100];
	pid_t pid;
	pid_t wait_pid;
	int stat;

	if (pipe(fd) == -1)
	{
		printf("pipe Error\n");
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		printf("fork Error\n");
	}
	if (pid > 0)
	{
		read(fd[0], buff, 25);
		printf("부모 프로세스 출력 : %s\n\n", buff);
		write(fd[1], "goodjob\n", 25);
		wait_pid = wait(&stat);
		if (wait_pid == -1)
		{
			perror("Error: wait: ");
			return 0;
		}
	}
	else
	{
		write(fd[1], "connect\n", 25);
		sleep(2);
		read(fd[0], buff, 25);
		printf("자식 프로세스 출력 : %s\n\n", buff);
	}
}
