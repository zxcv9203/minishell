#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>

int main(void)
{
	pid_t pid;
	int stat;

	pid = fork();
	if (pid == -1)
	{
		perror("Error: wait: ");
		return (0);
	}
	if (pid > 0)
	{
		printf("부모 PID : %d, 리턴값 : %d\n", getpid(), pid);
		sleep(1);
		if(kill(pid, 9) == 0)
			printf("자식 프로세스 kill에 성공했습니다.\n");
		else
			printf("자식 프로세스 kill에 실패하였습니다.\n");
		printf("부모 프로세스 종료\n");
	}
	else if (pid == 0)
	{
		printf("자식 PID: %d 리턴값 : %d\n", getpid(), pid);
		sleep(3);
		printf("자식 프로세스 종료\n");
	}
}
