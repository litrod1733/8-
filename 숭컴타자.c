#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <termio.h>
int getch(void) { //getch�Լ� ���� 
	int ch;
	struct termios buf;
	struct termios save;
	tcgetattr(0, &save);
	buf = save;
	buf.c_lflag&=~(ICANON|ECHO);
	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, &buf);
	ch = getchar();
	tcsetattr(0, TCSAFLUSH, &save);
	return ch;
}
int main(void) {
	system("clear");
	char c;
	int i=1;
	while(i) {
		char c;
		printf("**********************************************\n");
		printf("*                                            *\n");
		printf("*  1. �ڸ�����                  2. ��������  *\n");
		printf("*  3. ���忬��                  3. ��ۿ���  *\n");
		printf("*  5. ���α׷� ����                          *\n");
		printf("*                                            *\n");
		printf("**********************************************\n");
		c=getch(); 
		system("clear");
		switch (c) {
			case '1' :
				break;
			case '2' :
				break;
			case '3' :
				break;
			case '4' :
				break;
			case '5' :
				break;
			default :
				break;				
		}
		if(c=='5')
			i=0;
	}
	system("clear");
	printf("**********************************************\n");
	printf("*                                            *\n");
	printf("*                                            *\n");
	printf("*                  THANK YOU!                *\n");
	printf("*                                            *\n");
	printf("*                                            *\n");
	printf("**********************************************\n");
	sleep(2);
	system("clear");
	return 0;
}
