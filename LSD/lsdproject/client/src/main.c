/*
 *客户端主程序入口
 */

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "../include/fun.h"

int sockfd = -1;		//定义一个套接字

int fd[2] = {0};		//定义管道的文件描述符为全局变量

char login_user[20] = "";	//寄存登录的用户名


int main(int argc,char **argv)
{
	if(signal(SIGALRM,sighandlle) == SIG_ERR)
	{
		printf("注册信号失败\n");
	}
	//注册信号
	if(signal(SIGINT,sighandlle) == SIG_ERR)
	{
		printf("SIGINT信号注册失败\n");
	}
	if(signal(SIGTSTP,sighandlle) == SIG_ERR)
	{
		printf("SIGTSTP信号注册失败\n");
	}
	//创建管道
	pipe(fd);

	struct sockaddr_in ser;         //定义一个地址信息结构体
	memset(&ser,0,sizeof(ser));
	socket_init(&sockfd, &ser);
	//向服务器发送连接请求
	if(connect(sockfd,(struct sockaddr *)&ser,sizeof(struct sockaddr_in)) < 0)
	{
		printf("连接失败\n");
		return 1;
	}
		
	/*
	 * 创建一个新的线程：主线程负责向套结字写入数据 ，另一个线程负责从套结字读出服务器的回应
         * 然后入无名管道，主线程从管道读取数据做相应处理，再向套结字写入新的数据
         */
	pthread_t new_thread;
	create_new_pthread(&new_thread,&sockfd);
	//显示菜单
        client_menu(&sockfd);

	return 0;
}






