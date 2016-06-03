#include "serheard.h"

int ser_wait_frd(userdata rd_usr_data, int newsockfd)  //等待好友聊天
{
	int wait_usernum;
	char wait_name[MAXLEN];
	int wat_fd;
	userdata wait_data;	

	//创建用户等待文件:./qq_sql/[usernum].dat
	bzero(wait_name, sizeof(wait_name));
	itoa(rd_usr_data.usernum, wait_name);
	strcat(wait_name, ".wat");
	if ((wat_fd = open(wait_name, O_CREAT | O_WRONLY | O_TRUNC, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH)) < 0)
	{
		perror("creat .wat failed:");
		return -1;
	}
	wait_data.usernum = 0;
	if (write(wat_fd, &wait_data, sizeof(wait_data)) < 0)
	{
		perror("write() .wat failed:");
		return -1;
	}
	close(wat_fd);
	if ((wat_fd = open(wait_name, O_RDONLY)) < 0)  //打开.wat文件
	{
		perror("open() .wat failed:");
		return -1;
	}
	while (1)
	{
		lseek(wat_fd, 0, SEEK_SET);
		if (read(wat_fd, &wait_data, sizeof(wait_data)) < 0)  //读取.wat文件
		{
			perror("read() .wat failed:");
		}
		if (wait_data.usernum > 0)
		{
			break;
		}
		sleep(1);
	}

	if (send(newsockfd, &wait_data, sizeof(wait_data), 0) < 0)
	{
		perror("send() wait_data failed:");
		return -1;
	}
}

