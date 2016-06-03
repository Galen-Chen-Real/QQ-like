#include "cliheard.h"

void slct_friend(int sockfd, int *frd_num)  //打印好友列表并选择好友
{
	frdinfo frd_info;
	int frdnum[MAXFRD];
	int i = 0;
	int j;

	system("clear");
	printf("好友列表...\n");
	while (recv(sockfd, &frd_info, sizeof(frd_info), 0) > 0 && frd_info.frdnum > 0)
	{
		printf("帐号:%d\t昵称:%s\n", frd_info.frdnum, frd_info.frdname);
		frdnum[i++] = frd_info.frdnum;
	}
	printf("请选择好友进行聊天[帐号],负数则返回:");
	while (1)
	{
		scanf("%d", frd_num);
		for (j = 0; j < i; j++)
		{
			if (*frd_num == frdnum[j])
			{
				return;
			}
		}
		if (*frd_num > 0)
		{
			printf("帐号%d不在好友列表中,请重新输入:", *frd_num);
		}
		else
			return;
	}
}
