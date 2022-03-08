
#include "arduino_packet.h"
#include "compare.h"

unsigned int save_location=0;


void type_check(char message[],int clnt_sock)
{	
	if (message[1]==init)
	{
		init_response(message,clnt_sock);
	}


}

void init_response(char buffer[],int clnt_sock)
{
	char message[64] = {0x00,};
	int index =0;
	int i=0;
	int check_sum=0;

	message[index++]=socket_server;
	message[index++]=init;
	message[index++]=buffer[2];
	
	while(i<index){
		check_sum=check_sum^message[i];
		i+=1;     
	}

    message[index++]=check_sum;
	
	
	write(clnt_sock, message,index);
}


