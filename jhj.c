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
	char answer;//입력받을 변수
	int progress=0, fault=0, accurate=0, answer_count=0;//진행도,오타수,정확도,입력한갯수를 우한 변수선언
	int correct_answer=0;//맞게 입력한 답을 위한 변수
	int a,esc;//종료를 위한 변수선언

	char quest[52]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};//화면에 하나씩 띄워질 알파벳
	
    int num;//수를 램덤으로 뽑아 저장하기위한 변수선언
	
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

			printf("%c\n",quest[num]);//알파벳중 랜덤으로 하나를 띄워줌
			answer=getch();//엔터없이 문자를 받아줌
			answer_count++;//입력한수 증가
			printf("%c\n",answer);
			system("clear");
			if(quest[num]==answer){//제시한 알파벳과 입력해준 알바펫이 같으면 
				progress++; accurate++;//진행도,정확도를 증가시켜줌
				break;
		    }
			else{	 
				fault++;//제시한 알파벳과 입력해준 알파벳이 다르면 오류변수를 증가시켜줌
				if(answer==27)//esc를 누르면 메인으로 돌아감
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
