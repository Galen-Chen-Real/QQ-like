#include "filetrans.h"

#define IP INADDR_ANY
#define MAXLEN 128
#define MAXDATA 1024
//#define PORT 2015
#define LIS_NUM 1
#define MAXPATH 128

void trans_file(char *pathname, int newsockfd)
{
	char path[MAXPATH];
	int fd;
	//FILE *scr;
	int len;
	int res;
	char data[MAXDATA];
	//int data[MAXDATA];
	struct stat buf;
	off_t size;
	double sum = 0.0, ratio = 0.0;

	strcpy(path, pathname);
	res = send(newsockfd, path, strlen(path), 0);  /*发送文件名*/
	if (res < 0)
	{
		error("send() failed");
	}

	res = recv(newsockfd, data, MAXDATA, 0);  /*接收验证信息*/
	if (res < 0)
	{
		error("recv() failed");
	}
	printf("发送文件名:%s 成功 \n", path);

	//open() path
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		error("open() failed");
	}

	//stat() path
	res = stat(path, &buf);
	if (res < 0)
	{
		error("stat() failed");
	}

	//7.send() result
	while ((len = read(fd, data, MAXDATA)) > 0)
	{
		//data[len] = '\0';
		//printf("len = %d \n", len);
		res = send(newsockfd, data, len, 0);  /*发送信息*/  
		if (res < 0)
		{
			error("send() failed");
		}
		sum += res;
		ratio = sum / buf.st_size;
		printf("sending : %7.2f%%\n", 100.0 * ratio);

		res = recv(newsockfd, data, MAXDATA, 0);  /*接收验证信息*/ 
		if (res < 0)
		{
			error("recv() failed");
		}
	}
	
	data[0] = '\0';
	send(newsockfd, data, 0, 0);  /*告知接受方已发送完毕*/
	printf("传输完毕!\n");
	lseek(fd, 0, SEEK_SET);
	//fseek(scr, 0, SEEK_SET);

	close(fd);

}

void receive_file(int sockfd, char *recvpath)
{
	int res;
	int fd;
	//FILE *des;
	char path[MAXPATH];
	char crt_path[MAXPATH];
	int len;
	char data[MAXDATA];
	//int data[MAXDATA];

	bzero(crt_path, sizeof(crt_path));
	strcpy(crt_path, recvpath);

	res = recv(sockfd, path, MAXPATH, 0);  /*接收文件名*/
	if (res < 0)
	{
		error("recv() failed");
	}
	path[res] = '\0';

	getname(path);  /*去除路径取出文件名*/

	strcpy(crt_path + strlen(crt_path), path);

	//open() path
	printf("creat file %s \n", crt_path);
	
	fd = open(crt_path, O_CREAT | O_WRONLY | O_TRUNC, 00777);  /*创建文件*/ 
	if (fd < 0)
	{
		error("open() failed");
	}

	bzero(data, MAXDATA);
	res = send(sockfd, data, 1, 0);  /*发送已接收到的验证信息*/
	if (res < 0)
	{
		error("send() failed");
	}

	//6.recv() result
	while ((len = recv(sockfd, data, MAXDATA, 0)) > 0)  /*接收信息*/
	{			
		//printf("%s", data);
		len = write(fd, data, len);  /*将信息写入文件*/
		if (len < 0)
		{
			error("write() failed");
		}

		bzero(data, MAXDATA);

		res = send(sockfd, data, 1, 0);  /*发送已接收到的验证信息*/
		if (res < 0)
		{
			error("send() failed");
		}
	}
	printf("文件接收成功,存储在:%s\n", crt_path);

	close(fd);
}

void getname(char *path)
{
	int i;
	int len = strlen(path);
	char name[128];

	strcpy(name, path);
	for (i = len; i > 0 && *(path + i) != '/'; i--)
	{
		;
	}
	if (i != 0)
	{
		i++;
	}
	strcpy(path, name + i);
}

void error(char *s)
{
	printf("error: %s \n", s);
	exit(EXIT_FAILURE);
}
