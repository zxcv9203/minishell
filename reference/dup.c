#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
	int fd;
	int fd2;
	int dup_fd;
	char *msg = "hello dup";

	fd = open("test", O_RDWR | O_CREAT, 0744);
	/*
		파일 이름은 test
		읽기 쓰기가 가능한 형태로 열고 만약 파일이 존재하지 않을 경우 생성함,
		권한은 744로 설정
	*/
	if (fd < 0)
	{
		printf("File open error\n");
		return (0);
	}
	dup_fd = dup(fd);
	write(dup_fd, msg, strlen(msg));
	printf("%d %d %d\n", fd, dup_fd);
	close(fd);
	close(dup_fd);

}
