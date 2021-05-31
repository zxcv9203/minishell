#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void pwd(void)
{
	char *pwd;

	// pwd = NULL;
	// if (!(pwd = getcwd(pwd, 100)))
	// 	return ;
	pwd = malloc(1);
	printf("%s", pwd);
	free(pwd);

}
int main(void)
{
	pwd();
	system("leaks a.out");
}
