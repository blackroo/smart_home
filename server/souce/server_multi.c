
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/socket.h>
#include"compare.h"

#define PORT 5000


void error_handling(char *message);
void z_handler(int sig);

int tcp_server_create()
{
	int serv_sock;
	struct sockaddr_in serv_addr;
	
	
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(PORT);

	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1)
		error_handling("bind() error");

	if(listen(serv_sock,5)==-1)
		error_handling("listen() error");

	return serv_sock;
}



int compare_data(int clnt_sock)
{
	int str_len;
	char message[BUFSIZE] = {0x00,};
	
	while((str_len=read(clnt_sock, message, BUFSIZE)) !=0)
	{

		if(message[0]!=0x01)
		{
			continue;
		}

		if(check_sum(message) == -1)
		{
			printf("checksum error\n");
			continue;
		}


		debugHexDump("recv_data", (unsigned char*)message, (int)strlen(message));
		
		if(message[1]==arduino_request || message[1]==arduino_response)
		{
			type_check(message,clnt_sock);
		}
		//init_packet(clnt_sock,message);
		//write(clnt_sock, message, str_len);
		//write(1,message, str_len);

		memset(message,0,BUFSIZE);
	}

	return 1;
}



int main(int argc, char **argv)
{
	int serv_sock;
	int clnt_sock;
	struct sockaddr_in clnt_addr;

	struct sigaction act;
	int addr_size, state;
	pid_t pid;
	

	//핸들러 설정
	act.sa_handler=z_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;

	state=sigaction(SIGCHLD, &act, 0);
	if(state != 0){
		puts("sigaction() error");
		exit(1);
	}
	//tcp 서버 연결
	serv_sock=tcp_server_create();
	

	while(1)
	{
		//client 접속 대기
		addr_size=sizeof(clnt_addr);
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr, &addr_size);

		//client 접속 실패시
		if(clnt_sock==-1)
			continue;
		//프로세스 생성 실패
		if((pid=fork())==-1)
		{
			close(clnt_sock);
			continue;
		}
		//client 접속 성공시 다시 대기상태로
		else if(pid>0)
		{
			puts("connect!");
			close(clnt_sock);
			continue;
		}

		//연결된 클라이언트에 대한 동작
		else
		{
			close(serv_sock);

			if(compare_data(clnt_sock)==1);
			{
				puts("disconnect!");
				close(clnt_sock);
				exit(0);	
			}
		}
	}
	return 0;

	
}

void z_handler(int sig)
{
	pid_t pid;
	int rtn;

	pid=waitpid(-1,&rtn,WNOHANG);
	if(pid!=-1)
	{
		printf("dead prossecc ID : %d \n",pid);
		printf("return data : %d \n\n",WEXITSTATUS(rtn));
	}
}

void error_handling(char * message)
{
	fputs(message,stderr);
	fputc('\n', stderr);
	exit(1);
}
