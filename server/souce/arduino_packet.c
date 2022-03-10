
#include "arduino_packet.h"
#include "compare.h"
#include <pthread.h>


unsigned int save_location=0;

int sock;

void *recv_ThreadRun()
{
	int str_len;
	char message[BUFSIZE]={0x00};

    
    while((str_len=read(sock, message, BUFSIZE)) !=0)
	{

		if(message[0]!=socket_client)
		{
			continue;
		}


		if(check_sum(message) == -1)
		{
			printf("checksum error\n");
			continue;
		}

		if(message[1]==senser_period)
		{
			sensor_recv(message);
			file_save("tcp_status", 1);

		}


		
		debugHexDump("recv_data", (unsigned char*)message, (int)strlen(message));
		
		memset(message,0,BUFSIZE);
	}

}
 
void *send_ThreadRun()
{
	int i=0;

    while(1)
    {





	
    	if(i>200)
    	{
    		 if(file_exist("tcp_status", 1)==-1)
			 	exit(0);
			 i=0;
    	}
    	i++;
		sleep(1);
    }
}




void type_check(char message[],int clnt_sock)
{	

	pthread_t recv_Thread, send_Thread;
    int threadErr;

	if (message[1]==init)
	{
		save_location=message[2];
		init_response(message,clnt_sock);
		sock=clnt_sock;
		if(threadErr = pthread_create(&recv_Thread,NULL,recv_ThreadRun,NULL))
	    {
	        // 에러시 에러 출력
	        printf("Thread Err = %d",threadErr);
	    }
	    
	    if(threadErr = pthread_create(&send_Thread,NULL,send_ThreadRun,NULL))
	    {
	        // 에러시 에러 출력
	        printf("Thread Err = %d",threadErr);
	    }
	    
	    while(1)
		{
			sleep(1);
		}
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


void sensor_recv(char buffer[])
{
	float dust = 0;
	float temperature = 0;
	float humidity = 0;
	char values[BUFSIZE] = {0x00,};
	char *ptr;
	char filename[128]={0x00,};

	sprintf(values,&buffer[3]);
	
	ptr = strtok(values, ","); 
	dust = atof(ptr);
	file_save("dust",dust);

	ptr = strtok(NULL, ","); 
	temperature = atof(ptr);
	file_save("temperature",temperature);

	ptr = strtok(NULL, ","); 
	humidity = atof(ptr);
	file_save("humidity",humidity);
	

	sensor_response(buffer);
}


void sensor_response(char buffer[])
{
	char message[64] = {0x00,};
	int index =0;
	int i=0;
	int check_sum=0;
	
	
	message[index++]=socket_server;
	message[index++]=senser_period;
	message[index++]=buffer[2];
	
	while(i<index){
		check_sum=check_sum^message[i];
		i+=1;     
	}

    message[index++]=check_sum;
	
	
	write(sock, message,index);
}


void file_save(char *name, float val)
{
	FILE *fp;
	time_t t = time(NULL);
	char filename[128]={0x00,};
	char now_time[64]={0x00,};
	struct tm tm = *localtime(&t);

	sprintf(filename,"%s/%d_%s",temp_location,save_location,name);


	fp = fopen(filename, "w");

	if(fp == NULL){
		printf("파일열기 실패\n");
		return;
	} 
	else {
		fprintf(fp,"%0.2f\n",val);
		fprintf(fp,"%d-%d-%d %d:%d:%d\n",
			tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday,
         	tm.tm_hour, tm.tm_min, tm.tm_sec);
	}

	fclose(fp);

	return;
}

int file_exist(char *name, int mode)
{
	FILE *fp;
	char filename[128]={0x00,};
	sprintf(filename,"%s/%d_%s",temp_location,save_location,name);
	
	fp = fopen(filename, "r");
	if(fp == NULL){
		return -1;
	}
	fclose(fp);
	if(mode==1)
		remove(filename);
	return 0;
}
