#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_int()
{
	printf("CTRL + C를 한번 더 입력시 종료됩니다.\n");
	signal(SIGINT, SIG_DFL);
}

int main(void)
{
	signal(SIGINT, sig_int);
	while (1)
	{
		printf("looping.....\n");
		sleep(1);
	}
}
