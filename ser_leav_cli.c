#include "serheard.h"

int ser_leav_cli(userdata rd_usr_data, int newsockfd)  //发送留言
{
	char s_usernum[MAXLEN];
	int fd;
	int len;
	char se_buf[2 * MAXBUF];

	bzero(s_usernum, sizeof(s_usernum));
	itoa(rd_usr_data.usernum, s_usernum);
	strcat(s_usernum, ".tmp");
	if ((fd = open(s_usernum, O_RDONLY)) < 0)  //打开用户留言文件
	{
		perror("open() .tmp failed:");
		return -1;
	}
	lseek(fd, 0, SEEK_SET);
	while (1)  //读取用户留言文件
	{
		bzero(se_buf, sizeof(se_buf));
		if ((len = read(fd, &se_buf, sizeof(se_buf))) <= 0)
		{
			perror("read() .tmp failed:");
			break;
		}
		if (send(newsockfd, &se_buf, len, 0) < 0)
		{
			perror("send() se_buf failed:");
			break;
		}
	}
	sleep(1);
	if (send(newsockfd, "over", 5, 0) < 0)
	{
		perror("send() over failed:");
	}
	close(open(s_usernum, O_TRUNC));  //清空留言文件
	close(fd);
}
