/*
客户端功能函数
*/
#include "../include/fun.h"

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
 *客户端套接字创建与初始化
 *sockfd:指向套接字描述符的指针
 *ser :指向地址信息结构体的指针
 */
void socket_init(int *sockfd,struct sockaddr_in *ser)
{
	if(sockfd == NULL)
	{
		return;
	}
	//加载配置文件信息：IP、端口号
	char ser_IP[20] = "";
	char ser_port[5] = "";
	load_ser_config(ser_IP,ser_port);
	int reuse = 0;
	//创建服务进程套接字
	*sockfd = socket(AF_INET,SOCK_STREAM,0);
	
	//端口的立即重用
	if(setsockopt(*sockfd,SOL_SOCKET,SO_REUSEADDR,(char *)&reuse,sizeof(reuse)) < 0) 
        { 
                printf("setsockopt is wrong!\n"); 
                return; 
        } 
	if(sockfd < 0)
	{
		printf("创建套接字失败\n");
		return;
	}
	//地址信息初始化
	ser->sin_family = AF_INET;
	ser->sin_port = htons(atoi(ser_port));			//字节序转换
	inet_pton(AF_INET,ser_IP,&ser->sin_addr.s_addr);	//网络地址转换
}
/*
 *以分离属性创建客户端的读线程
 *new_thread :新线程描述符
 *sockfd :套结字描述符
 */
void create_new_pthread(pthread_t *new_thread,int *sockfd)
{	
	if(new_thread == NULL || sockfd == NULL)
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
	retval = pthread_create(new_thread,&attr,(void *)pthread_deal,(void *)sockfd);//线程处理函数
	if(retval < 0)
	{
		perror("子线程创建失败\n");
	}
	//销毁线程属性结构体
	pthread_attr_destroy(&attr);
}

/*
 * 读线程处理函数
 * sockfd :指向套结字描述符的指针
 */
void *pthread_deal(int *sockfd)
{
	if(sockfd == NULL)
	{
		printf("套结字传入失败\n");
		return NULL;
	}
	//从套结字中读取数据
	MSG mess;
	while(1)
	{
		memset(&mess,0,sizeof(MSG));
		if(read(*sockfd,&mess,sizeof(MSG)) < 0)
		{
			printf("从套结字读数据失败\n");
			return NULL;
		}
		//将读到的数据写入管道
		if(write(fd[1],&mess,sizeof(MSG)) != sizeof(MSG))
		{
			printf("write pipe error\n");
			return NULL;
		}
	}
	return (void *)1;
}





/*
 *客户端初始登录界面
 */
void client_menu(int *sockfd)
{
	
	int cho = -1;
	do
	{	
		printf("**************************************\n");
		printf("\t\t1、用户注册\n");
		printf("\t\t2、用户登录\n");
		printf("\t\t0、退出客户端\n");
		printf("**************************************\n");
		printf("请输入选项: ");
		scanf("%d",&cho);
		while(getchar() != '\n');//清空输入缓存
		
		switch(cho)
		{
			case 1://进入注册二级菜单
				send_regist_packet(sockfd);
				break;
			case 2://用户登录二级菜单
				send_login_packet(sockfd);
				break;
			case 0://退出客户端
				close(*sockfd);//关闭套结字
				break;
			default:
				printf("无效的选项输入\n");
		}

	}while(cho != 0);
}


/*
 *发送注册包
 *sockfd :指向套接字的指针
 *ser：服务器地址结构体指针
 */
void send_regist_packet(int *sockfd)
{
	if(sockfd == NULL)
	{
		return;
	}
	MSG mess;   //定义一个数据包
	//用户名和密码输入
	while(1)
	{
		//打包发送，等待用户重名校验结果
		memset(&mess,0,sizeof(MSG));		//初始化数据包
		mess.type = htonl(TYPE_REG);				//数据包类型
		printf("请输入要注册的用户名：");
		scanf("%s",mess.name);
		while(getchar() != '\n')
			;
		printf("请输入要密码：");
		scanf("%s",mess.pwd);
		while(getchar() != '\n')
			;
		//向服务器发送注册包
		if(write(*sockfd,&mess,sizeof(MSG)) < 0)
		{
			printf("向套接字写入数据失败\n");
		}
		
		//从管道读出数据
		memset(&mess,0,sizeof(MSG));
		if(read(fd[0],&mess,sizeof(MSG)) < 0)
		{
			printf("从管道读出数据失败\n");
		}

		//读出的数据处理
		if(mess.type == ntohl(TYPE_REG))		//数据包类型判断
		{
			if(!strcmp(mess.data, "ok"))	//重名检查通过
			{
				printf("注册成功\n");
				break;
			}
			if(!strcmp(mess.data, "error"))	//重名检查失败
			{
				printf("该用户名已被注册，请重新注册\n");
			}
		}
	}	
}


