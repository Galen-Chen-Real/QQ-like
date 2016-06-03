
#ifndef FILEHEARD
#define FILEHEARD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>

void trans_file(char *pathname, int newsockfd);
void error(char *);
void receive_file(int sockfd, char *path);
void getname(char *);

#endif
