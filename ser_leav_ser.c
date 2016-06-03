#include "serheard.h"

int ser_leav_ser(userdata frd_data, userdata rd_usr_data, int newsockfd)  //给朋友留言
{
	int fd;
	char s_frdnum[MAXLEN];
	char buf[MAXBUF];
	char wr_buf[2 * MAXBUF];
	int len;
	//打开留言文件
	itoa(frd_data.usernum, s_frdnum);
	strcat(s_frdnum, ".tmp");
	
	if ((fd = open(s_frdnum, O_WRONLY | O_APPEND)) < 0)
	{
		printf("open() .tmp failed:");
		return -1;
	}

	while (1)
	{
		//接收留言
		bzero(wr_buf, sizeof(wr_buf));
		strcpy(wr_buf, rd_usr_data.username);
		strcat(wr_buf, ":");
		bzero(buf, sizeof(buf));
		if ((len = recv(newsockfd, &buf, MAXBUF, 0)) < 0)
		{
			perror("recv() leav failed:");
		}

		//printf("ok1:wr_buf = %s", wr_buf);
		if (!strncasecmp(buf, "quit", 4))
		{
			break;
		}
		strcat(wr_buf, buf);
		strcat(wr_buf, "\n");

		//printf("ok2:wr_buf = %s", wr_buf);
		//将留言写入.tmp中
		if (write(fd, &wr_buf, strlen(wr_buf)) < 0)
		{
			perror("write() .tmp failed:");
		}
	}
	close(fd);
	return 0;
}
