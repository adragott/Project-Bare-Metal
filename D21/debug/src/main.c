#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "debug.h"

char buffer[512] = {'\0'};
int main()
{
	int port;
	if((port = open(COM_PORT, O_RDWR|O_NOCTTY|O_NONBLOCK)) < 0)
	{
		printf("Error %d", port);
		return -1;
	}
	sleep(1);
	while(1)
	{

		ssize_t sizeBuff = read(port, buffer, 512);
		const char* temp = buffer;
		if(sizeBuff > 0)
		{
			while(*temp)
			{
				printf("%c", *temp++);
			}

			memset(buffer, '\0', sizeBuff);
		}
	}
}
