/********************************************************************
*程序功能：用户信息链表底层函数
*作者：lxg
*源程序名：fun.h
*创建日期：2014-4-21
*最后更新日期：2014-4-27
*********************************************************************/
#ifndef	LINK_USER_H
#define LINK_USER_H
//文件包含
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//全局变量
typedef struct link_user
{
	char uid[20];//用户名
	char pwd[20];//用户密码
	int money;//余额
}USER;

//节点
typedef struct unode
{
	USER user;
	struct unode *next;
}UNODE;

//函数声明
UNODE *create_user(USER *data);//创建一个新结点

UNODE *insert_user_after(UNODE *head,USER *data);//尾部插入一个新节点

void print_oneusr(UNODE *usr);//打印一个彩民信息

void print_user_all(UNODE *head);//打印用户信息链

UNODE *search_username(UNODE *head,char str[]);//根据账户名查找

void search_usrname_one(UNODE *head);//根据账户查询某一彩民的信息（账户唯一）

void usr_name_sort(UNODE *head);//根据账户名排序

void usr_money_sort(UNODE *head);//根据账户余额排序

void free_all_usr(UNODE *head);//用户信息堆内存释放函数(不保留头节点)

#endif/*LINK_USER_H*/
