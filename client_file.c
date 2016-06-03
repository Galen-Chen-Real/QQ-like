
/**********************************************************
  接收从服务器器传过来的文件:./client_file ser_ip port
 **********************************************************/

#include "filetrans.h"

#define IP INADDR_ANY
#define MAXLEN 128
#define MAXDATA 1024
//#define PORT 2015
#define LIS_NUM 1
#define MAXPATH 128

int main(int argc, char *argv[])
{
	int sockfd;
	int res;
	int len;
	int PORT = atoi(argv[2]);
	char buf[MAXLEN];
	char path[MAXPATH] = "/mnt/receive/";
	struct sockaddr_in server_addr;

	if (mkdir(path, 0777) < 0)  //初始化运行环境:创建工作目录
	{
		perror("if display 'File exists' is right:");
	}

	//1.socket()
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		error("socket() failed");
	}

	//2.struct sockaddr
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = PORT;
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	bzero(server_addr.sin_zero, sizeof(server_addr.sin_zero));

	//3.connect()
	len = sizeof(server_addr);
	res = connect(sockfd, (struct sockaddr *)&server_addr, len);
	if (res < 0)
	{
		error("connect() failed");
	}
	
	//4.gets() command
	memset(buf, '\0', sizeof(buf));
	printf("是否要接收文件[y/n]:");
	//scanf("%s", buf);
	gets(buf);
	//strcpy(buf, "y");

	//5.send() command
	res = send(sockfd, buf, strlen(buf), 0);
	if (res < 0)
	{
		error("send() failed");
	}

	if (!strncasecmp(buf, "y", 1))
	{
		receive_file(sockfd, path);
	}
	else
	{
		printf("您取消了接收文件!\n");
	}

	close(sockfd);
	
	return 0;
}
