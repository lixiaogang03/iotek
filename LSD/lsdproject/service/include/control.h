
#ifndef _CONTROL_H
#define _CONTROL_H
/*
 *功能实现函数
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <wait.h>
#include "../include/link_user.h"
#include "../include/link_online.h"
#include "../include/link_daily.h"
#include "../include/view.h"

#define gettid() syscall(__NR_gettid)


#define NONE         "\033[m" 
#define RED          "\033[0;32;31m" 
#define LIGHT_RED    "\033[1;31m" 
#define GREEN        "\033[0;32;32m" 
#define LIGHT_GREEN  "\033[1;32m"
#define BLUE         "\033[0;32;34m" 
#define LIGHT_BLUE   "\033[1;34m"  
/*
 *通信协议相关
 */
//数据类型宏
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

extern UNODE *uhead;
extern ONODE *ohead;
extern DNODE *dhead;

extern pthread_mutex_t mutex;

//加载配置文件信息
extern void load_ser_config(char *IP,char *port);

//套接字的初始化
extern void socket_init(int *sockfd,struct sockaddr_in *ser);

//以分离属性创建一个新线程
extern void create_new_pthread(pthread_t *new_thread,int lisfd);

//分离属性创建管理员线程
extern void create_admin_pthread(pthread_t *admin_thread);

//线程处理函数
extern void *pthread_deal(int lisfd);

//设置监听并获取连接用户的IP
extern void set_listen(int *sockfd,int *lisfd,char *cip);

//注册包处理（重名查询，追加所有用户链表节点）
extern void regist_pack_deal(MSG *mess,int lisfd);

//登入包处理（登录验证）
extern void login_pack_deal(MSG *mess,int lisfd,int *flag);

//心跳包处理
extern void heart_pack_deal(MSG *mess, int *flag);

//shell命令处理（开子进程处理，执行结果重定向到套接字）
extern void cmd_pack_deal(MSG *mess, int lisfd);

//标准输出与标准错误流重定向
extern void std_dup2(int lisfd);

//用户下线后处理
extern void downline_pack_deal(MSG *mess, int *flag);

//服务器退出的资源回收
extern void sighandlle(int signo);

#endif


