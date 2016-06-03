#include "cliheard.h"

void chat_leav_cli(int sockfd, userdata frd_data)  //发送留言
{
	char buf[MAXLEN];

	system("clear");
	printf("发送留言...\n");
	printf("帐号%d(%s)忙碌或者不在线,你可以给对方留言...\n直接输入信息回车即可发送[quit退出] \n", frd_data.usernum, frd_data.username);

	while (1)
	{
		bzero(buf, sizeof(buf));
		scanf("%s", buf);
		if (send(sockfd, buf, strlen(buf), 0) < 0)
		{
			perror("send() lea_buf failed:");
		}
		if (!strncasecmp(buf, "quit", 4))
		{
			break;
		}
	}
}
