#ifndef CLIHEARD
#define CLIHEARD

#include "qqheard.h"

int send_ser_cmd(enum ser_command ser_cmd, int sockfd);  //发送服务命令,成功:0; 失败:-1
int register_user(userdata *reg_data, int sockfd, enum ser_command ser_cmd);  //注册,成功:usernum; 失败:-1
int login_user(userdata *usr_data, int sockfd, enum ser_command ser_cmd);  //登录,成功:usernum; 帐号/密码错误:0; 失败:-1
void lgn_menu(userdata usr_data, int sockfd);  //登录后菜单
void slct_friend(int sockfd, int *frd_num);  //打印好友列表并选择好友
void add_friend(userdata *usr_data, int sockfd, enum ser_command ser_cmd);  //添加好友
void chat_friend(userdata usr_data, int sockfd, enum ser_command ser_cmd);  //单聊菜单
void chat_group(int sockfd, enum ser_command ser_cmd);  //群聊
void modification(userdata usr_data, int sockfd, enum ser_command ser_cmd);  //修改用户信息
void chat_leav_cli(int sockfd, userdata frd_data);  //发送留言
#endif
