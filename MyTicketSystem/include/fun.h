/***********************
*程序功能：
*作者：lxg
*源程序名：fun.h
*创建日期：2014-4-21
*最后更新日期：2014-4-1
************************/
#ifndef FUN_H
#define FUN_H
//文件包含
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../include/link_ticket.h"
#include "../include/link_user.h"
#include "../include/link_winner.h"
#include "../include/file_deal.h"

typedef struct administer
{
	char adm[20];
	char pwd[20];
	int money;//奖池
}ADMIN;

//营收信息结构体定义
typedef struct profit
{
	int timeid;
	char type[8];
	int money;
	int total_money;
	char remark[30];
}PROFIT;


//函数声明
/************************* 登录与注册 ********************************************/

void admin_check_login(ADMIN *p);//管理员登录

void f_usr_regist(UNODE *head);//用户注册

void user_check_login(UNODE *head);//用户登录

/************************** 用户菜单执行函数 **************************************/

int f_buy_code(TICKET *ticket);//购票号码输入函数

void f_print_buycode(TICKET *ticket);//打印购买的彩票的信息

void buy_ticket(TNODE *thead,UNODE *usr,WNODE *whead);//购票

void f_search_usr(UNODE *usr);//查看个人信息

void f_search_ticket(TNODE *head,UNODE *usr);//查看已购信息

void f_update_usrpwd(UNODE *usr);//修改密码

void f_usr_add_money(UNODE *usr);//追加金额

void f_winner_notice(UNODE *usr,TNODE *thead,WNODE *whead);//中奖信息通知：用户登录时对上一期是否中奖进行消息显示，
								//以及总共中奖金额的统计

/****************************** 金额管理******************************************/

void delay();//摇奖延时

void f_print_wincode(WINNER *win);//打印本期开奖信息

void f_winner(WNODE *whead,TNODE *thead,UNODE *uhead);//摇号并创建开奖信息链表

int f_money_grade(TNODE *temp,int num[4]);//奖金分级函数, 可增加奖池金额函数

void f_money_deal(UNODE *uhead,TNODE *thead,WINNER win);// 金额管理(用户余额，奖池金额，开奖状态，中奖状态，中奖金额）

void save_profit_txt(PROFIT *profit);//追加盈利信息到文件

/***************************** 管理员的菜单行为 ************************************/

void save_admin_txt(ADMIN *admi);//保存管理员信息到文件

void load_admin_txt(ADMIN *admin);//加载管理员信息到全局变量

void f_view_admin(ADMIN *adm);//管理员信息查看

void f_update_adminpwd(ADMIN *admin);//修改管理员密码

void f_admin_update_usrpwd(UNODE *head);//管理员权限下修改彩民密码

void f_admin_add_money(ADMIN *admin);//追加奖池金额

void f_delete_usr(UNODE *head);//某一个删除注册用户

void f_delete_ticket_usr(TNODE *head);//按用户名删除购票信息

void f_delete_ticket_timeid(TNODE *head);//按期号删除购票信息


#endif/*FUN_H*/
