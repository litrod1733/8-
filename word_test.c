#include<stdio.h>
#include<string.h>
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
int word();

int main(){
        int select;
        system("clear");
        printf("1:자리연습\n2:낱말연습\n3:짧은글 연습\n4:긴글엽습\n5:프로그램 종료\n");
        select=getchar();
        switch(select){
                case '1':
                    break;
                case '2':
                    word();
                    break;
                case '5':
					exit(1);
                default:
					main();
                    break;
        }
        return 0;
}

int word(){
	char word[100][100]={
"aware","animator","optimistic","outlook","abundance","vigor","positive", "contribution", "dynamics", "definitely", "further","potential","replace","assume","extra","accommodate","donation","essential","betterment","eager","assure","commitment","reputation","diagnostic","paycheck","overtime","current","supervisor","assure","timesheet","glide","sunbeam","twilight","portrait","sparkling","brilliant","script","confidence","overcome","anxiety","available","trustful","electric","bargain","collaborator","vein","fiercely","shin","shatter","chrome","reapply","lap","christening","bride","reception","entertain","general","operate","architecture","undivided","recall","threaten","precious","appealing","preservation","stir","component","transmit","tragedy","profound","sustainability","estimate","luxury","merchandise","myth","alternative","direct","survey","reveal","perceive","variation","simultaneous","sequential","conscious","test","subset","reveal","viewpoint","involved","refuse","perception","impress","dishonesty","befriend","identity","genuine","unique","pictorial","proof","mindfulness"};
	int progress=0, fault_num=0, accurate=0,i;	//progress:진행도 fault_num:오타수 accurate:정확도
	int random;									//random:무작위word를 추출하기 위한 인덱스값 저장 
	int length=0,N;								//length:문자의 길이	N:word의 길이
	int end=0;									//end가 0이면 계속 1이면 끝내기
	int enter;
	int judge=1;								//judge:문자열 비교
	char out[100]={"###\n"};					//끝낼 문자열
	getchar(); 									// 공백문자 삭제
	while(progress<20){
		char ans[100]={};						//사용자가 입력한 문자열 저장을 위한 변수,항상 초기화함
		system("clear");
		judge=1;								//항상 초기화함
		srand(time(NULL));
		random=rand()%100;
		for(i=0;i<100;i++){						//랜덤하게 추출된 단어의 길이구하기 시작
				if(word[random][i]==0){
						break;
				}
		}
		N=i;									//단어 길이 구하기 끝

		//시작
		printf(">> 영문 타자 연습 프로그램:짧은 글 연습<<\n");
		if(progress==0){						//progress가 0이면 나눌 수 없기 떄문,진행도,오타수,정확도 출력
			printf("진행도: %d%% 	오타수 : %d 	정확도: %.0f%%\n",progress*5,fault_num,(float)accurate*100);
		}
		else{
			printf("진행도: %d%% 	오타수 : %d 	정확도: %.0f%%\n",progress*5,fault_num,(float)accurate*100/progress);
		}

		for(i=0;i<N;i++){
			printf("%c",word[random][i]);		//화면에 무작위 단어 띄우기
		}
		printf("\n");
		for(i=0;i<100;i++){						//입력 받기시작
			ans[i]=getch();
			printf("%c",ans[i]);
			if(ans[i]==127){					//지우기시작
				printf("\b \b");
				i-=2;							//지우기 끝
			}
			if(ans[i]=='\n'){					//엔터 입력하면 다음 문장으로 넘어감
				break;
			}
		}										//입력 받기 끝
		length=i;								//입력받은 단어의 길이 구하기
		if(!strcmp(ans,out)){					//###입력하면 함수 끝내기
				main();
		}
		for(i=0;i<length-1;i++){				//문자열 비교
			if(word[random][i]!=ans[i]){
				judge=0;
				break;
				}
		}
		if(length!=N){
				judge=0;
		}										//문자열 비교 끝(같으면 judge=1 다르면 judge=0)
		if(judge==1){							//입력한 단어와 화면에 출력한 문자가 같으면(judge==1) 정확도 변수(accurate)를 하나 증가시키고  아니면(judge==0) 오타수(fault_num) 변수를 하나 증가시킨다.
			accurate++;							//정확도 증가
		}
		else{	
				fault_num++;					//오타수 증가
		}
		progress++;								//진행도 증가
	}
	system("clear");
	printf("진행도: %d%% 	오타수 : %d 	정확도: %.0f%%\n",progress*5,fault_num,(float)accurate*100/progress);
	printf("\n메뉴로 복귀하려면 enter를 누르세요");
	while(1){									//메뉴로 넘어가기 위해 enter를 입력받음
		enter=getch();
		if(enter=='\n'){
			main();
		}
	}
	return 0;									//끝나고 enter입력할때까지 대기하도록 만들어야함
}
