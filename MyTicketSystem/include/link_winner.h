/******************************************************************************
*程序功能：已开奖彩票信息链表基本操作函数
*作者：lxg
*源程序名：fun.h
*创建日期：2014-4-21
*最后更新日期：2014-4-27
*******************************************************************************/
#ifndef	LINK_WINNER_H
#define LINK_WINNER_H
//文件包含
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//全局变量

typedef struct link_winner
{
	int timeid;//期号
	int zid[4];//4个不同的中奖号码
	char ktime[40];//开奖时间
}WINNER;

//节点定义
typedef struct wnode
{
	WINNER winner;//开奖彩票信息
	struct wnode *next;
}WNODE;


//函数声明
WNODE *create_winner(WINNER *data);//创建一个新结点

WNODE *insert_winner_after(WNODE *head,WINNER *data);//尾部插入一个新节点

void print_winner_all(WNODE *head);//打印已开奖彩票信息链,已按期号排好序

WNODE *search_winner(WNODE *head,int timeid);//查询某一期的开奖信息

void f_search_timeid_win(WNODE *head);//根据期号查询已购彩票信息

void free_all_winner(WNODE *head);//已开奖彩票信息堆内存释放函数(不保留头节点)


#endif/*LINK_WINNER_H*/
