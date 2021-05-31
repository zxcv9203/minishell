#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd;
	// 표준입력은 터미널에 연결되어있으므로 1을 반환
	printf("%d\n", isatty(0));
	fd = open("test", O_RDONLY);
	// 해당 파일은 터미널에 연결되어 있지 않기 때문에 0을 반환
	printf("%d\n", isatty(fd));

	fd = open("/dev/ttyp0", O_RDONLY);
	if (fd == -1)
	{
		printf("open Err\n");
		return (0);
	}
	printf("%d\n", isatty(fd)); // 터미널에 연결되어있기 때문에 1이 반환된다.
	close(fd);
}
