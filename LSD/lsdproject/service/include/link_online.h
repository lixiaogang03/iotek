
#ifndef _LINK_ONLINE_H
#define _LINK_ONLINE_H
/*
 底层链表操作函数
 作者：李晓刚
 时间：2014年5月21日
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//在线用户信息结构体
typedef struct online
{
	char name[20];
	char log_time[30];	
}ONLINE;

//链表节点定义
typedef struct onode
{
	ONLINE online;
	struct onode *next;
}ONODE;

//创建单个空节点
extern ONODE *create_online(ONLINE *data);

//尾部链接一个节点
extern ONODE *insert_online_after(ONODE *head, ONLINE *data);

//打印一个在线用户信息
extern void print_one_online(ONODE *usr);

//打印所有在线用户信息
extern void print_online_all(ONODE *head);

//根据用户名（字符串）查找
extern ONODE *search_online_name(ONODE *head,char str[]);

//按用户名删除购票信息
extern void delete_online_user(ONODE *head,char name[20]);

//用户信息堆内存释放函数(不保留头节点)
extern void free_all_online(ONODE *head);


#endif



