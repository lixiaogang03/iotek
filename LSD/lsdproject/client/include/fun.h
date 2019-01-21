
#ifndef _FUN_H
#define _FUN_H

/*
 *客户端相关功能函数
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <wait.h>


#define TYPE_LOGIN  0   //登陆数据包
#define	TYPE_REG    1   //注册数据包
#define TYPE_MSG    2   //消息数据包
#define	TYPE_HEART  3   //心跳数据包
#define	TYPE_CMD    4   //命令数据包
#define	TYPE_DOWN   5   //下线消息
#define	TYPE_ERR    6


//数据包组织   | 数据包的类型 | 数据的大小size | 数据内容char data[size] | 校验码 | 保留空间 |
typedef struct message
{
	int type;		//数据包类型
	char name[20];		//有效数据长度
	char pwd[20];		//用户密码
	char data[2048];	//有效数据
	
}MSG;
//管道声明
extern int fd[2];

extern int sockfd;

//寄存登录的用户名
extern char login_user[20];

//加载配置文件信息
extern void load_ser_config(char *IP,char *port);

//以分离属性创建客户端的读线程
extern void create_new_pthread(pthread_t *new_thread,int *sockfd);

//客户端读线程处理函数
extern void *pthread_deal(int *sockfd);

//客户端套接字创建与初始化
extern void socket_init(int *sockfd,struct sockaddr_in *ser);

//客户端初始登录界面
extern void client_menu(int *sockfd);

//发送注册包
extern void send_regist_packet(int *sockfd);

//发送登录包
extern void send_login_packet(int *sockfd);

//登录成功以后的菜单
extern void login_menu(int *sockfd);

//向服务器发送shell命令
extern void send_shell_cmd(int *sockfd);

//下线通知给服务器
extern void send_downline_pack(int *sockfd);

//异常信号处理函数
extern void sighandlle(int signo);

#endif



