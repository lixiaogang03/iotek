/*
 功能实现部分
*/
#include "../include/control.h"

/*
 *加载配置文件信息
 *IP:服务器IP
 *port:服务器进程端口号
 *无返回
 */
void load_ser_config(char *IP,char *port)
{
	if(IP == NULL || port == NULL)
	{
		printf("指针传入失败\n");
		return;
	}
	FILE *fp = NULL;//定义文件指针
	fp = fopen("config.txt","rt");
	if(fp == NULL)
	{
		printf("config.txt文件打开失败\n");
		return;
	}
	//从文件中读取IP和端口号
	if(fscanf(fp,"%s\n%s",IP,port) < 0)
	{
		printf("fscanf error\n");
		return;
	}
}

/*
 *监听套接字初始化函数
 *sockfd:存储套接字地址
 *ser:指向地址结构体的指针
 */
void socket_init(int *sockfd,struct sockaddr_in *ser)
{
	if(sockfd == NULL || ser == NULL)
	{
		printf("参数传入失败\n");
		return;
	}
	//加载配置文件信息：IP、端口号
	char ser_IP[20] = "";
	char ser_port[5] = "";
	load_ser_config(ser_IP,ser_port);
	int reuse = 1;

	//建立套接字
	*sockfd = socket(AF_INET,SOCK_STREAM,0);
	//端口的立即重用
	if(setsockopt(*sockfd,SOL_SOCKET,SO_REUSEADDR,(char *)&reuse,sizeof(reuse)) < 0) 
        { 
                printf("setsockopt is wrong!\n"); 
                return; 
        } 

	if(*sockfd < 0)
	{
		printf("socket error\n");
		return;
	}

	//设置IPV4
	ser->sin_family = AF_INET;
	//端口号字节序转换
	ser->sin_port = htons(atoi(ser_port));
	//IP地址转换
	inet_pton(AF_INET,ser_IP,&ser->sin_addr.s_addr);

	//绑定本地信息：IP，进程的端口号bind();
	if(bind(*sockfd,(struct sockaddr *)ser,sizeof(*ser)) < 0)
	{
		printf("绑定地址结构体失败\n");
		return;
	}

	//监听客户端的服务请求
	if(listen(*sockfd,10) < 0)
	{
		printf("监听失败\n");
		return;
	}
}


/*
 *设置监听并获取连接用户的IP
 *sockfd:监听套接字指针
 *lisfd:指向监听套接字的指针
 *cip:指向当前连接用户的IP
 */
void set_listen(int *sockfd,int *lisfd,char *cip)
{
	if(cip == NULL || sockfd == NULL || lisfd == NULL)
	{
		return;
	}
	//客户信息结构体
	struct sockaddr_in client;
	memset(&client,0,sizeof(client));
	int len = sizeof(client);
	//设置监听
	printf("等待客户连接..............\n");
	*lisfd = accept(*sockfd,(struct sockaddr *)&client,(socklen_t *)&len);
	sleep(2);
	if(lisfd < 0)
	{
		printf("连接失败.....\n");
		return;
	}
	//输出已连接的客户IP
	memset(cip,0,20);
	inet_ntop(AF_INET,(void *)&client.sin_addr.s_addr,cip,20);
	printf(LIGHT_GREEN"客户IP:%s成功连接上\n"NONE,cip);

}


/*
 *以分离属性创建一个新用户线程
 *new_thread:指向新线程描述符的指针
 *lisfd: 已连接套接字指针
 */
void create_new_pthread(pthread_t *new_thread,int lisfd)
{	
	if(new_thread == NULL)
	{
		return;
	}
	int retval = -1;
	//定义线程属性
	pthread_attr_t attr;
	//线程属性初始化
	pthread_attr_init(&attr);
	//线程分离属性设置
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	//以分离属性创建子线程
	retval = pthread_create(new_thread,&attr,(void *)pthread_deal,(void *)lisfd);
	if(retval < 0)
	{
		perror("子线程创建失败\n");
	}
	//printf("创建新线程成功\n");
	//销毁线程属性结构体
	pthread_attr_destroy(&attr);
}


/*
 *分离属性创建管理员线程
 *admin_thread: 管理员线程描述符
 */
void create_admin_pthread(pthread_t *admin_thread)
{	
	if(admin_thread == NULL)
	{
		return;
	}
	int retval = -1;
	//定义线程属性
	pthread_attr_t attr;
	//线程属性初始化
	pthread_attr_init(&attr);
	//线程分离属性设置
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	//以分离属性创建子线程
	retval = pthread_create(admin_thread,&attr,(void *)pthread_admin_deal,NULL);//管理员线程处理
	if(retval < 0)
	{
		perror("子线程创建失败\n");
	}
	//销毁线程属性结构体
	pthread_attr_destroy(&attr);
}

/*
 *用户线程处理函数
 *lisfd:监听套接字
 */
