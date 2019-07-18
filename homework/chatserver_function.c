/*********************************************************************************
 *      Copyright:  (C) 2019 Guozhihao
 *                  All rights reserved.
 *
 *       Filename:  chatserver_function.c
 *    Description:  此文件包含了所有聊天服务器的函数 
 *                 
 *        Version:  1.0.0(07/17/2019)
 *         Author:  Guozhihao <810170156@qq.com>
 *      ChangeLog:  1, Release initial version on "07/17/2019 01:48:47 PM"
 *                 
 ********************************************************************************/
#include "chat.h"
/**************************************************************************************
 *  Description:创建新节点
 *   Input Args:(sockaddr_in *) temp_addr
 *  Output Args:None
 * Return Value:(client_node) node
 *************************************************************************************/
ptr_list_client_node create_node (struct sockaddr_in *temp_addr)
{
    ptr_list_client_node  node;
    
    node = (ptr_list_client_node) malloc(sizeof(ptr_list_client_node));
    if( NULL == node)
            CERR_EXIT("malloc sizeof struct ptr_list_client_node error!");

    node->addr = *temp_addr;
    node->next = NULL;

    return node; 
} /* ----- End of create_node()  ----- */


/**************************************************************************************
 *  Description:使用头插法创建客户端的链表
 *   Input Args:(ptr_list_client_node) head（头结点）,
 *   (struct sockaddr_in *)temp_addr（新节点的地址） 
 *  Output Args:None
 * Return Value:None
 *************************************************************************************/
void insert_client_node(ptr_list_client_node head, struct sockaddr_in * temp_addr)
{
    ptr_list_client_node node = create_node(temp_addr);
    node->next = head->next;
    head->next = node;
}
/**************************************************************************************
 *  Description:处理客户端登入信息并将信息转发给所有用户
 *   Input Args:
 *   客户端链表的头结点(struct _list_client_node *) head，
 *   服务器的套接字 server_sockfd,
 *   存放客户端地址结构体的指针(struct sockaddr_in*) temp_addr,
 *   存放收到客户端发送信息的指针(struct list_client_node *) c_message
 *  Output Args:
 * Return Value:
 *************************************************************************************/
void login_client (ptr_list_client_node head, int server_sockfd, struct sockaddr_in *temp_addr,ptr_message c_message)
{
    /* 插入新客户端 */ 
    insert_client_node(head,temp_addr);
    /* 初始head指向服务器，下一个才是客户端 */
    head = head->next;
    
    /* 包括发送者的客户端也会受到自己的登录信息 */
    while(NULL != head)
    {
        IF_CHECK(sendto(server_sockfd,c_message,sizeof(*c_message),0,(struct sockaddr *)&head->addr,sizeof(struct sockaddr_in))); 
        head = head -> next;
    }

} /* ----- End of login_client()  ----- */


/**************************************************************************************
 *  Description:广播发送信息到客户端成员链表当中去
 *   Input Args:
 *   客户端链表的头结点(struct _list_client_node *) head，
 *   服务器的套接字 server_sockfd,
 *   存放客户端地址结构体的指针(struct sockaddr_in*) temp_addr,
 *   存放收到客户端发送信息的指针(struct list_client_node *) c_message
 *  Output Args:None
 * Return Value:None
 *************************************************************************************/
void broadcast_client_message (ptr_list_client_node head,int server_sockfd,struct sockaddr_in * temp_addr, ptr_message c_message)
{
    int         flag = 0; //1表示找到了

    while(NULL != head->next)
    {
        head = head->next;
        if((flag) || !(flag = memcmp(temp_addr,&head->addr,sizeof(struct sockaddr_in))))
            IF_CHECK(sendto(server_sockfd,c_message,sizeof(*c_message), 0, (struct sockaddr *)&head->addr,sizeof(struct sockaddr_in)));
    }

} /* ----- End of broadcast_client_message()  ----- */

/**************************************************************************************
 *  Description:用户退出房间操作
 *   Input Args:
 *   客户端链表的头结点(struct _list_client_node *) head，
 *   服务器的套接字 server_sockfd,
 *   存放客户端地址结构体的指针(struct sockaddr_in*) temp_addr,
 *   存放收到客户端发送信息的指针(struct list_client_node *) c_message
 *  Output Args:None
 * Return Value:None
 *************************************************************************************/
void left_chatroom (ptr_list_client_node head,int server_sockfd, struct sockaddr_in * temp_addr,ptr_message c_message )
{
    int             flag = 0;//1表示找到
    while(NULL != head->next)
    {
        if((flag) || !(flag = memcmp(temp_addr,&head->next->addr,sizeof(struct sockaddr_in))))
        {
            IF_CHECK(sendto(server_sockfd,c_message,sizeof(*c_message), 0, (struct sockaddr *)&head->next->addr,sizeof(struct sockaddr_in)));

            head = head->next;
        }
        else
        {
            /* 在服务器链表当中删除对应客户端 */
            ptr_list_client_node temp;
            temp = head->next;
            head->next = temp->next;

            /* 扫尾处理 */
            free(temp);
            temp = NULL;
        }
    }
} /* ----- End of left_chatroom()  ----- */









