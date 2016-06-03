#include "serheard.h"

int ser_read_usrdat(int usernum, userdata *data)  //读取用户信息
{
	char s_usernum[MAXLEN];
	int fd;

	//打开指定好友信息文件
	itoa(usernum, s_usernum);
	strcat(s_usernum, ".dat");
	if ((fd = open(s_usernum, O_RDONLY)) < 0)
	{
		perror("open() s_usernum failed:");
		return -1;
	}
	//读取好友信息
	if (read(fd, data, sizeof(userdata)) < 0)
	{
		perror("read() s_frd_usernum failed:");
		return -1;
	}

}
