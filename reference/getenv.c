#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	char *s;

	s = getenv("LANG");
	printf("%s", s);
}