void *pthread_deal(int lisfd)
{
	//接收数据缓存区
	MSG mess;
	int flag = 1;
	int length = -1;
	//循环读套接字，根据协议头作相应处理
	while(1)
	{
		memset(&mess,0,sizeof(mess));
		length = read(lisfd,&mess,sizeof(MSG));
		if(length <= 0)
		{
			printf(LIGHT_GREEN"客户端链接断开\n"NONE);
			return NULL;
		}
		else
		{
			//解包
			switch(ntohl(mess.type))
			{
				case 0:
					login_pack_deal(&mess,lisfd,&flag);	//处理登录数据包
					break;
				case 1:
					regist_pack_deal(&mess,lisfd);	//处理注册数据包
					break;
				case 2:
						//处理消息数据包
					break;	
				case 3:
					heart_pack_deal(&mess, &flag);
					break;
				case 4:
					cmd_pack_deal(&mess, lisfd);	//处理命令数据包
					break;
				case 5:				
					downline_pack_deal(&mess, &flag);
					break;
				case 6:
						//处理错误数据包
					break;
				default:
					printf("未知的数据包类型\n");
			}
		}	

	}
}


/*********************************与客户端的交互********************************/
/*
 * 注册包处理（重名查询，追加所有用户链表节点）
 * mess :从客户端接收的消息
 * lisfd :监听套结字
 */
void regist_pack_deal(MSG *mess,int lisfd)
{
	if(mess == NULL)
	{
		printf("指针传入失败\n");
		return;
	}
	MSG reply;
	memset(&reply,0,sizeof(MSG));
	USER user;	//定义用户信息结构体
	memset(&user,0,sizeof(USER));
	//重名检查
	UNODE *pre = NULL;
	pre = search_username(uhead,mess->name);
	if(pre == NULL)
	{
		//重名检查成功后回复用户
		reply.type = htonl(TYPE_REG);
		strcpy(reply.data, "ok");
		if(write(lisfd,&reply,sizeof(MSG)) < 0)
		{
			printf("写入套接字失败\n");
		}
		printf("写入套结字成功\n");
		strcpy(user.name,mess->name);
		strcpy(user.pwd,mess->pwd);
		//上锁
		pthread_mutex_lock(&mutex);
		//后向节点插入
		insert_user_after(uhead,&user);
		print_user_all(uhead);
		//打开互斥锁
		pthread_mutex_unlock(&mutex);
		
	}
	else
	{
		reply.type = htonl(TYPE_REG);
		strcpy(reply.data, "error");
		if(write(lisfd,&reply,sizeof(MSG)) < 0)
		{
			printf("写入套接字失败\n");
		}
		printf("回复重名检查失败消息\n");
	}

}

/*
 * 登入包处理（登录验证）
 * mess :从客户端接收的消息
 * lisfd :监听套结字
 */
void login_pack_deal(MSG *mess,int lisfd,int *flag)
{
	if(mess == NULL)
	{
		printf("参数传入失败\n");
		return;
	}
	ONLINE on_user;
	DAILY record;
	time_t curtime;					//定义时间变量
	char time_buf[30] = "";				//转化字符串
	MSG reply;					//回复数据包
	memset(&reply,0,sizeof(MSG));
	//上锁
	pthread_mutex_lock(&mutex);
	//是否已在线
	if(search_online_name(ohead, mess->name) != NULL)
	{
		//打开互斥锁
		pthread_mutex_unlock(&mutex);
		memset(&reply,0,sizeof(MSG));
		reply.type = htonl(TYPE_LOGIN);
		strcpy(reply.data, "already");
		if(write(lisfd,&reply,sizeof(MSG)) < 0)
		{
			printf("写入套接字失败\n");
		}
		return;	
	}
	//打开互斥锁
	pthread_mutex_unlock(&mutex);
	//用户名核对
	UNODE *pre = NULL;
	pre = search_username(uhead,mess->name);
	if(pre == NULL)				//要登录的用户名不存在
	{
		memset(&reply,0,sizeof(MSG));
		reply.type = htonl(TYPE_LOGIN);
		strcpy(reply.data, "error");
		if(write(lisfd,&reply,sizeof(MSG)) < 0)
		{
			printf("写入套接字失败\n");
		}
	}
	else								//要登录的用户名存在
	{
		if(!strcmp(pre->next->user.pwd, mess->pwd))
		{
			//回复客户端查询结果
			memset(&reply,0,sizeof(MSG));
			reply.type = htonl(TYPE_LOGIN);
			strcpy(reply.data, "ok");
			*flag = 1;		//心跳
			if(write(lisfd,&reply,sizeof(MSG)) < 0)
			{
				printf("写入套接字失败\n");
			}
	

			//获取用户的登录时间
			time(&curtime);
			strcpy(time_buf,ctime(&curtime));
			time_buf[strlen(time_buf)-1] = '\0';
			printf(RED"%s已上线\n"NONE,pre->next->user.name);

			//上锁
			pthread_mutex_lock(&mutex);

			//在线用户链表追加
			memset(&on_user,0,sizeof(ONLINE));
			strcpy(on_user.name, pre->next->user.name);
			strcpy(on_user.log_time,time_buf);
			insert_online_after(ohead, &on_user);
			print_online_all(ohead);

			//日志链表追加
			memset(&record,0,sizeof(DAILY));
			strcpy(record.name, pre->next->user.name);
			strcpy(record.log_time,time_buf);
			insert_daily_after(dhead, &record);
			//print_daily_all(dhead);

			//打开互斥锁
			pthread_mutex_unlock(&mutex);
			return;		
		
		}
		else
		{
			//回复客户端查询结果
			memset(&reply,0,sizeof(MSG));
			reply.type = htonl(TYPE_LOGIN);
			strcpy(reply.data, "error");
			if(write(lisfd,&reply,sizeof(MSG)) < 0)
			{
				printf("写入套接字失败\n");
			}
		}
	}
}

