#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>

void ViewRUsage(pid_t pid, struct rusage *pru)
{
    printf("\n=== pid rusage info ===\n");
    struct timeval *tv = &(pru->ru_utime);
    printf("user CPU time used [%ld]sec [%d]usec\n", tv->tv_sec,tv->tv_usec );
    tv = &(pru->ru_stime);
    printf("system CPU time used [%ld]sec [%d]usec\n", tv->tv_sec,tv->tv_usec );
}

int main(void)
{
    pid_t pid;
	pid_t ret;
	int stat;
    struct rusage ru;

	pid = fork();
    if(pid == -1)
    {
        perror("error fork");
        return 0;
    }

    if(pid > 0)
    {
        printf("<parent> fork child pid:%u\n",pid);
        ret = wait3(&stat, 0, &ru);
        ViewRUsage(ret, &ru);
    }
    else
        printf("<child> pid:%d \n", getpid());
}

