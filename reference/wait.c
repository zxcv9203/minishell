#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>

void wait_case()
{
	pid_t pid;
	pid_t wait_pid;
	int stat;

	pid = fork();
	if (pid == -1)
	{
		perror("Error: wait: ");
		return ;
	}
	if (pid > 0)
	{
		printf("부모 PID : %d, 리턴값 : %d\n", getpid(), pid);
		wait_pid = wait(&stat);
		if (wait_pid == -1)
		{
			perror("Error: wait: ");
			return ;
		}
		if (WIFEXITED(stat))
			printf("자식 프로세스가 정상적으로 종료되었습니다. %d\n", WEXITSTATUS(stat));
		else if (WIFSIGNALED(stat))
			printf("자식 프로세스가 비정상적으로 종료되었습니다. %d\n", WIFSIGNALED(stat));
		printf("부모 프로세스 종료 %d %d\n", wait_pid, WTERMSIG(stat));
	}
	else if (pid == 0)
	{
		printf("자식 PID: %d 리턴값 : %d\n", getpid(), pid);
		sleep(100);
		printf("자식 프로세스 종료\n");
	}
}

int main(void)
{
	wait_case();
	// kill 명령어를 사용해서 비정상적인 종료 확인해보기
}
