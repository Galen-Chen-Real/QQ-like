#include "serheard.h"

int ser_update(userdata usr_data)  //将更新后的用户信息写入文件中
{
	int fd;
	char s_usernum[MAXLEN];

	itoa(usr_data.usernum, s_usernum);
	strcat(s_usernum, ".dat");
	if ((fd = open(s_usernum, O_WRONLY)) < 0)
	{
		perror("open() s_usernum failed:");
		return -1;
	}
	if (write(fd, &usr_data, sizeof(usr_data)) < 0)
	{
		perror("write() usr_data failed:");
		close(fd);
		return -1;
	}
	close(fd);
	return 0;
}
