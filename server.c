#include "serheard.h"

int main(int argc, char *argv[])
{
	int sockfd, newsockfd;
	int res;
	int len;
	int usernum;
	int frd_usernum;
	int minutes;
	userdata rd_usr_data;
	struct sockaddr_in serv_addr, cli_addr;
	enum ser_command ser_cmd;
	struct in_addr ser_ip;

	system("clear");
	ser_ip.s_addr = INADDR_ANY;
	printf("服务器已经启动,IP地址为%s\n", inet_ntoa(ser_ip));
	if (mkdir(INFOPATH, 0777) < 0)  //初始化运行环境:创建工作目录
	{
		perror("if display 'File exists' is right:");
	}
	chdir(INFOPATH);  //切换到工作目录
	if (creat(SUMUSER, 0777) < 0)
	{
		perror("if display 'File exists' is right:");
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket() sockfd failed:");
		return -1;
	}

	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = PORT;
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	if ((bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) < 0)
	{
		perror("bind() serv_addr failed:");
		return -1;
	}

	if ((listen(sockfd, LISNUM)) < 0)
	{
		perror("listen() sockfd failed:");
		return -1;
	}

	while (1)
	{
		len = sizeof(cli_addr);
		if ((newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &len)) < 0)
		{
			perror("accept() cli_addr failed:");
			continue;
		}

		if (fork() == 0)
		{
			while (1)
			{
				if (recv(newsockfd, &ser_cmd, sizeof(ser_cmd), 0) < 0)
				{
					perror("recv() ser_cmd failed:");
					return;
				}
				switch (ser_cmd)
				{
				case REGISTER:  //注册命令
					if (ser_register(newsockfd) < 0)
					{
						usernum = -1;
						if (send(newsockfd, &usernum, sizeof(usernum), 0) < 0)  //发生错误,发送-1
						{
							perror("send() usernum failed:");
							return -1;
						}
					}
					break;
				case LOGIN:  //登录命令
					ser_login_user(&rd_usr_data, newsockfd);
					rd_usr_data.useraddr = cli_addr;  //记录登陆的IP
					ser_update(rd_usr_data);
					break;
				case FRIEND:  //找人聊天命令
					ser_slct_friend(rd_usr_data.usernum, newsockfd);
					if (recv(newsockfd, &frd_usernum, sizeof(frd_usernum), 0) < 0)
					{
						perror("recv() frd_usernum failed");
					}
					ser_chat_friend(rd_usr_data, frd_usernum, newsockfd);
					break;
				case WAIT:  //等人聊天命令

					ser_leav_cli(rd_usr_data, newsockfd);  //发送留言

					rd_usr_data.flag = ONLINE;
					ser_update(rd_usr_data);  //更新状态为在线

					ser_wait_frd(rd_usr_data, newsockfd);  //等待好友聊天

					rd_usr_data.flag = BUSY;
					ser_update(rd_usr_data);  //更新状态为忙碌
					break;
				case MODIFICATION:  //修改信息命令
					ser_mod_usrdat(&rd_usr_data, newsockfd);
					break;
				case ADDFRD:  //添加朋友命令
					ser_add_friend(&rd_usr_data, newsockfd);
					break;
				case GROUP:  //群聊命令
					break;
				case USERIP:  
					break;
				case USERSTATE:
					break;
				case LOGINOUT:  //退出登录命令
					if (recv(newsockfd, &minutes, sizeof(minutes), 0) < 0)
					{
						perror("recv() loginout failed:");
					}
					rd_usr_data.minutes += minutes;
					rd_usr_data.flag = OUTLINE;
					ser_update(rd_usr_data);
					break;
				case QUIT:  //退出系统命令
					printf("用户已退出 \n");
					return;
					break;
				default :
					printf("unknow command: ser_cmd = %d \n", ser_cmd);
					return -1;				
				}
			}
		}
	}
	return 0;
}
