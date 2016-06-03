#include "cliheard.h"

void add_friend(userdata *usr_data, int sockfd, enum ser_command ser_cmd)  //添加好友
{
	int add_frdnum;
	enum add_command add_cmd;
	userdata add_frd_data;

	if (send_ser_cmd(ser_cmd, sockfd) < 0)
	{
		return;
	}

	system("clear");
	printf("添加好友...\n");

	while (1)
	{
		printf("请输入要添加的帐号[100~200](帐号为负则退出):");
		scanf("%d", &add_frdnum);
		if (add_frdnum < 0)
		{
			printf("帐号为负,将退出添加 \n");
			return;
		}
		if (send(sockfd, &add_frdnum, sizeof(add_frdnum), 0) < 0)
		{
			perror("send() add_frdnum failed:");
			return;
		}
		if (recv(sockfd, &add_cmd, sizeof(add_cmd), 0) < 0)
		{
			perror("recv() add_cmd failed");
			return;
		}
		switch(add_cmd)
		{
			case EXIST:
				if (recv(sockfd, &add_frd_data, sizeof(add_frd_data), 0) < 0)
				{
					perror("recv() add_frd_data failed");
					break;
				}
				printf("已经添加帐号:%d(%s)为好友 \n", add_frd_data.usernum, add_frd_data.username);
				usr_data->frdcount++;
				break;
			case UNEXIST:
				printf("帐号:%d不存在 \n", add_frdnum);
				break;
			default:
				printf("default: add_cmd = %d \n", add_frdnum);
				break;
		}
		sleep(2);
	}
}
