#include <unistd.h>
#include <stdio.h>

void check_process(void)
{
    pid_t pid;
    int n;

    n = 0;
    pid = fork();	//부모 프로세스와 자식 프로세스의 분기가 나누어지면서 실행되기 때문에 부모와 자식 프로세스를 다 확인할 수 있다.
    if (pid == -1)
	{
        printf("fork failed\n");
        return ;
    }
    if(pid > 0)			// 부모프로세스의 반환 값은 자식프로세스의 PID이기 때문에 1이상의 수가 온다.
	{
        x += 1;
        printf("부모 PID : %ld,  n : %d , pid : %d\n",(long)getpid(), n, pid);
    }
    else if(pid == 0)	// 자식프로세스의 반환 값은 0이다
	{
        x += 2;
    	printf("자식 PID : %ld,  n : %d, pid: %d\n",(long)getpid(), n, pid);
    }
}

int main(void)
{
	check_process();
}
