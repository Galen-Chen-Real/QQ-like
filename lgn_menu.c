#include "cliheard.h"

void lgn_menu(userdata usr_data, int sockfd)  //登录后菜单
{
	void chat_wait_ser(userdata wait_data, userdata usr_data, int sockfd);  //和wait_data聊天
	int cmd;
	char re_buf[2 * MAXBUF];
	enum ser_command ser_cmd;
	userdata wait_data;
	char ip[MAXLEN];
	time_t sta_time, cur_time;
	int minutes;
	//pthread_t pthrd

	sta_time = time((time_t *)NULL);  //获取开始时间

	while (1)
	{
		system("clear");
		cur_time = time((time_t *)NULL);  //获取当前时间
		minutes = (cur_time - sta_time) / 60;

		printf("\n帐号:%d\t昵称:%s\t状态:%s\t在线时长:%d分\n", usr_data.usernum, usr_data.username, "BUSY", usr_data.minutes + minutes);
		printf("1.找人聊天\n2.等人聊天\n3.添加好友\n4.修改信息\n5.群聊\n6.退出登录\n请选择:");
		scanf("%d", &cmd);
		switch (cmd)
		{
		case 1:  //找人聊天
			//if (!pthread_create(&pthrd, NULL, lgn_pthrd_fun, (void *)serv_addr))
			//{
			//	perror("pthread_create() lgn_pthrd_fun failed:");
			//}
			ser_cmd = FRIEND;
			if (usr_data.frdcount > 0)
			{
				chat_friend(usr_data, sockfd, ser_cmd);
			}
			else
			{
				system("clear");
				printf("你还没有好友,请先添加好友\n");
				sleep(2);
			}
			break;
		case 2:  //等人聊天
			ser_cmd = WAIT;
			if (send_ser_cmd(ser_cmd, sockfd) < 0)
			{
				break;
			}
			system("clear");
			cur_time = time((time_t *)NULL);  //获取当前时间
			minutes = (cur_time - sta_time) / 60;

			printf("\n帐号:%d\t昵称:%s\t状态:%s\t在线时长:%d分\n", usr_data.usernum, usr_data.username, "ONLINE", usr_data.minutes + minutes);
			printf("接收留言...\n");
			while(1)
			{
				bzero(re_buf, sizeof(re_buf));
				if (recv(sockfd, &re_buf, sizeof(re_buf), 0) < 0)
				{
					perror("rece() re_buf failed:");
					break;
				}
				if (!strncasecmp(re_buf, "over", 4))
				{
					break;
				}
				printf("%s", re_buf);

			}
			printf("留言接收完毕\n");
			printf("等待一个连接到来，开始新的聊天...\n");
			if (recv(sockfd, &wait_data, sizeof(wait_data), 0) < 0)
			{
				perror("recv() wait_addr failed:");
				break;
			}
			printf("用户%d(%s)和你聊天...\n", wait_data.usernum, wait_data.username);
			sleep(1);  //防止udp_server未启动

			if (fork() == 0)
			{
				execl("./udp_server", "./udp_server", inet_ntoa(wait_data.useraddr.sin_addr), "3344", NULL);
			}
			else
			{
				wait(NULL);
			}
			//chat_wait_ser(wait_data, usr_data, sockfd);
			break;
		case 3:  //添加好友
			ser_cmd = ADDFRD;
			add_friend(&usr_data, sockfd, ser_cmd);
			break;
		case 4:  //修改信息
			ser_cmd = MODIFICATION;
			modification(usr_data, sockfd, ser_cmd);
			break;
		case 5:  //群聊
			ser_cmd = GROUP;
			/*
			if (usr_data.grpcount > 0)
			{
				chat_group(sockfd, ser_cmd);
			}
			else
			{
				printf("你还没有加入任何群,请先添加群\n");
			}
			*/
			chat_group(sockfd, ser_cmd);
			break;
		case 6:  //退出登录
			ser_cmd = LOGINOUT;
			send_ser_cmd(ser_cmd, sockfd);

			cur_time = time((time_t *)NULL);  //获取当前时间
			minutes = (cur_time - sta_time) / 60;
			if (send(sockfd, &minutes, sizeof(minutes), 0) < 0)
			{
				perror("send() loginout failed:");
			}
			return;
			break;
		default :
			printf("输入错误 \n");
			break;		
		}
	}
}
