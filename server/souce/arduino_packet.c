
#include "arduino_packet.h"
#include "compare.h"




void type_check(char message[],int clnt_sock)
{
	char filename[64]={0x00,};
	char Command[64]={0x00,};
	int location_num=0;
	FILE *file;
	int time=160;
	
	if(message[1]==arduino_request)
	{
		if(message[2]==arduino_connect)
		{
			location_num = message[3];
			init_response(clnt_sock);
		}
	}

	if(location_num!=0)
	{
		while(1)
		{
			sprintf(filename,"%s/%d_dustsensor",temp_location,location_num);
			
			if (file = fopen(filename, "r")) 
		    {
		        fclose(file);
				sprintf(Command,"sudo rm %s",filename);
				system(Command);
				dust_request(clnt_sock);
				time=0;
				sleep(1);
		    }
			else if(time>=180)
			{
				dust_request(clnt_sock);
				time=0;
			}
		    else
		    {
		    	time++;
				sleep(1);
		    }
		}
	}
}

void init_response(int clnt_sock)
{
	char * message = "connect";
	write(clnt_sock, message, strlen(message));
}

void dust_request(int clnt_sock)
{
	char filename[64]={0x00,};
	char command[64]={0x00,};
	char buffer[64]={0x00,};
	char * message = "Dust sensor";

	FILE *fp;


	time_t t = time(NULL);
	struct tm tm = *localtime(&t);



	
	write(clnt_sock, message, strlen(message));

	sprintf(filename,"%s/dust_request",temp_location);
	sprintf(command,"sudo touch %s",filename);
	system(command);
	
	
	while(read(clnt_sock, buffer, 64)<=0);

	memset(command,0,64);
	sprintf(command,"sudo rm %s",filename);
	system(command);

	memset(command,0,64);
	sprintf(command,"%s/dust_value",temp_location);

	if((fp = fopen(command, "w"))!=NULL)
	{
		memset(command,0,64);
		sprintf(command,"time[%d-%d-%d %d:%d:%d]\n",tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday,
         tm.tm_hour, tm.tm_min, tm.tm_sec);
		fputs(command, fp);
		
		memset(command,0,64);
		sprintf(command,"dust[%.2f]\n",atof(buffer));
		fputs(command, fp);
		
		fclose(fp);
	}

	printf("time[%d-%d-%d %d:%d:%d]\n",
         tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday,
         tm.tm_hour, tm.tm_min, tm.tm_sec);

	printf("dust[%.2f]\n", atof(buffer));
	

}

