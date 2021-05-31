#include <stdio.h>

typedef struct	s_tmp
{
	int *num;
}				t_tmp;

t_tmp test(void)
{
	int a = 1;
	t_tmp tmp;
	tmp.num = &a;
	printf("%p\n", tmp.num);
	return (tmp);
}

int main(void)
{
	t_tmp tmp = test();
	printf("%p\n", tmp.num);
	printf("%d\n", *(tmp.num));
}
