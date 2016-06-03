#include "serheard.h"

int ser_mod_usrdat(userdata *rd_usr_data, int newsockfd)  //修改用户信息
{
	if (recv(newsockfd, rd_usr_data, sizeof(userdata), 0) < 0)
	{
		perror("recv() mod_data failed:");
		return -1;
	}
	ser_update(*rd_usr_data);
}
