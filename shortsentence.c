#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<termio.h>
#include<string.h>
int getch(void){
	int ch;
	struct termios buf;
	struct termios save;
	tcgetattr(0,&save);
	buf = save;
	buf.c_lflag &= ~(ICANON | ECHO);
	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, &buf);
	ch = getchar();
	tcsetattr(0,TCSAFLUSH,&save);
	return ch;
}
int f_progress(int size, int i, int k){    // 진행도 계산하는 함수
	return k*20 + (i+1)*20/size;
}
int f_accuracy(int i, int x){              // 정확도 계산하는 함수
	return (i+1-x)*100/(i+1);
}
int main(void){
	char finish = {0}, str[30][100]={"We don't know a million of one percent about anything","Gravitation cannot be held responsible for people falling in love","There is no remedy for love but to love more","A man apt to promise is apt to forget","Success isn't permanent, and failure fatal","All people want is some to listen","A faltter is a friend who is your inferior, or pretends to be so","A friend should bear his friend's infirmities","The multitude of books is making us ignorant","Prediction is very difficult, especially about the future","I tend to live in the past because most of my life is there","Employ thy time well, if thou meanest to get lesuire","The future will be better tomorrow","Nothing is as far away as one minute ago","A single day is enough to make us a little larger","The empires of the future are the empires of the mind","Early morning hath gold in its mouth","The Bible promises no loaves to the loafer","You need chaos in your soul to give birth to a dancing star","It's not that I'm so smart, it's just that I stay with problems longer","As long as you derive inner help and comfort from anything, keep it","We cannot really love anybody with whom we never laugh","Human beings have an inalienable right to invent themselves","While there's life, there's hope","What we dwell on is who we become","A day without laughter is a day wasted","Laughter is by definition healthy","Hope is only the love of life","Wheresoever you go, go with all your heart","The greatest risk is the risk of riskless living"};  // 30 문장

	int finalaccuracy, progress = 0 ,n,np[10]={0};           // finalaccuracy 마지막 정확도 저장,  progress 진행도, n은 랜덤으로 지정된 수 저장, np[10]은 랜덤으로 지정된 수들 저장
	time_t start,end;                                        // start 타이핑 치기 시작한 시간 end  한 타를 치고 끝난 시간
	double finalbtype,finalntype;                            // finalntype 마지막 현재타수 저장,finalbtype 마지막 최고타수 저장 
	srand(time(NULL));                                       // 똑같은 난수 안나오게
	for(int k=0;k<5;k++){                                    // 짧은글 타자 연습 5번 반복
		char arr[100]={0};                                   // 입력받을 문자 저장공간
		int x=0, y=0, i=0, accuracy=0, size=0;           	 // x는 오타개수 y는 맞은개수 i는 while 문에서 사용 accuracy는 정확도 size는 출력문장길이
		double ntype=0, btype=0;                             // ntype은 현재타수 btype은 최고타수

		n=rand()%30;                                         // 랜덤으로 수 생성
		np[k]=n;
		for(int j=0;n!=np[j];j++){                           // 5문장중 중복되는 문장이 있지 않도록 하는 과정
				n=rand()%30;
				np[k]=n;
		}
		size = strlen(str[n]);                               // 문장의 길이
		start = time(NULL);                                  
		while(1){ 
			printf(">>영문 타자 연습 프로그램: 짧은 글 연습<<\n");
			printf("진행도: %d, 현재타수:%.0lf, 최고타수:%.0lf, 정확도:%d%%\n\n",progress,ntype,btype,accuracy);
			printf("%s\n",str[n]);
			printf("%s",arr);
			arr[i]=getch();
			end = time(NULL);
			
			if(arr[i]==127)                                   // backspace 입력시
				if(i==0)
					i--;
				else{
					i--;
					if(arr[i]!=str[n][i])
						x--;
					accuracy = f_accuracy(i,x);
					arr[i] = '\0';
					progress = f_progress(size,i,k);
					i--;
				}
			else if(arr[i] != str[n][i] && arr[i] != '\n' && arr[i] != 127 && arr[i] != 27){          // 입력한 문자가 틀렸을 경우
				x++;
				progress = f_progress(size,i,k);
				accuracy = f_accuracy(i,x);
			}
			else if(arr[i]=='\n' || arr[i]==27){                                      // 엔터를 치거나 ESC 입력시 while문 탈출
				system("clear");
				break;
			}
			else{                                                                     // 입력한 문자가 맞을 경우
				y++;
				progress = f_progress(size,i,k);
				accuracy = f_accuracy(i,x);
			}
			
			ntype = 60 / ((double)(end-start)/y);                                     // 현재타수 구함

			if(ntype > btype)                                                         // 최고타수 구함
				btype = ntype;

			i++;
			system("clear");
		}
		if(k==4){                                                                     // 5개 문장 다 입력한 후 마지막에 나왔던 진행도,현재타수,최고타수,정확도 출력하기 위해 각 변수에 저장
			finalbtype = btype;
			finalntype = ntype;
			finalaccuracy = accuracy;
		}


		if(arr[i] == 27){                                                          // ESC 입력시 메뉴로 복귀
			finish = 27;
			break;
		}
	}
	while(1){
	if(finish !=27){                                                                 // ESC를 입력하지 않았고 마지막 문장이 끝나고 난 뒤 
		printf(">>영어 타자 연습 프로그램 : 짧은 글 연습\n\n");
		printf("진행도: %d  평균타수:%.2lf 최고타수:%.2lf  정확도:%d \n\n",progress,finalntype,finalbtype,finalaccuracy);
		printf("짧은 글 연습이 끝났습니다.\n ESC를 누르면 메뉴로 돌아갑니다.");
		finish = getch();
		system("clear");
	}
	else                                    // ESC 누르면 메뉴로 복귀
		break;
	}
	return 0;
}
