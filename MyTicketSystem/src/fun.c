
/********************************************************************************
*程序功能：增删改查功能函数
*作者：lxg
*源程序名：fun.c
*创建日期：2014-4-21
*最后更新日期：2014-4-27
***********************************************************************************/
//文件包含
#include "../include/fun.h"
#include "../include/menu.h"

/***********************************************************************************
 * 管理员登录
 * p :指向结构体ADMIN的指针
 ***********************************************************************************/
void admin_check_login(ADMIN *p)
{
	if(p == NULL)
		return;
	int i = 3;//输入密码次数限制
	char name[20] = "";
	char pwd[20] = "";

	while(1)
	{
		printf("请输入您的账户名：");
		scanf("%s",name);
		while(getchar()!='\n')
			;
		printf("请输入密码：");
		scanf("%s",pwd);
		while(getchar()!='\n')
			;
		if(!strcmp(p->adm,name) && !strcmp(p->pwd,pwd))
		{
			admin_login();
			break;
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


/**************************************************************************************
 * 用户注册
 * head:头节点
 **************************************************************************************/
void f_usr_regist(UNODE *head)
{
	if(head == NULL)
		return;

	char temp1[20] = "";
	char temp2[20] = "";
	UNODE *pre = NULL;
 	USER user = {"","",0};//临时结构体初始化
 	//重名检查 
	while(1)
 	{
 		printf("请输入用户名(英文)：");
 		scanf("%s",user.uid);
		while(getchar() != '\n')
			;
 		pre = search_username(head,user.uid);
 		if(pre == NULL)
 			break;
 		printf("此用户名已被注册\n");
 	}
	while(1)
	{
		printf("请输入密码：");
		scanf("%s",temp1);
		while(getchar()!='\n')
			;
		printf("请再次输入密码：");
		scanf("%s",temp2);
		while(getchar()!='\n')
			;
		if(!strcmp(temp1,temp2))
		{
			strcpy(user.pwd,temp1);
			break;
		}
		printf("两次输入的密码不一致,请重新输入\n");
	}
	insert_user_after(head,&user);//追加节点
	printf("注册成功！\n");//打印检验
	//print_user_all(head);
}


/*********************************************************************************
 * 用户登录
 * head :用户信息链头节点
 *********************************************************************************/
void user_check_login(UNODE *head)
{
	if(head == NULL)
		return;

	int i = 3;//输入密码次数控制
	char name[20] = "";
	char pwd[20] = "";
	UNODE *pre = NULL;

	printf("请输入您的用户名：");
	scanf("%s",name);
	while(getchar()!='\n')
		;
	while(1)
	{
		printf("请输入密码：");
		scanf("%s",pwd);
		while(getchar()!='\n')
			;
		pre = search_username(head,name);//查找函数,返回前一个节点
		if(pre == NULL)
		{
			printf("此用户不存在\n");
			printf(">>>>>按回车键退出:");
			while(getchar()!='\n')
				;
			break;
		}
		else if(strcmp(pre->next->user.pwd,pwd))
		{
			i--;
			if(i == 0)  
			{
				printf("密码输入已超过三次，请联系管理员！！！\n");
				printf(">>>>>按回车键退出:");
				while(getchar()!='\n')
					;
				break;
			}
			printf("密码不正确,还有%d次机会\n",i);
		}
		else
		{
			user_login(pre->next);
			return;
		}	
	}
}


/***********************************************************************************
 * 购票号码输入函数（处理号码非法输入的问题）
 * ticket :指向TICKET结构体的指针
 * 返回是否合法购买的标志
 **********************************************************************************/
int f_buy_code(TICKET *ticket)
{
	int i = 0;
	for(i = 0;i < 4;i++)
	{
		printf(">>>请输入购买的第%d个号码(1-5)：",i+1);
		scanf("%d",&ticket->buyid[i]);
		while(getchar() != '\n')
			;
		if(ticket->buyid[i] < 1 || ticket->buyid[i] > 5)
		{
			printf("非法号码输入！！！\n");//输错一次退出购票
			return 0;
		}	
	}
	printf("请输入要购买的注数：");
	scanf("%d",&ticket->bnum);
	//清空输入缓存
	while(getchar() != '\n')
		;
	if(ticket->bnum == 0)
	{
		printf("非法注数输入\n");
		return 0;
	}	
	return 1;	
}


/***********************************************************************************
 * 打印购买的彩票的信息
 * ticket :指向TICKET结构体的指针
 ***********************************************************************************/
void f_print_buycode(TICKET *ticket)
{
	printf("\t\t\t*****************************************************************\n");
	printf("\t\t\t\t用户名\t期号\t购买号码\t注数\t购票金额\n");
	printf("\t\t\t\t%s\t%d\t",ticket->uid,ticket->timeid);
	printf("%d %d %d %d\t",ticket->buyid[0],ticket->buyid[1],ticket->buyid[2],ticket->buyid[3]);
	printf("\t%d\t%d\n",ticket->bnum,5 * ticket->bnum);
	printf("\t\t\t*****************************************************************\n");
}


/***********************************************************************************
 * 购票
 * thead: 购票信息头节点
 * usr ：当前登录用户节点
 * whead: 开奖信息头节点
 ***********************************************************************************/
void buy_ticket(TNODE *thead,UNODE *usr,WNODE *whead)
{
	if(thead == NULL)	return;
	if(usr == NULL)	return;
	if(whead == NULL)	return;
	
	//extern ADMIN admin;
	extern PROFIT profit;
	char cho = '\0'; 
	TICKET ticket;
	//临时数据域初始化，开奖状态 中奖状态置0 中奖金额置0，开奖时进行更新
	memset(&ticket,0,sizeof(TICKET));
	//获得上一期开奖的期号
	while(whead->next != NULL)
	{
		whead = whead->next;
	}
	//购票信息链表更新
	ticket.timeid = whead->winner.timeid + 1;//上一期的期号加1
	strcpy(ticket.uid,usr->user.uid);
	//盈利结构体更新
	profit.timeid = ticket.timeid;//期号
	strcpy(profit.type,"in");//类型
	strcpy(profit.remark,"购票--");//备注更新
	strcat(profit.remark,usr->user.uid);//谁购票
	
	while(1)
	{
		while(f_buy_code(&ticket) == 0)//调用购票函数，直到输入正确的购票号码
			;
		if(usr->user.money < (5 * ticket.bnum))
		{
			printf("余额不足，请先充值再购买\n");
			return;
		}
		f_print_buycode(&ticket);//打印购买的彩票的信息	
		usr->user.money = usr->user.money - 5 * ticket.bnum;//用户余额更新
		admin.money = admin.money + 5 * ticket.bnum;// 奖池金额更新
		//盈利信息更新
		profit.money = 5 * ticket.bnum;//发生金额
		profit.total_money = admin.money;//奖池金额
		save_profit_txt(&profit);//追加模式保存到文件
		//购票信息链尾部插入新结点
		insert_ticket_after(thead,&ticket);
		
		printf("是否继续购买（y/n）:");
		scanf(" %c",&cho);
		while(getchar()!='\n')
			;
		if(cho != 'y' && cho != 'Y')
		{
			break;
		}
	}
}


/*********************************************************************************
 *查看个人信息
 *usr ：当前登录用户节点
 *********************************************************************************/
void f_search_usr(UNODE *usr)
{
	if(usr == NULL)
		return;
	printf("\t\t\t***********************************************\n");
	printf("\t\t\t     用户名\t密码\t余额\n");
	printf("\t\t\t     %s\t%s\t%d\n",usr->user.uid,usr->user.pwd,usr->user.money);
	printf("\t\t\t***********************************************\n");	
}


/**********************************************************************************
 * 查看购票信息
 * head : 已购票信息链头节点
 * usr ：当前登录用户信息节点
 **********************************************************************************/
void f_search_ticket(TNODE *head,UNODE *usr)
{
	if(head == NULL)	return;
	if(usr == NULL)	return;

	printf("用户名\t期号\t号码\t注数\t开奖\t中奖\t中奖金额\n");
	TNODE *temp = NULL;
	while(1)
	{
		temp = search_ticketname(head,usr->user.uid);
		if(temp == NULL)
			return;
		head = temp->next;
		print_oneticket(head);
	}
}

/***************************************************************************************
 * 修改密码
 * usr : 当前登录用户信息链节点
 ***************************************************************************************/
void f_update_usrpwd(UNODE *usr)
{
	if(usr == NULL)	return;

	char oldpwd[20] = "";
	char newpwd1[20] = "";
	char newpwd2[20] = "";
	char cho = '\0';

	printf("请输入原来的密码：");
	scanf("%s",oldpwd);
	while(getchar()!='\n')
		;
	if(strcmp(usr->user.pwd,oldpwd))
	{
		printf("输入的密码不正确\n");
		return;
	}
	while(1)
	{
		printf("请输入新的密码：");
		scanf("%s",newpwd1);
		while(getchar()!='\n')
			;
		printf("请再次输入新的密码：");
		scanf("%s",newpwd2);
		while(getchar()!='\n')
			;
		if(!strcmp(newpwd1,newpwd2))
		{
			printf("确定要修改吗？(y/n)");
			scanf(" %c",&cho);
			while(getchar()!='\n')
				;
			if(cho == 'y' || cho == 'Y')
			{
				strcpy(usr->user.pwd,newpwd1);
				return;
			}
		}
		else
		{
			printf("两次密码输入不一致，请重新输入\n");
		}
	}
}


/******************************************************************************
 * 追加金额
 * usr : 当前登录用户信息链节点
 ******************************************************************************/
void f_usr_add_money(UNODE *usr)
{
	if(usr ==NULL)		return;

	int money = 0;//追加的金额
	char cho = '\0';
	printf("请输入追加的金额（yuan):");
	scanf("%d",&money);
	while(getchar()!='\n')
		;
	if(money == 0)
	{
		printf("非法输入!!!\n");
		return;
	}
	printf("确定要追加吗？(y/n):");
	scanf(" %c",&cho);
	while(getchar()!='\n')
		;
	if(cho == 'y' || cho == 'Y')
	{
		usr->user.money += money;
		printf("\t\t此时的个人余额为：%d\n",usr->user.money);
	}
}


/**********************************************************************************
 * 摇奖延时函数
 *********************************************************************************/
void delay()
{
	long i = 800000000;
	long j = 100000000;
	for(;i;i--)
	{
		for(;j;j--);
	}
}


/**********************************************************************************
 * 打印本期开奖信息
 * win :开奖信息结构体指针
 **********************************************************************************/
void f_print_wincode(WINNER *win)
{
	printf("\t\t\t*****************************************************\n");
	printf("\t\t          期号\t中奖号码\t\t开奖时间            \n");
	printf("\t\t          %d\t",win->timeid);
	printf("%d %d %d %d\t\t",win->zid[0],win->zid[1],win->zid[2],win->zid[3]);
	printf("%s",win->ktime);//自带回车符
	printf("\t\t\t*****************************************************\n");
}


/**********************************************************************************
 * 摇号并创建开奖信息链表
 * whead:开奖信息链表头节点
 * thead:已购票信息链表头节点
 * uhead：用户信息链表头节点
 **********************************************************************************/
void f_winner(WNODE *whead,TNODE *thead,UNODE *uhead)
{
	if(whead == NULL)
		return;
	
	int i = 4;//开奖号码
	WINNER win;
	WNODE *temp = NULL;
	memset(&win,0,sizeof(WINNER));

	srand((unsigned) time(NULL));//Initializes the random number generator using the time of day.
	//改变期号
	temp = whead;
	while(temp->next != NULL)
	{
		temp = temp->next;
	}
	win.timeid = temp->winner.timeid + 1;//找到上一期的期号后加1作为本期的期号
	//存入本期的开奖号码
	while(i)
	{
		--i;
		win.zid[i] = rand() % 5 + 1;//产生1～5的随机数
	}
	//开奖时间
	time_t tim;
	tim = time(NULL);
	strcpy(win.ktime,ctime(&tim));//自带回车符
	//延时
	system("cat menudisplay/yaohao.txt");
	delay();
	//打印本期开奖信息
	f_print_wincode(&win);
	//尾部插入链表节点
	insert_winner_after(whead,&win);
	//金额处理
	f_money_deal(uhead,thead,win);
}


/*****************************************************************************************
 * 金额管理(用户余额，奖池金额，开奖状态，中奖状态，中奖金额）
 * uhead ：用户信息链头节点
 * thead : 已购票信息链头节点
 * win : 开奖信息结构体
 ******************************************************************************************/
void f_money_deal(UNODE *uhead,TNODE *thead,WINNER win)
{
	if(uhead == NULL)  return;
	if(thead == NULL)  return;

	extern ADMIN admin;
	extern PROFIT profit;
	TNODE *temp = NULL;
	UNODE *usr = NULL;
	int grade = 0;
	//对已购票的用户进行循环比对处理
	while(thead->next != NULL)
	{
		temp = search_timeid(thead,win.timeid);//返回的是找到的前一节点
		if(temp == NULL)
			return;
		thead = temp->next;
		thead->ticket.kflag = 1;//开奖标志更新
		grade = f_money_grade(thead,win.zid);
		//盈利信息更新
		strcpy(profit.type,"out");//类型更新
		if(grade == 4)
		{
			//奖池金额更新
			admin.money = admin.money - 100 * thead->ticket.bnum;
			//盈利信息更新
			profit.money = 100 * thead->ticket.bnum;
			profit.total_money = admin.money;
			strcpy(profit.remark,"中奖--");
			strcat(profit.remark,thead->ticket.uid);
			save_profit_txt(&profit);//追加保存到文件
			//用户余额更新
			usr = search_username(uhead,thead->ticket.uid);
			usr->next->user.money += 100 * thead->ticket.bnum;
			//中奖状态更新
			thead->ticket.zflag = 1;
			//中奖金额更新
			thead->ticket.money = 100 * thead->ticket.bnum;
		}
		else if(grade == 3)
		{
			//奖池金额更新
			admin.money = admin.money - 50 * thead->ticket.bnum;
			//盈利信息更新
			profit.money = 50 * thead->ticket.bnum;
			profit.total_money = admin.money;
			strcpy(profit.remark,"中奖--");
			strcat(profit.remark,thead->ticket.uid);//追加保存到文件
			save_profit_txt(&profit);
			//用户余额更新
			usr = search_username(uhead, thead->ticket.uid);
			usr->next->user.money += 50 * thead->ticket.bnum;
			//中奖状态更新
			thead->ticket.zflag = 1;
			//中奖金额更新
			thead->ticket.money = 50 * thead->ticket.bnum;
		}
		else if(grade == 2)
		{
			//奖池金额更新
			admin.money = admin.money - 10 * thead->ticket.bnum;
			//盈利信息更新
			profit.money = 10 * thead->ticket.bnum;
			profit.total_money = admin.money;
			strcpy(profit.remark,"中奖--");
			strcat(profit.remark,thead->ticket.uid);
			save_profit_txt(&profit);//追加保存到文件
			//用户余额更新
			usr = search_username(uhead, thead->ticket.uid);
			usr->next->user.money += 10 * thead->ticket.bnum;
			//中奖状态更新
			thead->ticket.zflag = 1;
			//中奖金额更新
			thead->ticket.money = 10 * thead->ticket.bnum;
		}
		else	;				
	}
}


/**************************************************************************************
 * 奖金分级函数
 * temp :当前购票信息
 * num : 开奖号码
 **************************************************************************************/
int f_money_grade(TNODE *temp,int num[4])
{
	int i = 4;
	int grade = 0;
	while(i)
	{
		--i;
		if(temp->ticket.buyid[i] == num[i])
			grade++;
	}
	return grade;
}


/***********************************************************************************
 * 中奖信息通知：用户登录时对上一期是否中奖进行消息显示，以及总共中奖金额的统计
 * usr ：当前登录用户信息节点指针
 * thead :已购彩票信息链头节点指针
 * whead ：已开奖信息链表头结点指针
 ************************************************************************************/
void f_winner_notice(UNODE *usr,TNODE *thead,WNODE *whead)
{
	if(usr == NULL || thead == NULL || whead == NULL)
		return;
	TNODE *temp = NULL;
	int sum_money = 0;//总中奖金额寄存变量
	//找到本期的开奖信息
	while(whead->next != NULL)
	{
		whead = whead->next;
	}
	printf("\t\t\t******************************************************\n");
	printf("\t\t\t\t第 %d 期的中奖号码为：%d  %d",whead->winner.timeid,whead->winner.zid[0],whead->winner.zid[1]);
	printf("  %d  %d\n",whead->winner.zid[2],whead->winner.zid[3]);
	//在当前购票信息链中统计当前登录用户中奖金额
	while (1)
	{
		temp = search_ticketname(thead,usr->user.uid);//返回查找到的前一节点指针
		//测试返回值
		if(temp == NULL)
		{	
			break;
		}
		thead = temp->next;
		//筛选本期期号
		if(thead->ticket.timeid == whead->winner.timeid)
		{
			//本期中奖金额累加统计
			sum_money += thead->ticket.money;
		}
		if(thead->next == NULL)
		{
			break;
		}
	}
	//判断打印消息
	if(sum_money > 0)
	{
		printf("\t\t\t\t\t*^_^*恭喜您中奖啦！！\n");
		printf("\t\t\t\t\t*^_^*您本期的总中奖金额为：%d 元\n",sum_money);
		printf("\t\t\t*****************************************************\n");		
	}
	else
	{
		printf("\t\t\t\t\t真遗憾：您没有中奖............\n");
		printf("\t\t\t\t\t\t期待下一次的好运气吧.......\n");
		printf("\t\t\t*****************************************************\n");	
	}	
}


/***********************************************************************************
 * 管理员信息存储到文件
 * admin:管理员信息结构体
 ***********************************************************************************/
void save_admin_txt(ADMIN *admin)
{
	if(admin == NULL)
		return;

	FILE *fp = fopen("ticketfile/administer.txt", "wt"); 
	if (fp == NULL)
	{
		printf("打开失败\n");
		return;
	}
	//只向文件中写入管理员信息的内容
	fprintf(fp,"%s\t%s\t%d\n",admin->adm,admin->pwd,admin->money);

	fclose(fp);
}


/************************************************************************************
 * 加载管理员信息到结构体
 * admin :管理员信息结构体
 ************************************************************************************/
void load_admin_txt(ADMIN *admin)
{
	if(admin == NULL)
		return;

	FILE *fp = fopen("ticketfile/administer.txt", "rt");
	if (fp == NULL)
	{
		printf("打开失败\n");
		return;
	}
	fscanf(fp,"%s\t%s\t%d\n",admin->adm,admin->pwd,&admin->money);
	fclose(fp);
}


/****************************************************************************************
 * 查看管理员信息
 * admin :管理员信息结构体
 ****************************************************************************************/
void f_view_admin(ADMIN *adm)
{
	if(adm == NULL)
		return;
	printf("\t\t\t****************************************************\n");
	printf("\t\t\t       帐户名\t密码\t奖池金额\n");
	printf("\t\t\t       %s\t%s\t%d\n",adm->adm,adm->pwd,adm->money);
	printf("\t\t\t****************************************************\n");
}


/**************************************************************************************
 * 修改管理员密码
 * admin :指向管理员信息的结构指针
 **************************************************************************************/
void f_update_adminpwd(ADMIN *admin)
{
	if(admin == NULL)
		return;
	int num = 3;//密码循环输入次数控制
	char cho = '\0';
	char old_pwd[20] = "";
	char new_pwd1[20] = "";
	char new_pwd2[20] = "";

	printf("请输入原来的管理员密码：");
	scanf("%s",old_pwd);
	while(getchar()!='\n')
		;
	if(strcmp(admin->pwd,old_pwd))
	{
		printf("密码输入不正确\n");
		return;
	}
	printf("确定要修改吗？(y/n):");
	scanf(" %c",&cho);
	while(getchar()!='\n')
		;
	if(cho == 'y' || cho == 'Y')
	{
		while(1)
		{
			printf("请输入新的管理员密码：");
			scanf("%s",new_pwd1);
			while(getchar()!='\n')
				;
			printf("请再次输入新的管理员密码：");
			scanf("%s",new_pwd2);
			while(getchar()!='\n')
				;
			if(!strcmp(new_pwd1,new_pwd2))
			{
				strcpy(admin->pwd,new_pwd1);
				break;
			}
			else
			{
				num--;
				if(num == 0)
				{
					printf("密码输入已超过三次\n");
					printf(">>>>>按回车键退出:");
					while(getchar()!='\n')
						;
					break;
				}
				printf("两次输入的新密码不一致，还有%d次机会\n",num);
			}
		}
	}
}


/******************************************************************************
 * 管理员权限下修改彩民密码
 * head :用户信息链头节点
 ******************************************************************************/
void f_admin_update_usrpwd(UNODE *head)
{
	if(head == NULL)
		return;

	char update_usr[20] = "";//修改谁的密码
	char new_usrpwd[20] = "";
	UNODE *temp = NULL;

	printf("请输入要修改的用户名：");
	scanf("%s",update_usr);
	while(getchar()!='\n')
		;
	temp = search_username(head,update_usr);//返回前一个
	if(temp == NULL)
	{
		printf("此用户不存在\n");
		return;
	}
	printf("原来的密码为：%s\n",temp->next->user.pwd);
	printf("请输入新密码：");
	scanf("%s",new_usrpwd);
	while(getchar()!='\n')
		;
	//密码修改
	strcpy(temp->next->user.pwd,new_usrpwd);
	printf("修改后的密码为：%s\n",temp->next->user.pwd);
}


/**********************************************************************************
 * 追加奖池金额
 * admin :管理员信息结构体指针
 **********************************************************************************/
void f_admin_add_money(ADMIN *admin)
{
	if(admin == NULL)
		return;

	int add = 0;
	char cho = '\0';

	printf("请输入追加的金额（yuan):");
	scanf("%d", &add);
	while(getchar()!='\n')
		;
	if(add == 0)
	{
		printf("非法输入!!!\n");
		return;
	}

	printf("确定要追加吗？(y/n)");
	scanf(" %c", &cho);
	while(getchar()!='\n')
		;
	if (cho == 'y' || cho == 'Y')
	{
		admin->money = admin->money + add;
		printf("追加后的奖池金额为:%d\n",admin->money);
	}
}


/*********************************************************************************
 * 按用户名删除注册用户（判断余额）
 * head :用户信息链头节点
 *********************************************************************************/
void f_delete_usr(UNODE *head)
{
	if(head == NULL)
		return;
	char de_usrname[20] = "";
	char cho = '\0';
	UNODE *temp = NULL;
	UNODE *pre = NULL;

	printf("请输入要删除的用户的用户名：");
	scanf("%s",de_usrname);
	while(getchar()!='\n')
		;

	pre = search_username(head,de_usrname);
	if(pre == NULL)
	{
		printf("要删除的用户不存在\n");
		return;
	}
	//删除节点
	printf("确定要删除吗？(y/n)");
	scanf(" %c", &cho);
	while(getchar()!='\n')
		;
	if (cho == 'y' || cho == 'Y')
	{
		if(pre->next->user.money > 0)
		{
			printf("此用户仍有余额，无法删除\n");
		}
		else
		{
			temp = pre->next;
			pre->next =temp->next;
			free(temp);
			printf("删除成功\n");
		}
	}
	temp = NULL;//防止悬空指针
}


/****************************************************************************************
 * 按用户名删除购票信息
 * head:购票信息链头节点
 ****************************************************************************************/
void f_delete_ticket_usr(TNODE *head)
{
	if(head == NULL)
		return;

	char de_usrname[20] = "";
	char cho = '\0';
	TNODE *temp = NULL;
	TNODE *pre = NULL;

	printf("请输入要删除的购票信息的用户名：");
	scanf("%s", de_usrname);
	while(getchar()!='\n')
		;
	printf("确定要删除吗？(y/n)");
	scanf(" %c", &cho);
	while(getchar()!='\n')
		;
	if (cho != 'y' && cho != 'Y')
	{
		return;
	}
	while(1)
	{
		pre = search_ticketname(head,de_usrname);
		if (pre == NULL)
			break;
		//删除节点
		temp = pre->next;
		pre->next = temp->next;
		free(temp);
	}
	printf("删除成功\n");
	temp = NULL; //防止悬空指针
}


/*****************************************************************************************
 * 按期号删除购票信息
 * head:购票信息链头节点
 *****************************************************************************************/
void f_delete_ticket_timeid(TNODE *head)
{
	if (head == NULL)
		return;

	int de_timeid = 0;
	char cho = '\0';
	TNODE *temp = NULL;
	TNODE *pre = NULL;

	printf("请输入要删除的购票信息的期号：");
	scanf("%d",&de_timeid);
	while(getchar()!='\n')
		;
	printf("确定要删除吗？(y/n)");
	scanf(" %c", &cho);//只取输入中的第一个有效字符
	while(getchar()!='\n')
		;
	if (cho != 'y' && cho != 'Y')
	{
		return;
	}
	while (1)
	{
		pre = search_timeid(head,de_timeid);
		if (pre == NULL)
			break;
		//删除节点
		temp = pre->next;
		pre->next = temp->next;
		free(temp);
	}
	printf("删除成功\n");
	temp = NULL; //防止悬空指针
}


/**************************************************************************************
 * 按追加模式打开文件
 * profit :盈利信息结构体指针
 **************************************************************************************/
void save_profit_txt(PROFIT *profit)
{
	if(profit == NULL)
		return;
	FILE *fp = fopen("ticketfile/profit.txt", "at"); //若打开的文件已存在,追加内容
	if (fp == NULL)
	{
		printf("打开失败\n");
		return;
	}
	//追加信息
	fprintf(fp,"%d\t%s\t%d\t",profit->timeid,profit->type,profit->money);
	fprintf(fp,"%d\t%s\n",profit->total_money,profit->remark);
	fclose(fp);
}






