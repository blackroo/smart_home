
#include "arduino_packet.h"
#include "compare.h"




void type_check(char message[],int clnt_sock)
{
	char filename[64]={0x00,};
	char Command[64]={0x00,};
	int location_num=0;
	FILE *file;
	
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
			sprintf(filename,"%s/%d_light_on",temp_location,location_num);
			
			if (file = fopen(filename, "r")) 
		    {
		        fclose(file);
		        printf("file exists\n");
				sprintf(Command,"sudo rm %s",filename);
				system(Command);
				switch_on(clnt_sock);
				sleep(1);
		    }
		    else
		    {
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

void switch_on(int clnt_sock)
{
	char * message = "switch on";
	write(clnt_sock, message, strlen(message));
}

