#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<termio.h>
int getch(){
	int ch;
	struct termios buf;
	struct termios save;
	tcgetattr(0,&save);
	buf = save;
	buf.c_lflag &= ~(ICANON| ECHO);
	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;
	tcsetattr(0,TCSAFLUSH,&buf);
	ch = getchar();
	tcsetattr(0,TCSAFLUSH,&save);
	return ch;
}
int main();
int alp(){             //자리연습
	char answer;      //입력받을 변수
	int progress=0, fault=0, accurate=0, answer_count=0; //진행도,오타수,정확도,입력한 개수를 위한 변수선언
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
int word(){           // 단어 연습
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

int f_progress(int size, int i, int k){    // 진행도 계산하는 함수
	return k*20 + (i+1)*20/size;
}
int f_accuracy(int i, int x){              // 정확도 계산하는 함수
	return (i+1-x)*100/(i+1);
}
int sstc(){   //짧은 글 연습
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
int main(void) {
	system("clear");
	char c;
	int i=1;
	while(i) {
		char c;
		printf("**********************************************\n");
		printf("*                                            *\n");
		printf("*  1. 자리연습                  2. 낱말연습  *\n");
		printf("*  3. 짧은글연습                4. 긴글연습  *\n");
		printf("*  5. 프로그램 종료                          *\n");
		printf("*                                            *\n");
		printf("**********************************************\n");
		printf("숫자를 입력하세요:");
		c=getch(); 
		system("clear");
		switch (c) {
			case '1' :
				alp();
				break; 
			case '2' :
				word();
				break;
			case '3' :
				sstc();
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
