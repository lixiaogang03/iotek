
#ifndef LINK_DAILY_H
#define LINK_DAILY_H

/*
 底层链表操作函数
 作者：李晓刚
 时间：2014年5月21日
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//日志信息结构体
typedef struct daily
{
	char name[20];
	//char IP[20];//登录IP
	char log_time[30];//登录时间
	char off_time[30];//下线时间
	char off_state[10];//正常退出和异常退出
}DAILY;
//链表节点定义
typedef struct dnode
{
	DAILY daily;
	struct dnode *next;
}DNODE;

//创建一个新节点
extern DNODE *create_daily(DAILY *data);

//尾部链接一个节点
extern DNODE *insert_daily_after(DNODE *head,DAILY *data);

//打印某一日志信息
extern void print_one_daily(DNODE *usr);

//打印所有日志信息
extern void print_daily_all(DNODE *head);

//根据用户名（字符串）查找
extern DNODE *search_daily_name(DNODE *head,char str[]);

//用户信息堆内存释放函数(不保留头节点)
extern void free_all_daily(DNODE *head);

//保存日志信息链
extern void save_daily_txt(DNODE *head);

//加载日志信息链
extern void load_all_daily(DNODE *head);



#endif
