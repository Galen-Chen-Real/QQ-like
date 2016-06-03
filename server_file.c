
/**********************************************************
  将服务器的文件传送到到客户端:./server_file cli_ip port
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
	int sockfd, newsockfd;
	int res;
	int len;
	int PORT = atoi(argv[2]);
	char buf[MAXLEN];
	char pathname[MAXPATH];	
	struct sockaddr_in serv_addr, cli_addr;

	//1.socket()
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		error("socket() failed");
	}

	//2.struct sockaddr
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = PORT;
	serv_addr.sin_addr.s_addr = IP;
	bzero(serv_addr.sin_zero, sizeof(serv_addr.sin_zero));

	//3.bind()
	res = bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (res < 0)
	{
		error("bind() failed");
	}

	//4.listen()
	res = listen(sockfd, LIS_NUM);
	if (res < 0)
	{
		error("listen() failed");
	}

	//5.accept()
	printf("等待接收方建立连接...\n");
	len = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &len);
	if (newsockfd < 0)
	{
		error("accept() failed");
	}

	//6.recv() command
	printf("等待对方是否同意接收文件...\n");
	memset(buf, '\0', sizeof(buf));
	res = recv(newsockfd, buf, MAXLEN, 0);
	if (res < 0)
	{
		error("recv() failed");
	}
	if (!strncasecmp(buf, "y", 1))
	{
		printf("对方同意接收...\n", buf);

		printf("请输入要传输的文件:");
		gets(pathname);

		trans_file(pathname, newsockfd);
	}
	else
	{
		printf("对方不同意接收文件!\n");
	}

	close(sockfd);
	close(newsockfd);

	return 0;
}
