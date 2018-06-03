#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<termio.h>
int getch(){
	int ch;
	struct termios buf;
	struct termios save;
	tcgetattr(0,&save);
	buf=save;
	buf.c_lflag&=~(ICANON|ECHO);
	buf.c_cc[VMIN]=1;
	buf.c_cc[VTIME]=0;
	tcsetattr(0,TCSAFLUSH,&buf);
	ch=getchar();
	tcsetattr(0,TCSAFLUSH,&save);
	return ch;
    }
int main();
int alp(){
	char answer;
	int progress=0, fault=0, accurate=0, answer_count=0;
	int correct_answer=0;
	int a,esc;

	char quest[52]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	
    int num;
	
	system("clear");

	for(a=0;a<20;a++){
		srand(time(NULL));
		num=rand()%52;
		while(1){
			printf(">>영문타자 연습 프로그램: 자리 연습<<\n");
			if(answer_count==0){
			
				printf("진행도:%d%%, 오타수:%d, 정확도:%.0f%%\n",progress*5,fault,0);
			}
			else
				printf("진행도:%d%%, 오타수:%d, 정확도:%.0f%%\n",progress*5,fault,(float)accurate*100/answer_count);

			printf("%c\n",quest[num]);
			answer=getch();
			answer_count++;
			printf("%c\n",answer);
			system("clear");
			if(quest[num]==answer){
				progress++; accurate++;
				break;
		    }
			else{	 
				fault++;
				if(answer==27)
				main();
			}  
		}
	}
	printf(">>영문타자 연습 프로그램: 자리 연습<<\n");
	printf("진행도:%d%%, 오타수:%d, 정확도:%.0f%%\n",progress*5,fault,(float)accurate*100/answer_count);
	return 0;
}
int main(){
	alp();
	return 0;
}
