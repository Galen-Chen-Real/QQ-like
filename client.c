#include "cliheard.h"

int main(int argc, char *argv[])
{
	int cmd;
	int sockfd;
	int res;
	char SERVIP[SERVIPLEN];
	userdata reg_data;
	userdata usr_data;
	enum ser_command ser_cmd;
	struct sockaddr_in serv_addr;

	system("clear");
	printf("请填写服务器IP：");
	scanf("%s", SERVIP);

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket() sockfd failed:");
		return -1;
	}

	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = PORT;
	serv_addr.sin_addr.s_addr = inet_addr(SERVIP);

	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("connect() serv_addr failed:");
		return -1;
	}

	while (1)
	{
		system("clear");
		printf("\n欢迎使用本聊天系统\n");
		printf("1.注册\n2.登录\n3.退出\n请选择:");
		scanf("%d", &cmd);
		switch (cmd)
		{
		case 1:
			ser_cmd = REGISTER;
			if (register_user(&reg_data, sockfd, ser_cmd) < 0) //进行注册
			{
				printf("注册失败\n");
			}
			else
			{
				printf("\n请牢记你的帐号信息\n");
				printf("帐号:%d\t昵称:%s\t密码:%s\n", reg_data.usernum, reg_data.username, reg_data.pwd);
				sleep(3);
			}
			break;
		case 2:
			ser_cmd = LOGIN;
			if ((res = login_user(&usr_data, sockfd, ser_cmd)) < 0)
			{
				printf("登录失败\n");
				break;
			}
			else if (res == 0)
			{
				printf("帐号/密码错误\n");
				break;
			}
			else
			{
				printf("登录成功\n");
				lgn_menu(usr_data, sockfd);
			}
			break;
		case 3:
			ser_cmd = QUIT;
			send_ser_cmd(ser_cmd, sockfd);
			return 0;
			break;
		default :
			printf("输入错误\n");
			break;		
		}
	}	
	return 0;
}
