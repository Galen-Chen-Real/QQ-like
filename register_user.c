#include "cliheard.h"

int register_user(userdata *reg_data, int sockfd, enum ser_command ser_cmd)  //注册,成功:usernum; 失败:-1
{
	char username[MAXLEN];
	char userpwd1[MAXLEN];
	char userpwd2[MAXLEN];
	int usernum;

	system("clear");
	//填写昵称
	printf("注册...\n请输入昵称:");
	//gets(username);
	scanf("%s", username);
	//printf("ok1: username = %s \n", username);
	strcpy((*reg_data).username, username);
	//填写密码
	printf("请输入密码:");
	//gets(userpwd1);
	scanf("%s", userpwd1);
	printf("再次输入密码:");
	//gets(userpwd2);
	scanf("%s", userpwd2);
	if (!strcmp(userpwd1, userpwd2))
	{
		strcpy((*reg_data).pwd, userpwd1);
		printf("输入成功 \n");
	}
	else
	{
		printf("两次输入不相同,输入失败 \n");
		return -1;
	}
	//发送注册请求
	if (send_ser_cmd(ser_cmd, sockfd) < 0)
	{
		return -1;
	}
	//发送注册信息
	if (send(sockfd, reg_data, sizeof(*reg_data), 0) < 0)
	{
		perror("send() reg_data failed:");
		return -1;
	}
	//接收服务器分配的帐号[100-200]
	if (recv(sockfd, reg_data, sizeof(*reg_data), 0) < 0)
	{
		perror("recv() reg_data failed:");
		return -1;
	}
	printf("注册成功 \n");
	return reg_data->usernum;
}
