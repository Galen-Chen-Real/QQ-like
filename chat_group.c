#include "cliheard.h"

void chat_group(int sockfd, enum ser_command ser_cmd)  //群聊
{
	send_ser_cmd(ser_cmd, sockfd);

	system("clear");
	printf("\n正在进入广播消息模式...\n");
	if (fork() == 0)
	{
		execl("./udp_grp", "./udp_grp", "255.255.255.255", "3344", NULL);
	}
	else
	{
		wait(NULL);
	}
}
