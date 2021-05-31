#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	int fd;

	printf("%d\n", ttyslot());
	fd = open("test", O_RDONLY);
	printf("%d\n", ttyslot());
	close(fd);
	// 어떻게 쓰는지 모르겠음.. 계속 에러발생
}
