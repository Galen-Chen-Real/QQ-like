#include "cliheard.h"

void modification(userdata usr_data, int sockfd, enum ser_command ser_cmd)  //修改用户信息
{
	int modi_cmd;
	char username[MAXLEN];
	char pwd[MAXLEN];
	char modipwd1[MAXLEN];
	char modipwd2[MAXLEN];
	int i = 3;

	system("clear");
	printf("修改信息前需要先验证密码...\n");

	while (1)
	{
		if (i < 0)
		{
			return;
		}
		printf("请输入密码(剩%d次):", i);
		scanf("%s", pwd);
		if (!strcmp(pwd, usr_data.pwd))
		{
			break;
		}
		else
		{
			i--;
			printf("密码错误 \n");
		}
	}
	while (1)
	{
		system("clear");
		printf("修改信息...\n");
		printf("1.修改昵称\n2.修改密码\n3.退出修改(上传)\n请选择:");
		scanf("%d", &modi_cmd);
		switch (modi_cmd)
		{
		case 1:
			printf("旧用户名:%s\n新用户名:", usr_data.username);
			scanf("%s", username);
			strcpy(usr_data.username, username);
			printf("修改成功 \n");
			break;
		case 2:
			printf("旧密码:%s\n新密码:", usr_data.pwd);
			scanf("%s", modipwd1);
			printf("再次输入:");
			scanf("%s", modipwd2);
			if (!strcmp(modipwd1, modipwd2))
			{
				strcpy(usr_data.pwd, modipwd1);
				printf("修改成功 \n");
				break;
			}
			printf("两次输入不相同,修改失败 \n");
			break;
		case 3:
			if (send_ser_cmd(ser_cmd, sockfd) < 0)
			{
				break;
			}
			if (send(sockfd, &usr_data, sizeof(usr_data), 0) < 0)
			{
				perror("send() modi_usr_data failed");
				break;
			}
			printf("修改成功!\n");
			return;
			break;
		default :
			printf("输入错误 \n");
			break;
		}
		sleep(2);
	}
}
