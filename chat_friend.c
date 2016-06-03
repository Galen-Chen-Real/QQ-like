#include "qqheard.h"
#include "cliheard.h"

void chat_friend(userdata usr_data, int sockfd, enum ser_command ser_cmd)  //单聊菜单
{
	int frd_num;
	enum usr_flag frd_cmd;
	userdata frd_data;

	if (send_ser_cmd(ser_cmd, sockfd) < 0)
	{
		return;
	}
	slct_friend(sockfd, &frd_num);  //打印好友列表并选择好友
	if (frd_num < 0)
	{
		return;
	}
	if (send(sockfd, &frd_num, sizeof(frd_num), 0) < 0)  //向好友发出聊天申请
	{
		perror("send() frd_num failed:");
		return;
	}
	if (recv(sockfd, &frd_data, sizeof(frd_data), 0) < 0)  //接收好友信息
	{
		perror("recv() frd_data failed:");
		return;
	}

	//printf("ok1:frd_num = %d\n", frd_num);

	switch (frd_data.flag)
	{
	case ONLINE:
		//chat_wait_cli(frd_data, usr_data, sockfd);
		system("clear");
		printf("将和%d(%s)聊天...\n", frd_data.usernum, frd_data.username);
		if (fork() == 0)
		{
			execl("./udp_server", "./udp_server", inet_ntoa(frd_data.useraddr.sin_addr), "3344", NULL);
		}
		else
		{
			wait(NULL);
		}
		break;
	case OUTLINE:  //此处无break;
	case BUSY:
		chat_leav_cli(sockfd, frd_data);
		break;
	default :
		printf("发生错误:flag = %d \n", frd_data.flag);
		break;
	}
}
