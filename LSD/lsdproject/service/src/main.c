/*
服务器端主程序入口
*/


#include "../include/control.h"

//三条链表的头节点定义
UNODE *uhead = NULL;
ONODE *ohead = NULL;
DNODE *dhead = NULL;

//定义互斥锁
pthread_mutex_t mutex;


int main(int arrgc,char **argv)
{
	//注册信号
	if(signal(SIGINT,sighandlle) == SIG_ERR)
	{
		printf("SIGINT信号注册失败\n");
	}
	if(signal(SIGTSTP,sighandlle) == SIG_ERR)
	{
		printf("SIGTSTP信号注册失败\n");
	}

	//链表头节点的创建和初始化
	uhead = (UNODE *)malloc(sizeof(UNODE));
	ohead = (ONODE *)malloc(sizeof(ONODE));
	dhead = (DNODE *)malloc(sizeof(DNODE));
	if(uhead == NULL || ohead == NULL || dhead == NULL)
	{
		return 1;
	}
	memset(uhead,0,sizeof(UNODE));
	memset(ohead,0,sizeof(ONODE));
	memset(dhead,0,sizeof(DNODE));
	
	load_all_user(uhead);			//加载所有用户信息
	load_all_daily(dhead);			//加载日志文件信息
	
	int sockfd = -1;
	struct sockaddr_in ser;
	socket_init(&sockfd,&ser);
	
	
	int lisfd = -1;        //连接套接字文件描述符
	char cip[16] = "";	//客户IP
	pthread_t new_thread;	//创建新线程

	pthread_t admin_thread;  //新线程处理管理员的请求
	//分离属性创建管理员线程，调用线程处理函数
	create_admin_pthread(&admin_thread);

	do
	{
		//设置监听提示连接信息
		set_listen(&sockfd, &lisfd, cip);
		
		//分离属性创建新的线程，调用线程处理函数
		create_new_pthread(&new_thread, lisfd);	

	}while(1);
	
	return 0;
}









