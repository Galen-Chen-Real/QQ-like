#include "cliheard.h"

int login_user(userdata *usr_data, int sockfd, enum ser_command ser_cmd)  //登录,成功:usernum; 帐号/密码错误:0; 失败:-1
{
	system("clear");
	//填写信息
	printf("登录...\n帐号:");
	scanf("%d", &((*usr_data).usernum));
	printf("密码:");
	//gets((*usr_data).pwd);
	scanf("%s", usr_data->pwd);
	//发送登录请求
	if (send_ser_cmd(ser_cmd, sockfd) < 0)
	{
		return -1;
	}
	//发送登录验证信息
	if (send(sockfd, usr_data, sizeof(*usr_data), 0) < 0)
	{
		perror("send() login_usr_data failed:");
		return -1;
	}
	//接收服务器返回信息
	if (recv(sockfd, usr_data, sizeof(*usr_data), 0) < 0)
	{
		perror("recv() login_usr_data failed:");
		return -1;
	}
	
	if (usr_data->minutes < 0)  //帐号/密码错误
	{
		return 0;
	}
	else
	{
		return usr_data->usernum;
	}
}
