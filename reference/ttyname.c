#include <unistd.h>
#include <stdio.h>

int main(void)
{
	printf("Your tty name is : %s\n", ttyname(0));
}
