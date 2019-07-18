/*********************************************************************************
 *      Copyright:  (C) 2019 Guozhihao
 *                  All rights reserved.
 *
 *       Filename:  chatserver.c
 *    Description:  多人聊天服务器端主函数main()
 *                 
 *        Version:  1.0.0(07/17/2019)
 *         Author:  Guozhihao <810170156@qq.com>
 *      ChangeLog:  2, Release initial version on "07/19/2019 08:34:01 AM"
 *                 
 ********************************************************************************/
#include "chat.h"
#define TEST 1

/********************************************************************************
 *   Input Args:
 *  Output Args:None
 * Return Value:None
 ********************************************************************************/
int main (int argc, char **argv)
{
    /* 聊天服务器端监听的socket描述符 */
    int                     server_sock_fd;    
    /* 定义客户消息 */
    message                 client_message;
    ptr_list_client_node    head_node;

    struct sockaddr_in      server_addr;
    socklen_t               server_addr_len;

    /* 安装信号 */

    /* 配置服务器结构体 */
    memset(&server_addr,0,sizeof(server_addr));
    server_addr_len = sizeof(server_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    inet_aton("127.0.0.1",&server_addr.sin_addr);

    /* 检验并创建服务器套接字 */
    IF_CHECK((server_sock_fd = socket(AF_INET,SOCK_DGRAM,0))); 

    /* 检验和绑定配置服务器地址 */
    IF_CHECK(bind(server_sock_fd,(struct sockaddr *)&server_addr, server_addr_len));

    /* 产生第一个指向服务器的节点 */
    head_node  =  create_node(&server_addr); 

#if TEXT
    printf(stdout,"now to listening...\n");
#endif

    /* 开始监听 */
    while(START_RUN)
    {
#if TEXT
        printf(stdout,"now to waiting client...\n");
#endif
        /* 接受客户端的数据 */
        memset(&client_message,0,sizeof(message)); 
        IF_CHECK((recvfrom(server_sock_fd,(ptr_message)&client_message, sizeof(message), 0, (struct sockaddr*)&server_addr, &server_addr_len)));
        client_message.name[NAME_LEN-1] = '\0';
        client_message.text[TEXT_LEN-1] = '\0';
#if TEXT
        printf(stdout,"now to operating...\n");
#endif

        //fprintf(stdout, "client message [%s:%d] => [%c:%s:%s]\n",inet_ntoa(server_addr.sin_addr),ntohs(server_addr.sin_port), client_message.type, client_message.name, client_message.text);

        switch(client_message.type)
        {
            case '1':
                  login_client(head_node,server_sock_fd, &server_addr,&client_message);break;
            case '2':
                  broadcast_client_message(head_node,server_sock_fd, &server_addr, &client_message);break;
            case '3':
                  left_chatroom(head_node,server_sock_fd, &server_addr, &client_message);break;
            default:
                  //fprintf(stderr,"client message is error ![%s:%d] => [%c:%s:%s]\n", inet_ntoa(server_addr.sin_addr),ntohs(server_addr.sin_port),client_message.type,client_message.name,client_message.text);
                  left_chatroom( head_node,server_sock_fd, &server_addr,  &client_message);
                  break;
        }
    }
    close(server_sock_fd);
    
    
} /* ----- End of main() ----- */


