#include "serheard.h"

int ser_slct_friend(int usernum, int newsockfd)  //发送好友列表
{
	int fd;
	char s_usernum[MAXLEN];
	frdinfo frd_info;
	//打开好友列表文件
	itoa(usernum, s_usernum);
	strcat(s_usernum, ".frd");
	if ((fd = open(s_usernum, O_RDONLY)) < 0)
	{
		perror("open() .frd failed");
	}
	//读取文件
	while (read(fd, &frd_info, sizeof(frd_info)) > 0)
	{
		//发送好友列表
		if (send(newsockfd, &frd_info, sizeof(frd_info), 0) < 0)
		{
			perror("send() frd_info failed:");
		}
	}
	close(fd);
	//告知客户端已经发送完毕
	frd_info.frdnum = -1;
	if (send(newsockfd, &frd_info, sizeof(frd_info), 0) < 0)
	{
		perror("send() rtn_frd_info failed:");
		return -1;
	}
	return 0;
}
