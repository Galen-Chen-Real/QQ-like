#ifndef QQHEARD
#define QQHEARD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

#define MAXFRD 20
#define MAXLEN 32
#define MAXBUF 128
#define LISNUM 2
#define SERVIPLEN 32
#define PORT 7788
#define INFOPATH "./qq_sql/"
#define SUMUSER "sum.frd"

enum ser_command
{
	REGISTER = 1, LOGIN = 2, MODIFICATION = 3, FRIEND = 4, GROUP = 5, USERIP = 6, USERSTATE = 7, LOGINOUT = 8,ADDFRD = 9, ADDGRP = 10, WAIT = 11, QUIT = 12
};

enum add_command
{
	EXIST = 1, UNEXIST = 2
};

enum usr_flag
{
	ONLINE = 0, OUTLINE = 1, BUSY = 2
};

typedef struct userdata
{
	int usernum;
	enum usr_flag flag; 
	char username[MAXLEN]; 
	char pwd[MAXLEN]; 
	int minutes; 
	int frdcount; 
	int grpcount; 
	struct sockaddr_in useraddr;
}userdata;

typedef struct frdinfo
{
	int frdnum; 
	char frdname[MAXLEN];
}frdinfo;

#endif
