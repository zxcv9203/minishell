#include <stdio.h>
#include <termios.h>

int main(void)
{
	struct termios is_term;
	struct termios term_set;
	char buf[100];

	tcgetattr(0, &is_term);
	term_set.c_lflag &= (~ISIG); //특정 시그널을 무시하게 됨
	tcsetattr(0, TCSANOW, &term_set); // TCSANOW -> 속성을 바로변경하는 동작코드
	while(1)
	{
		//해당 코드 실행중에 ctrl + c를 이용해서 종료하려고해도 무시되고 계속실행됨
		fgets(buf, 100, stdin);
		fputs(buf, stdout);
	}
}
