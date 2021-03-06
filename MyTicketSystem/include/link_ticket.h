
/**********************************************************************
*程序功能：已购彩票信息链底层函数
*作者：lxg
*源程序名：link_ticket.h
*创建日期：2014-4-21
*最后更新日期：2014-4-27
***********************************************************************/
#ifndef LINK_TICKET_H
#define LINK_TICKET_H
//文件包含
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//全局变量
typedef struct link_ticket
{
	char uid[20];//用户名
	int timeid;//期号
	int buyid[4];//购买号码4个不同的号码
	int bnum;//购买注数
	int kflag;//开奖状态
	int zflag;//中奖状态
	int money;//中奖金额
}TICKET;

//链表节点定义
typedef struct tnode
{
	TICKET ticket;//已购买彩票信息
	struct tnode *next;
}TNODE;


//函数声明

TNODE *create_ticket(TICKET *data);//创建一个新节点

TNODE *insert_ticket_after(TNODE *head,TICKET *data);//尾部插入一个新结点

void print_oneticket(TNODE *tick);//打印单个已购彩票信息链

void print_ticket_all(TNODE *head);//打印已购彩票信息链

/***********************************************************************/

TNODE *search_ticketname(TNODE *head,char str[]);//根据账户名查找

void search_usrall_ticket(TNODE *head);//根据账户名查找所有购票信息

TNODE *search_timeid(TNODE *head,int timeid);//根据购买期号查找

void search_timeid_all(TNODE *head);//根据期号查找所有购票信息

/************************************************************************/

void ticket_name_sort(TNODE *head);//根据账户名排序

void get_money_sort(TNODE *head);//根据中奖金额排序

void free_all_ticket(TNODE *head);//已购彩票信息堆内存释放函数(不保留头节点)

#endif/*LINK_TICKET_H*/

