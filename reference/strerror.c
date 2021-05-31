#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int fd;

	fd = open("notexist", O_RDONLY);
	if (fd == -1)
	{
		//존재하지 않은 파일을 열기 때문에 에러발생
		printf("Error: open: %s", strerror(errno));
		return 0;
	}
	close(fd);
	printf("ok");
}
