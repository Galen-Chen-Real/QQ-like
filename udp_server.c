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
	int sig_fd;
	char sig_c;

	if (creat("./udp_sig_ser", 0777) < 0)
	{
		perror("creat() sig failed:");
		return -1;
	}
	if ((sig_fd = open("./udp_sig_ser", O_RDWR)) < 0)
	{
		perror("open() sig failed:");
		return -1;
	}
	lseek(sig_fd, 0, SEEK_SET);
	if (write(sig_fd, "y", 1) != 1)
	{
		perror("write() sig y failed:");
		return -1;
	}

	//1.创建套接字
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0)
	{
	    perror("Socket:");
		exit(-1);
	}
	else
	{
	    printf("聊天服务端(套接字%d)创建成功...\n直接输入消息回车键发送,输入\"transfile\"传输文件,输入\"quit\"结束...\n", sockfd);
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

	len = sizeof(clientaddr);
	
	//4.发送或者接收信息
	if (fork() == 0)
	{
		while(1)
		{
			bzero(recv_val, sizeof(recv_val));
			res = recvfrom(sockfd, &recv_val, sizeof(recv_val), 0, (struct sockaddr *)&clientaddr, (socklen_t *)&len);
			if(res > 0)
			{
			    printf("接收到的消息为: %s\n", recv_val);
				if (!strncmp(recv_val, "quit", 4))
				{
					printf("对方请求结束聊天!\n如果没有自动结束请手动输入\"quit\"结束聊天...\n");
					sendto(sockfd, &recv_val, strlen(recv_val), 0, (struct sockaddr *)&clientaddr, sizeof(clientaddr));
					return 0;
				}

				if (!strncmp(recv_val, "transfile", 9))
				{
					printf("对方请求传输文件...\n");

					lseek(sig_fd, 0, SEEK_SET);
					if (write(sig_fd, "n", 1) != 1)
					{
						perror("write() sig n fialed:");
					}
					
					if (fork() == 0)
					{
						execl("./client_file", "./client_file", argv[1], "2015", NULL);
					}
					else
					{
						wait(NULL);

						lseek(sig_fd, 0, SEEK_SET);
						if (write(sig_fd, "y", 1) != 1)
						{
							perror("write() sig ok failed:");
						}
					}
					
					//execl("./client_file", "./client_file", argv[1], "2015", NULL);
				}
			}
		}
	}
	else
	{
		while(1)
		{
			lseek(sig_fd, 0, SEEK_SET);
			if (read(sig_fd, &sig_c, 1) != 1)
			{
				perror("read() sig c failed:");
			}
			if (sig_c != 'y')
			{
				continue;
			}

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

			if (!strncmp(sedv_val, "transfile", 9))
			{
				printf("您请求请求传输文件...\n");
				
				if (fork() == 0)
				{
					execl("./server_file", "./server_file", argv[1], "2015", NULL);
				}
				else
				{
					wait(NULL);
				}
				
				//execl("./server_file", "./server_file", argv[1], "2015", NULL);
			}
		}

		wait(NULL);
	}

	//5.关闭
	close(sockfd);
	
	return 0;
}

