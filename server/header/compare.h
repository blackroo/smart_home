
#include "arduino_packet.h"

#define BUFSIZE 128

int debugHexDump(const char * title, unsigned char * addr, int len);
void init_packet(int sock, char data[]);
int check_sum(char data[]);



enum socket_type
{
    socket_client = 0x01,
    socket_server = 0x02,
};

enum function_type
{
	init = 0x20,
    senser_period = 0x21,
};



enum location
{
    my_room=0x11,
};


