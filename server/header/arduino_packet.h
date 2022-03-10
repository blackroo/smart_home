
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>


#define temp_location "../temp"


void type_check(char message[],int clnt_sock);
void init_response(char buffer[],int clnt_sock);
void sensor_recv(char buffer[]);
void sensor_response(char buffer[]);
void file_save(char *name, float val);
int file_exist(char *name, int mode);








