//UDP服务器:运行./udp_server ip port
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>

//#define PORTNUM 3344
#define MAXRECV 1280

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("argv != 3\n");
		return 0;
	}

	int sockfd;
	struct sockaddr_in myaddr, clientaddr;
	int res;
	int len;
	int PORTNUM = atoi(argv[2]);
	char recv_val[MAXRECV];
	char sedv_val[MAXRECV];

	//1.创建套接字
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0)
	{
	    perror("Socket:");
		exit(-1);
	}
	else
	{
	    printf("聊天服务端(套接字%d)创建成功...\n直接输入消息回车键发送,输入\"quit\"结束...\n", sockfd);
	}

	//2.填充服务器信息
	bzero(&myaddr, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = PORTNUM;
	myaddr.sin_addr.s_addr = INADDR_ANY;

	//3.绑定
	res = bind(sockfd, (struct sockaddr *)&myaddr, sizeof(myaddr));
	if(res < 0)
	{
	    perror("Bind:");
		exit(-1);

	}

	//填充对方的地址信息
	bzero(&clientaddr, sizeof(clientaddr));
	clientaddr.sin_family = AF_INET;
	clientaddr.sin_port = PORTNUM;
	clientaddr.sin_addr.s_addr = inet_addr(argv[1]);

	int so_broadcast = 1;
	setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&so_broadcast,sizeof(so_broadcast));

	len = sizeof(clientaddr);
	
	while(1)
	{
		bzero(sedv_val, sizeof(sedv_val));
		//scanf("%s", sedv_val);  //冲突所在
		gets(sedv_val);
		printf("发送的消息为：%s\n", sedv_val);
		res = sendto(sockfd, &sedv_val, strlen(sedv_val), 0, (struct sockaddr *)&clientaddr, sizeof(clientaddr));
		if (!strncmp(sedv_val, "quit", 4))
		{
			printf("您请求结束聊天!\n");
			break;
		}
	}

	//5.关闭
	close(sockfd);
	
	return 0;
}

