#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(void)
{
	int fd;

	fd = open("dup2_test", O_RDWR | O_CREAT | O_APPEND, 0744);
	if (fd < 0)
	{
		perror("open: ");
		return (0);
	}
	// printf의 출력 값이 표준출력이기 때문에 dup2_test에 1이 저장되는 것을 확인할 수 있음
	printf("%d", dup2(fd, 1));

}
