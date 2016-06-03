#include "serheard.h"

int ser_chat_friend(userdata rd_usr_data, int frd_usernum, int newsockfd)  //与指定好友聊天
{
	int fd;
	//int pip_fd;
	int wat_fd;
	char s_frd_usernum[MAXLEN];
	char wait_name[MAXLEN];

	userdata frd_data;

	ser_read_usrdat(frd_usernum, &frd_data);  //获取好友信息

	//发送好友信息
	if (send(newsockfd, &frd_data, sizeof(frd_data), 0) < 0)
	{
		perror("send() s_frd_usernum failed:");
		return -1;
	}

	switch (frd_data.flag)
	{
	case ONLINE:
		bzero(wait_name, sizeof(wait_name));
		itoa(frd_data.usernum, wait_name);
		strcat(wait_name, ".wat");
		if ((wat_fd = open(wait_name, O_WRONLY)) < 0)
		{
			perror("open() .wat failed:");
			break;
		}
		lseek(wat_fd, 0, SEEK_SET);
		if (write(wat_fd, &rd_usr_data, sizeof(rd_usr_data)) < 0)
		{
			perror("write() .wat failed:");
			break;
		}
		close(wat_fd);
		break;
	case OUTLINE:  //此处无break;
	case BUSY:
		ser_leav_ser(frd_data, rd_usr_data, newsockfd);
		break;
	default :
		printf("error: frd_data.flag = %d \n", frd_data.flag);
		break;
	
	}
}
