
#ifndef LINK_USER_H
#define LINK_USER_H
/*
 底层链表操作函数
 作者：李晓刚
 时间：2014年5月21日
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
底层三条链表数据结构
	1、所有用户信息链：用户名 、密码
	2、在线用户信息链：用户名、登录时间、登录IP
	3、日志链表：用户名、登录IP、登录时间、下线时间、是否正常下线
*/

//所有用户信息结构体
typedef struct user
{
	char name[20];
	char pwd[20];
}USER;

//链表节点定义
typedef struct unode
{
	USER user;
	struct unode *next;
}UNODE;

//创建单个空节点
extern UNODE *create_user(USER *data);

//尾部链接一个节点
extern UNODE *insert_user_after(UNODE *head,USER *data);

//打印某一用户信息
extern void print_oneusr(UNODE *usr);

//打印所有用户信息
extern void print_user_all(UNODE *head);

//根据用户名（字符串）查找
extern UNODE *search_username(UNODE *head,char str[]);

//修改密码
extern void update_usrpwd(UNODE *usr);

//用户信息堆内存释放函数(不保留头节点)
extern void free_all_usr(UNODE *head);

//保存用户信息链
extern void save_user_txt(UNODE *head);

//从文件加载所有注册用户信息
extern void load_all_user();


#endif


