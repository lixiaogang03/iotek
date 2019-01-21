/*
  菜单管理
*/
#include "../include/view.h"


/*
 *管理员帐户名和密码核对
 *
 */
void pthread_admin_deal()
{
	int i = 3;//输入密码次数限制
	char name[20] = "";
	char pwd[20] = "";

	while(1)
	{
		printf("************管理员登录***************\n");
		printf("\t请输入管理员账户名：");
		scanf("%s",name);
		while(getchar()!='\n')
			;
		printf("\t请输入密码：");
		scanf("%s",pwd);
		while(getchar()!='\n')
			;
		if(!strcmp("admin",name) && !strcmp("123456",pwd))
		{
			admin_login();
			//break;
		}
		else
		{
			i--;
			if(i == 0)  
			{
				printf("密码输入已超过三次!!!!\n");
				printf(">>>>>按回车键退出:");
				while(getchar()!='\n')
					;
				break;
			}
			printf("输入不正确，还有%d次机会\n",i);
		}
	}
}
 



/*
服务器二级菜单（管理员登录成功后）
	1、查看所有注册用户信息
	2、查看在线用户
	3、查看日志文件
	4、关闭服务器
	5、管理员退出
*/
void admin_login()
{
	int cho = -1;//用户选项
	do
	{
		printf("****************************************\n");
		printf("\t1、查看所有注册用户信息\n");
		printf("\t2、查看在线用户\n");
		printf("\t3、查看日志文件\n");
		printf("\t4、关闭服务器\n");
		printf("\t0、管理员退出\n");
		printf("****************************************\n");

		printf(">>>>请输入选项:");
		scanf("%d",&cho);		
		while(getchar()!='\n')
			;
		switch(cho)
		{
			case 1:
				print_user_all(uhead);
				break;
			case 2:
				print_online_all(ohead);
				break;
			case 3:
				print_daily_all(dhead);
				break;
			case 4:
				raise(SIGINT);
				break;
			case 0:
				printf("管理员退出\n");
				return;
			default:
				printf("输入错误,请重新输入\n");
				break;
		}	

	}while(cho != 0);
}















