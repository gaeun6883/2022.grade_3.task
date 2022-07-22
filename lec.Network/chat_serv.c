#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define BUF_SIZE 100
#define MAX_CLNT 256

//소겟번호와 해당 소켓번호를 가지는 이름을 묶기 위한 구조체
typedef struct{
      char name[BUF_SIZE];
      int num;
}clnt;

void* handle_clnt(void* arg);
void send_msg_all(char* msg, int len);
void send_msg_one(int who, char* msg, int len);
void error_handling(char *message);

int clnt_cnt=0, s=0;//s는 clnt 구조체 동적할당에 할당된 개수를 뜻한다.
int clnt_socks[MAX_CLNT];
pthread_mutex_t mutx;
clnt* c_list[MAX_CLNT];

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	int clnt_adr_sz;
	pthread_t t_id;
	
	if(argc!=2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	
	pthread_mutex_init(&mutx, NULL);//mutex 생성
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);  //tcp 통신을 할 것이다.
	
    //주소 설정
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr))==-1)//주소를 묶는다.(bind 함수)
		error_handling("bind() error");
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");
	
	while(1)
	{
	        clnt_adr_sz=sizeof(clnt_adr);
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);//clnt_sock 소켓을 통해 소켓 통신을 한다.
		
		pthread_mutex_lock(&mutx);//임계영역 보호
		clnt_socks[clnt_cnt++]=clnt_sock;//접속된 소켓 관리 배열에 넣는다.
		pthread_mutex_unlock(&mutx);
		
		pthread_create(&t_id, NULL, handle_clnt, (void*)&clnt_sock);//handle_clnt 함수를 수행하는 스레드 생성
		pthread_detach(t_id);
		printf("Connected client IP: %s \n", inet_ntoa(clnt_adr.sin_addr));
	}

	close(serv_sock);//socket을 닫는다.
	return 0;
}

void* handle_clnt(void* arg){
        int clnt_sock=*((int*)arg);
        int str_len=0, i;
        char msg[BUF_SIZE]="\0";
        
        while((str_len=read(clnt_sock, msg, sizeof(msg)))!=0){//메시지를 읽는다.
                   char from[BUF_SIZE]="\0", who[BUF_SIZE]="\0";//전송한 쪽의 이름과 보낼 쪽의 이름을 저장
                   char str[BUF_SIZE]="\0";//보낼 메시지를 저장
                   int who_n=-1, length=0;//who_n은 보낼 쪽의 소켓 번호, length는 보낼 메시지의 길이
                   int idx=0;
                   for(int i=0; i<strlen(msg);i++){//메시지 길이가 다 될때까지
                          idx++;
                          if(msg[i]==' ') break;//메시지에 빈칸이 있으면 끝
                          from[i]=msg[i];//from은 맨 앞 단어이다.
                   }
                   printf("\nfrom: %s\n", from);//from 출력
                   clnt* c=(clnt*)malloc(sizeof(clnt));//구조체 할당
                   memcpy(c->name,&from,strlen(from));//할당된 구조체에 이름(from)넣기
                   c->num=clnt_sock;//번호는 clnt_sock
                   
                   int flag=1;
                   for(int i=0; i<s; i++)
                        if(strcmp(c_list[i]->name,from)==0)//만약 구조체 배열에 이 이름이 이미 있다면 넘어가기
                                flag=0;
                   if(flag==1){//없다면 넣기
                        c_list[s]= c;
                        s++;
                   }
                   
                   //c_list의 상태를 보기 위해 넣은 출력문
                   /*printf("c_list size: %d\n", s);
                   for(int i=0; i<s; i++)
                         printf("c_list[%d] : %s - %d\n",i, c_list[i]->name, c_list[i]->num);*/
                   
                   //보낼 사람 who 찾기
                   idx++;
                   for(int i=0; idx<strlen(msg);i++){
                       if(msg[idx]==' ') break;//빈칸이 생길 때까지
                       who[i]=msg[idx++];//받을 사람은 두번째 단어
                   }
                   printf("to: %s\n", who);
                   for(int i=0; i<s; i++){//c_list 탐색
                       if(strcmp(c_list[i]->name,who)==0)//받을 사람 이름이 있다면
                              who_n=c_list[i]->num;//who_n은 그 사람의 소켓 숫자, 없다면 -1 
                   }
                   //printf("who_n: %d\n", who_n);
                   
                   idx++;
                   str[0]='\0';
                   for(int i=0; idx<strlen(msg); i++)//메시지의 끝까지 보낼 문자
                       str[i]=msg[idx++];
                   printf("send msg: %s\n", str);
                   length=strlen(str);//length는 보낼 문자의 길이
                       
                   if(strcmp(who,"all")==0) send_msg_all(str, length);//보낼 사람이 all이라면 모두에게 전송
                   else {/
                      if (who_n==-1){//보낼 사람이 없다면
                               char error_msg[BUF_SIZE]="no exist\n";//오류문자 전송
                               send_msg_one(clnt_sock, error_msg, strlen(error_msg));
                       }
                      else send_msg_one(who_n, str, length);//보낼 사람이 특정된다면 그 사람에게 전송
                   }
                   memset(msg, 0, BUF_SIZE);//메시지 버퍼 비우기
                   memset(str,0,BUF_SIZE);//str 버퍼 비우기
                   
         }
        
        //통신을 끝내고 나간 사람은 배열에서 빼내기
        pthread_mutex_lock(&mutx);
        for(i=0; i<clnt_cnt; i++){
                 if(clnt_sock==clnt_socks[i]){
                         while(i<clnt_cnt-1){
                                clnt_socks[i]=clnt_socks[i+1];
                                i++;
                         }
                         break;
                   }
        }
        clnt_cnt--;
        pthread_mutex_unlock(&mutx);
        close(clnt_sock);
        return NULL;
 }
 
//모두에게 메시지 전송
void send_msg_all(char* msg, int len){
        pthread_mutex_lock(&mutx);
        for(int i=0; i<clnt_cnt; i++){
             //printf("send: %d - %s\n", clnt_socks[i], msg);
             write(clnt_socks[i], msg, len);
        }
        pthread_mutex_unlock(&mutx);
}

//한사람에게만 메시지 전송
void send_msg_one(int who, char* msg, int len){
       pthread_mutex_lock(&mutx);
       //printf("send: %d - %s\n", who, msg);
       write(who, msg, len);
       pthread_mutex_unlock(&mutx);
}

//오류가 일어났을 때
void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
