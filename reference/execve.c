#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

extern char **environ;

int main(int argc, char *argv[])
{
	char **cmd;
	int idx;

	idx = -1;
	cmd = (char **)malloc(sizeof(char *) * (argc + 1));
	while (idx++ < argc)
		cmd[idx] = argv[idx];
	/* argc를 execve 파라미터에 전달할 수 없기 때문에 NULL이 파라미터의 끝을 의미함 */
	cmd[argc] = NULL;
	if(execve("/bin/cat", cmd, 0) == -1)
	{
		perror("Error: ls: ");
		return (1);
	}
	printf("ls 명령어로 실행로직이 변경되어서 이후의 로직은 실행되지 않습니다.");
	return (0);
}

