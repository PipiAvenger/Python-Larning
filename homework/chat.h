/********************************************************************************
 *      Copyright:  (C) 2019 Guozhihao
 *                  All rights reserved.
 *
 *       Filename:  chat.h
 *    Description:  服务器头文件
 *
 *        Version:  1.0.0(07/17/2019)
 *         Author:  Guozhihao <810170156@qq.com>
 *      ChangeLog:  1, Release initial version on "07/18/2019 09:38:02 AM"
 *                 
 ********************************************************************************/
#include <stdio.h>
#include <signal.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define         NAME_LEN (64)
#define         TEXT_LEN (512)
#define         START_RUN  (1)

#define         CERR(fmt, ...)\
    fprintf(stderr,"[%s:%s:%d][error: %d:%s]" fmt "\r\n",\
            __FILE__, __func__, __LINE__,errno,strerror(errno), ##__VA_ARGS__)

#define         CERR_EXIT(fmt,...) \
    CERR(fmt,##__VA_ARGS__),exit(EXIT_FAILURE)

#define         IF_CHECK(code) \
    if((code) < 0) \
        CERR_EXIT(#code)

typedef struct _message
{
    char type;
    char name[NAME_LEN];
    char text[TEXT_LEN];
}message,*ptr_message;

typedef struct _list_client_node
{
    struct                      sockaddr_in addr;
    struct _list_client_node *  next;
}*ptr_list_client_node;

extern void insert_client_node(ptr_list_client_node head, struct sockaddr_in * temp_addr);
extern void login_client (ptr_list_client_node head, int server_sockfd, struct sockaddr_in *temp_addr,ptr_message c_message);
extern void broadcast_client_message (ptr_list_client_node head,int server_sockfd,struct sockaddr_in *temp_addr, ptr_message c_message);
void left_chatroom (ptr_list_client_node head,int server_sockfd, struct sockaddr_in * temp_addr,ptr_message c_message );
