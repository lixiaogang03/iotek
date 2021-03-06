
/*********************************************************************
*程序功能：已开奖彩票信息链表基本操作函数
*作者：lxg
*源程序名：link_winner.c
*创建日期：2014-4-21
*最后更新日期：2014-4-27
**********************************************************************/
//文件包含
#include "../include/link_winner.h"


/*********************************************************************
 *创建单个空节点
 *data :用户信息结构体指针
 *返回创建的节点指针
 *******************************************************************/
WNODE *create_winner(WINNER *data)
{
	if(data == NULL)
	{
		return NULL;
	}
	//新结点指针
	WNODE *newnode = NULL;
	newnode = (WNODE *)malloc(sizeof(WNODE));
	//检查是否创建成功
	if(newnode == NULL)
	{
		printf("创建内存失败\n");
		return NULL;
	}
	//数据域内容赋值
	newnode->winner = *data;
	//指针域内容赋值
	newnode->next = NULL;
	//返回新创建的节点的指针
	return newnode;
}


/**************************************************************************
 *尾部链接一个节点
 *head:链表的头节点指针
 *user:用户信息结构体指针
 *返回新节点指针
 **************************************************************************/
WNODE *insert_winner_after(WNODE *head,WINNER *data)
{
	if(head == NULL)
		return NULL;
	//创建一个新节点
	WNODE *newcode = NULL;
	//找到插入的位置
	while(head->next!=NULL)
	{
		head = head->next;
	}
	//数据域
	newcode = create_winner(data);
	//指针域
	head->next = newcode;

	return newcode;
}


/***************************************************************************
 * 打印某一期的开奖信息
 * win :某一期开奖信息节点
 ***************************************************************************/
void print_onewinner(WNODE *win)
{
	if(win == NULL)
		return;
	printf("%d\t",win->winner.timeid);
	printf("%d %d", win->winner.zid[0], win->winner.zid[1]); //开奖号码
	printf(" %d %d\t\t", win->winner.zid[2], win->winner.zid[3]);
	printf("%s", win->winner.ktime);
}


/***************************************************************************
 * 打印已开奖彩票信息链
 * head :头节点
 **************************************************************************/
void print_winner_all(WNODE *head)
{
	if(head == NULL)
		return;
	printf("期号\t中奖号码\t\t开奖时间\n");
	while(head->next != NULL)
	{
		head = head->next;
		print_onewinner(head);
	}
}


/***************************************************************************
 * 根期号查询开奖信息
 * head:头节点指针
 * timeid:要查找的期号
 * 返回所在节点前一个节点的指针
 ***************************************************************************/
WNODE *search_winner(WNODE *head,int timeid)
{
	if(head == NULL)
		return NULL;

	WNODE *pre = NULL;
	while (head->next)
	{
		pre = head;
		head = head->next;
		if (head->winner.timeid == timeid)
		{
			return pre;
		}
	}
	return NULL;
}


/******************************************************************
 * 根据期号查询开奖信息
 * head : 已开奖信息链头节点
 ****************************************************************/
void f_search_timeid_win(WNODE *head)
{
	if(head == NULL)
		return;
	WNODE *find = NULL;
	int timeid = 0;

	printf("请输入要查询的期号：");
	scanf("%d",&timeid);
	while(getchar()!='\n')
		;
	find = search_winner(head,timeid);
	if(find == NULL)
		return;
	head = find->next;

	printf("期号\t中奖号码\t\t开奖时间\n");
	print_onewinner(head);
	free(find);
}


/******************************************************************************
 * 已开奖彩票信息堆内存释放函数(不保留头节点)
 * head:已开奖彩票信息链表头节点
 * 无返回值
 *******************************************************************************/
void free_all_winner(WNODE *head)
{
	if(head == NULL)
		return;
	WNODE *pre = NULL;
	
	while(head != NULL)
	{
		pre = head;//寄存head节点
		head = head->next;//head节点前移
		free(pre);//释放原来head指向的堆内存
	}
	//循环结束后，head为空
	pre = NULL;//防止产生悬空指针
}