/*
 * 发送登录包
 * sockfd:指向套接字的指针
 */
void send_login_packet(int *sockfd)
{
	if(sockfd == NULL)
	{
		return;
	}
	MSG mess;   //定义一个数据包
	
	while(1)
	{
		//打包发送
		memset(&mess,0,sizeof(MSG));		//初始化数据包
		mess.type = htonl(TYPE_LOGIN);				//数据包类型
		printf("请输入要登录的用户名：");
		scanf("%s",mess.name);
		while(getchar() != '\n')
			;
		printf("请输入要登录密码：");
		scanf("%s",mess.pwd);
		while(getchar() != '\n')
			;
		//寄存登录的用户名
		memset(login_user,0,20);
		strcpy(login_user, mess.name);
		
		//向服务器发送登录消息
		if(write(*sockfd,&mess,sizeof(MSG)) < 0)
		{
			printf("向套接字写入数据失败\n");
		}
		
		//从管道读出数据
		memset(&mess,0,sizeof(MSG));
		if(read(fd[0],&mess,sizeof(MSG)) < 0)
		{
			printf("从管道读出数据失败\n");
		}
			
		//读出的数据判断处理
		if(mess.type == ntohl(TYPE_LOGIN))
		{
			if(!strcmp(mess.data, "ok"))		//登录验证通过
			{
				alarm(3);
				login_menu(sockfd);
				break;
			
			}
			if(!strcmp(mess.data, "error"))	//登录验证失败
			{
				printf("用户名或密码输入错误\n");
			}
			if(!strcmp(mess.data, "already"))	//登录验证失败
			{
				printf("该用户名已在线\n");
				break;
			}
		}
	}
	
}


/*
 *登录成功以后的菜单（登录成功以后开始发送心跳包）
 *sockfd :指向套结字的指针	
 */
void login_menu(int *sockfd)
{
	int cho = -1;
	do
	{
		printf("**********************************\n");
		printf("\t1、发送shell命令\n");
		printf("\t2、聊天\n");
		printf("\t0、退出\n");
		printf("**********************************\n");

		printf("请输入选项：");
		scanf("%d",&cho);
		while(getchar()  != '\n');
		
		switch(cho)
		{
			case 1://发送shell命令
				send_shell_cmd(sockfd);
				break;	
			case 2://聊天
				
				break;	
			case 0://下线
				send_downline_pack(sockfd);
				break;
			default:
				printf("无效的选项输入\n");
				break;	
		}


	}while(cho != 0);
}

//发送心跳包

//发送shell命令
/* 
 * 向服务器发送shell命令
 * sockfd : 指向套结字的指针
 */
void send_shell_cmd(int *sockfd)
{
	if(sockfd == NULL)
	{
		return;
	}
	MSG mess;   //定义一个数据包
	//char buf[1024] = "";
	char buf[10] = "";
	//打包发送
	memset(&mess,0,sizeof(MSG));		//初始化数据包
	mess.type = htonl(TYPE_CMD);				//数据包类型
	printf("请输入要发送的shell命令：");
	//scanf("%s",mess.data);
	fgets(mess.data,sizeof(mess.data),stdin);
	mess.data[strlen(mess.data)-1] = '\0';
	strcpy(mess.name, login_user);
	//向服务器发送shell命令
	if(write(*sockfd,&mess,sizeof(MSG)) < 0)
	{
		printf("向套接字写入数据失败\n");
	}
	//从管道读出数据
	while(read(fd[0],&buf,9) == 9)
	{
		buf[9] = '\0';
		printf("%s",buf);
	}
}
//发送聊天数据包

/*
 *下线处理
 *sockfd :套结字指针
 */
void send_downline_pack(int *sockfd)
{
	if(sockfd == NULL)
	{
		return;
	}
	//向服务器发送一个下线消息
	MSG mess;
	memset(&mess,0,sizeof(MSG));
	mess.type = htonl(TYPE_DOWN);
	strcpy(mess.name,login_user);
	if(write(*sockfd,&mess,sizeof(MSG)) <= 0)
	{
		printf("write error\n");
	}
}


/*
 * 客户端异常退出信号处理
 * signo:捕获到的信号
 */
void sighandlle(int signo)
{
	if(signo == SIGTSTP || signo == SIGINT)
	{
		printf("客户端非正常退出\n");
		exit(1);		
	}
	if(signo == SIGALRM)
	{
		MSG mess;
		memset(&mess,0,sizeof(MSG));
		mess.type = htonl(TYPE_HEART);
		strcpy(mess.name,login_user);
		strcpy(mess.data,"heart");
		if(write(sockfd,&mess,sizeof(MSG)) < 0)
		{
			printf("write sockfd error\n");
		}
		alarm(3);
	}
}