//数据包处理（修改用户名密码，查看历史信息，聊天记录）（这里不做删除）

/*
 * 心跳包处理
 * mess : 数据包结构指针
 * flag : 心跳标志指针
 */
void heart_pack_deal(MSG *mess, int *flag)
{
	if(mess == NULL)
	{
		return;
	}
	if(*flag == 1)
	{  
		printf(LIGHT_RED"%ld\t%s\t%s\n"NONE, (long int)gettid(), mess->name,mess->data);
	}
}


/*
 * shell命令处理（开子进程处理，执行结果重定向到套接字）
 * mess :消息结构体指针
 * lisfd :已链接套结子
 */
void cmd_pack_deal(MSG *mess, int lisfd)
{
	if(mess == NULL)
	{
		return;
	}
	printf(BLUE"%s\tshell cmd>>%s\n"NONE,mess->name,mess->data);
	//保存标准输出文件描述符
	ssize_t oldfd_out = dup(STDOUT_FILENO);
	ssize_t oldfd_err = dup(STDERR_FILENO);
	//标准输出与标准错误流重定向
	std_dup2(lisfd);
	//定义变量并初始化
	
	system(mess->data);
	//恢复重定向  
	std_dup2(oldfd_out);
	std_dup2(oldfd_err);
}


/*
 * 标准输出与标准错误流重定向
 * lisfd :已链接套结字
 * flag : 心跳标志指针
 */
void std_dup2(int lisfd)
{
	//重定向标准输出
	if(STDOUT_FILENO != dup2(lisfd,STDOUT_FILENO))
	{
		printf("dup2 error\n");
		return;
	} 
	//重定向标准错误
	if(STDERR_FILENO != dup2(lisfd,STDERR_FILENO))
	{
		printf("dup2 error\n");
		return;
	} 
}

//客户端之间聊天（线程通信）

/*
 * 用户下线后处理
 * lisfd:已连接套结字
 */
void downline_pack_deal(MSG *mess, int *flag)
{
	if(mess == NULL || flag == NULL)
	{
		printf("参数传入失败\n");
	}

	time_t curtime;
	char time_buf[30] = "";
	DNODE *pre = NULL;
	DNODE *p = dhead;
	DNODE *buf = NULL;
	printf(GREEN"%s下线了\n"NONE,mess->name);
	*flag = 0;
	//上锁
	pthread_mutex_lock(&mutex);

	//在线用户信息链表处理
	delete_online_user(ohead, mess->name);
	print_online_all(ohead);

	//日志信息链表处理
	time(&curtime);
	strcpy(time_buf,ctime(&curtime));
	time_buf[strlen(time_buf)-1] = '\0';
	//查找到此用户
	while(1)
	{
		buf = pre;		//寄存上一次
		pre = search_daily_name(p, mess->name);
		
		if(pre == NULL)
		{
			break;
		}
		p = pre->next; 		//查找下一个
	}
	strcpy(buf->next->daily.off_time, time_buf);
	strcpy(buf->next->daily.off_state, "normal");
	print_daily_all(dhead);
	//打开互斥锁
	pthread_mutex_unlock(&mutex);
}


/*
 * 客户端异常退出信号处理
 * signo:捕获到的信号
 */
void sighandlle(int signo)
{
	if(signo == SIGTSTP || signo == SIGINT)
	{
		printf("资源全部释放\n");
		//服务器主线程退出时将所有用户信息保存到文件
		save_user_txt(uhead);
		//保存日志信息到文件
		save_daily_txt(dhead);
		//链表的释放
		free_all_usr(uhead);		
		free_all_online(ohead);	
		free_all_daily(dhead);
	
		//防止产生野指针
		uhead = NULL;
		ohead = NULL;
		dhead = NULL;

		//销毁互斥锁
		pthread_mutex_destroy(&mutex);

		exit(1);		
	}
}











