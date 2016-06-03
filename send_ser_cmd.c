#include "cliheard.h"

int send_ser_cmd(enum ser_command ser_cmd, int sockfd)  //发送服务命令
{
	if (send(sockfd, &ser_cmd, sizeof(ser_cmd), 0) < 0)
	{
		perror("send() sercmd failed:");
		return -1;
	}
	else
	{
		return 0;
	}
}
