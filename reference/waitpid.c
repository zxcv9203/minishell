#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>

int main(void)
{
	pid_t pid;
	int stat;
	int ret;

	pid = fork();
	if (pid == -1)
		return (printf("fork 생성 실패"));
	if (pid > 0)
	{
		printf("부모 PID : %d, PID: %d\n", getpid(), pid);
		sleep(3);
		ret = waitpid(pid, &stat, WNOHANG); // 자식 프로세스를 기다리지 않고 그냥 종료함
		printf("부모 프로세스 종료 ret: %d errno: %d\n", ret, errno);
		exit(0);
	}
	else if (pid == 0)
	{
		printf("자식 PID : %d\n", getpid());
		sleep(5);
		printf("자식 프로세스 종료함");
	}
}
