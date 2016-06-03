#include "serheard.h"

int ser_login_user(userdata *rd_usr_data, int newsockfd)  //接受用户登录
{
	userdata usr_data;
	char s_usernum[MAXLEN];
	int fd;
	//接收登陆验证信息
	if (recv(newsockfd, &usr_data, sizeof(usr_data), 0) < 0)
	{
		perror("recv usr_data failed:");
		return -1;
	}
	//打开对应用户信息文件
	itoa(usr_data.usernum, s_usernum);
	strcat(s_usernum, ".dat");
	if ((fd = open(s_usernum, O_RDONLY)) < 0)
	{
		usr_data.minutes = -1;  //该用户不存在
	}
	else
	{
		//读取服务器中该用户信息
		if (read(fd, rd_usr_data, sizeof(*rd_usr_data)) < 0)
		{
			perror("read() rd_usr_data failed:");
			usr_data.minutes = -1;
		}
		else
		{
			//与登陆验证信息相匹配
			if (strcmp(usr_data.pwd, rd_usr_data->pwd) != 0)
			{
				usr_data.minutes = -1;
			}
			else
			{
				//发送匹配结果
				if (send(newsockfd, rd_usr_data, sizeof(*rd_usr_data), 0) < 0)
				{
					perror("send() rd_usr_data failed:");
					close(fd);
					return -1;
				}
				else
				{
					//将用户状态标记为BUSY
					rd_usr_data->flag = BUSY;
					ser_update(*rd_usr_data);
					close(fd);
					return 0;
				}
			}
		}
	}
	if (send(newsockfd, &usr_data, sizeof(usr_data), 0) < 0)
	{
		perror("send() usr_data failed:");
	}
	close(fd);
	return -1;
}
