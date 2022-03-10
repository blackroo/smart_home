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



