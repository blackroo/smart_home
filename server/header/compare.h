
#include "arduino_packet.h"

#define BUFSIZE 512

int debugHexDump(const char * title, unsigned char * addr, int len);
void init_packet(int sock, char data[]);
int check_sum(char data[]);



enum command
{
	init_command = 0x01,
};

enum type
{
	arduino_request = 0x21,
    arduino_response = 0x22,
};

enum function_type
{
    arduino_connect = 0x21,
    arduino_light_switch = 0x22,
    arduino_senser = 0x23,
};


