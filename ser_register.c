#include "serheard.h"

int ser_register(int newsockfd)  //接受用户注册
{
	int usernum = (getpid() % 100) + 100;

	userdata reg_data;
	frdinfo reg_info;
	int dat_fd, frd_fd, grp_fd, tmp_fd, sum_fd;
	char pathname[MAXLEN];
	char name[MAXLEN];

	if (recv(newsockfd, &reg_data, sizeof(reg_data), 0) < 0)  //接收注册信息
	{
		perror("recv() reg_data failed:");
		return -1;
	}
	++usernum;  //帐号自动生成
	//填充其它默认信息
	reg_data.usernum = usernum;
	reg_data.flag = OUTLINE;
	reg_data.minutes = 0;
	reg_data.frdcount = 0;
	reg_data.grpcount = 0;
	//创建用户信息文件:./qq_sql/[usernum].dat
	itoa(reg_data.usernum, name);
	strcpy(pathname, name);
	strcat(pathname, ".dat");
	if ((dat_fd = open(pathname, O_CREAT | O_WRONLY | O_TRUNC, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH)) < 0)
	{
		perror("open() .dat failed:");
		return -1;
	}
	//将用户信息写入文件
	if (write(dat_fd, &reg_data, sizeof(reg_data)) < 0)
	{
		perror("write() reg_data failed:");
		return -1;
	}
	//创建用户好友列表文件:./qq_sql/[usernum].frd
	strcpy(pathname, name);
	strcat(pathname, ".frd");
	if ((frd_fd = open(pathname, O_CREAT | O_WRONLY | O_TRUNC, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH)) < 0)
	{
		perror("open() .frd failed:");
		return -1;
	}
	//创建用户群组列表文件:./qq_sql/[usernum].grp
	strcpy(pathname, name);
	strcat(pathname, ".grp");
	if ((grp_fd = open(pathname, O_CREAT | O_WRONLY | O_TRUNC, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH)) < 0)
	{
		perror("open() .grp failed:");
		return -1;
	}
	//创建用户留言文件:./qq_sql/[usernum].tmp
	strcpy(pathname, name);
	strcat(pathname, ".tmp");
	if ((tmp_fd = open(pathname, O_CREAT | O_WRONLY | O_TRUNC, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH)) < 0)
	{
		perror("open() .tmp failed:");
		return -1;
	}
	//将用户添加进SUMUSER中
	if ((sum_fd = open(SUMUSER, O_RDWR)) < 0)
	{
		perror("open() SUMUSER failed:");
		return -1;
	}
	reg_info.frdnum = reg_data.usernum;
	strcpy(reg_info.frdname, reg_data.username);
	lseek(sum_fd, 0, SEEK_END);
	if (write(sum_fd, &reg_info, sizeof(reg_info)) < 0)
	{
		perror("write() reg_info failed:");
		return -1;
	}
	//发送帐号
	if (send(newsockfd, &reg_data, sizeof(reg_data), 0) < 0)
	{
		perror("send() usernum failed:");
		return -1;
	}
	close(dat_fd);
	close(frd_fd);
	close(grp_fd);
	close(tmp_fd);
	close(sum_fd);
	return 0;
}
