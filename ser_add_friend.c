#include "serheard.h"

int ser_add_friend(userdata *rd_usr_data, int newsockfd)  //添加好友
{
	int add_frdnum;
	int sum_fd, add_frd_fd, usr_frd_fd;
	enum add_command add_cmd;
	char s_add_frdnum[MAXLEN];
	char s_usernum[MAXLEN];
	frdinfo add_frd_info;
	userdata add_frd_data;

	while (1)
	{
		//接收添加的帐号(帐号为负则退出)
		if (recv(newsockfd, &add_frdnum, sizeof(add_frdnum), 0) < 0)
		{
			perror("recv() add_frdnum failed:");
			return;
		}
		if (add_frdnum < 0)
		{
			break;
		}
		//打开SUMUSER
		if ((sum_fd = open(SUMUSER, O_RDONLY)) < 0)
		{
			perror("open() sum.frd failed:");
			return;
		}
		//查找帐号是否存在
		while (read(sum_fd, &add_frd_info, sizeof(add_frd_info)) > 0)
		{
			//如果帐号存在
			if (add_frdnum == add_frd_info.frdnum)
			{
				add_cmd = EXIST;
				//打开帐号信息文件
				itoa(add_frdnum, s_add_frdnum);
				strcat(s_add_frdnum, ".dat");
				if ((add_frd_fd = open(s_add_frdnum, O_RDONLY)) < 0)
				{
					perror("open() s_add_frdnum failed:");
					break;
				}
				//读取帐号信息
				if (read(add_frd_fd, &add_frd_data, sizeof(add_frd_data)) < 0)
				{
					perror("read() s_add_frdnum failed:");
					break;
				}
				//打开用户好友列表文件
				itoa(rd_usr_data->usernum, s_usernum);
				strcat(s_usernum, ".frd");
				if ((usr_frd_fd = open(s_usernum, O_RDWR)) < 0)
				{
					perror("open() rd_usr_data.frd failed:");
				}
				lseek(usr_frd_fd, 0, SEEK_END);
				//将帐号添加到用户好友列表文件中
				if (write(usr_frd_fd, &add_frd_info, sizeof(add_frd_info)) < 0)
				{
					perror("write() add_frd_info failed:");
					break;
				}
				//将用户好友数量加1
				rd_usr_data->frdcount++;
				ser_update(*rd_usr_data);
				//发送EXIST命令
				if (send(newsockfd, &add_cmd, sizeof(add_cmd), 0) < 0)
				{
					perror("send() EXIST failed:");
					break;
				}
				//发送帐号信息
				if (send(newsockfd, &add_frd_data, sizeof(add_frd_data), 0) < 0)
				{
					perror("send() add_frd_data failed:");
					break;
				}
				close(sum_fd);
				close(add_frd_fd);
				close(usr_frd_fd);
				return;
			}
		}
		//帐号不存在
		add_cmd = UNEXIST;
		if (send(newsockfd, &add_cmd, sizeof(add_cmd), 0) < 0)
		{
			perror("send() UNEXIST failed:");
		}
		close(sum_fd);
		close(add_frd_fd);
		close(usr_frd_fd);
	}
	return;
}
