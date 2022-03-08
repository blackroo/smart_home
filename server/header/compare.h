
#include "arduino_packet.h"

#define BUFSIZE 512

int debugHexDump(const char * title, unsigned char * addr, int len);
void init_packet(int sock, char data[]);
int check_sum(char data[]);



enum socket_type
{
    socket_client = 0x01,
    socket_server = 0x02,
};

enum location
{
	init = 0x20,
    my_room=0x11,
};



enum function_type
{
    arduino_connect = 0x21,
    arduino_light_switch = 0x22,
    arduino_senser = 0x23,
};


