#ifndef SERHEARD
#define SERHEARD

#include "qqheard.h"

void itoa(int n, char s[]);//将整数转换为字符串
int ser_register(int newsockfd);  //接受用户注册,成功:0; 失败:-1
int ser_login_user(userdata *rd_usr_data, int newsockfd);  //接受用户登录
int ser_slct_friend(int usernum, int newsockfd);  //发送好友列表
int ser_chat_friend(userdata rd_usr_data, int frd_usernum, int newsockfd);  //与指定好友聊天
int ser_update(userdata usr_data);  //将更新后的用户信息写入文件中
int ser_read_usrdat(int usernum, userdata *data);  //读取用户信息
int ser_leav_ser(userdata frd_data, userdata rd_usr_data, int newsockfd);  //给朋友留言
int ser_leav_cli(userdata rd_usr_data, int newsockfd);  //发送留言
int ser_wait_frd(userdata rd_usr_data, int newsockfd);  //等待好友聊天
int ser_add_friend(userdata *rd_usr_data, int newsockfd);  //添加好友
int ser_mod_usrdat(userdata *rd_usr_data, int newsockfd);  //修改用户信息
#endif
