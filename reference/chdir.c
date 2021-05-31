#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char *a;
	int ret;
	char *pwd;

	pwd = getcwd(pwd, 100);
	printf("현재 디렉토리 경로: %s\n", pwd);
	a = "/";
	ret = chdir(a);
	pwd = getcwd(pwd, 100);
	printf("chdir을 이용해 이전 디렉토리로 이동한 경로 : %s\n", pwd);
	if (ret == 0)
		printf("해당 디렉토리로 이동하는데 성공하였습니다.\n");
	else
		printf("해당 디렉토리로 이동하는데 실패하였습니다.\n");
}
