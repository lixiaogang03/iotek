
/************************************************************************
* 程序功能：已购买彩票链表基本操作函数
* 作者：lxg
* 源程序名：link_ticket.c
* 创建日期：2014-4-21
* 最后更新日期：2014-4-27
*************************************************************************/
//文件包含
#include "../include/link_ticket.h"


/*********************************************************************
 * 创建单个空节点
 * data :用户信息结构体指针
 * 返回创建的节点指针
 *******************************************************************/
TNODE *create_ticket(TICKET *data)
{
	if(data == NULL)
	{
		printf("节点指针传入失败\n");
		return NULL;
	}
	//新结点指针
	TNODE *newnode = NULL;
	newnode = (TNODE *)malloc(sizeof(TNODE));
	//检查是否创建成功
	if(newnode == NULL)
	{
		printf("创建内存失败\n");
		return NULL;
	}
	//数据域内容赋值
	newnode->ticket = *data;
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
TNODE *insert_ticket_after(TNODE *head,TICKET *data)
{
	if(head == NULL)
		return NULL;
	//创建一个新节点
	TNODE *newcode = NULL;
	//找到插入的位置
	while(head->next!=NULL)
	{
		head = head->next;
	}
	//数据域
	newcode = create_ticket(data);
	//指针域
	head->next = newcode;

	return newcode;
}


/************************************************************************
 * 打印单个已购彩票信息链
 * tick :单个彩票信息链节点
 ************************************************************************/
void print_oneticket(TNODE *tick)
{
	if(tick == NULL)
		return;
	printf("%s\t%d\t",tick->ticket.uid,tick->ticket.timeid);//账户名 	期号
	printf("%d %d", tick->ticket.buyid[0], tick->ticket.buyid[1]); //购买的号码
	printf(" %d %d\t", tick->ticket.buyid[2], tick->ticket.buyid[3]);
	printf("  %d\t", tick->ticket.bnum);						//购买注数
	printf("%d\t%d\t", tick->ticket.kflag, tick->ticket.zflag);		//开奖标志	中奖标志
	printf("%d\n", tick->ticket.money);						//中奖金额

}


/************************************************************************
 * 打印已购彩票信息链
 * head : 头节点
 ************************************************************************/
void print_ticket_all(TNODE *head)
{
	if(head == NULL)
		return;
	printf("用户名\t期号\t号码\t注数\t开奖\t中奖\t中奖金额\n");
	while(head->next != NULL)
	{
		head = head->next;
		print_oneticket(head);
	}
}


/***************************************************************************
 * 根据账户名（字符串）查找
 * head:头节点指针
 * str[]:要查找的用户名
 * 返回所在节点前一个节点的指针
 ***************************************************************************/
TNODE *search_ticketname(TNODE *head,char str[20])
{
	if(head == NULL)
		return NULL;

	TNODE *pre = NULL;
	while (head->next)
	{
		pre = head;
		head = head->next;
		if (!strcmp(head->ticket.uid,str))
		{
			return pre;
		}
	}
	return NULL;
}


/***************************************************************************
 * 根据账户名查找所有购票信息
 * head ：购票信息链头节点
 **************************************************************************/
void search_usrall_ticket(TNODE *head)
{
	if(head == NULL)
		return;

	TNODE *temp = NULL;
	char usrname[20] = "";

	printf("请输入要查找的用户名：");
	scanf("%s",usrname);
	while(getchar()!='\n')
		;
	printf("用户名\t期号\t号码\t注数\t开奖\t中奖\t中奖金额\n");

	while (1)
	{
		temp = search_ticketname(head,usrname);
		if (temp == NULL)
			return;
		head = temp->next;
		print_oneticket(head);
	}
}


/*************************************************************************
 * 按期号查找购票信息
 * head ：已购票信息链头节点
 * timed :要查找的期号
 *  返回所在节点前一个节点的指针
 ***********************************************************************/
TNODE *search_timeid(TNODE *head,int timeid)
{
	if(head == NULL)
		return NULL;

	TNODE *pre = NULL;
	while (head->next)
	{
		pre = head;
		head = head->next;
		if (head->ticket.timeid == timeid)
		{
			return pre;
		}
	}
	return NULL;
}


/******************************************************************************
 * 根据期号查找所有购票信息
 * head :购票信息链头节点
 ******************************************************************************/
void search_timeid_all(TNODE *head)
{
	if(head == NULL)
		return;
	int timeid = 0;
	TNODE *temp = NULL;
	printf("请输入要查找的期号:");
	scanf("%d",&timeid);
	while(getchar()!='\n')
		;
	printf("用户名\t期号\t号码\t注数\t开奖\t中奖\t中奖金额\n");
	while (1)
	{
		temp = search_timeid(head,timeid);
		if (temp == NULL)
			return;
		head = temp->next;
		print_oneticket(head);
	}
}


/*****************************************************************************
*根据账户排序(选择排序)
*head:头节点
******************************************************************************/
void ticket_name_sort(TNODE *head)
{
	if(head == NULL)
		return;

	TNODE *oldhead = NULL;
	TNODE *min = NULL;//中间变量，存放最小值
	TNODE *p = NULL;//链表中参加比较的数
	TNODE *min_p = NULL;//存放最小值前面的指针
	TNODE *newhead = NULL;//
	TNODE *newtail = NULL;//先链表的尾指针

	oldhead = head;
	head = head -> next;
	while(head != NULL)
	{
		//循环一次，找到一个最小值
		for(min = head,p=head;p->next != NULL;p=p->next)
		{
			if(strcmp(p->next->ticket.uid,min->ticket.uid) < 0)
			{
				min=p->next;//寄存下一个数据所在节点的地址//寄存本次比较较小的数据的地址
				min_p = p;//寄存当前节点地址//寄存当前数据节点的地址
			}
		}
		//找到最小值后，将最小值（min:最小值所在节点的指针）放入新的链表中，采用后向插入法
		if(NULL == newhead)
		{
			newhead = min;
		}
		else
		{
			newtail->next = min;
		}
		newtail = min;
		//找到最小值后，将原链表中的这个值删除
		if(min == head)
		{
			head = head->next;//后移
		}
		else
		{
			min_p->next = min->next;
		}
	}
	//排序完成后，为新的链表的最后一个节点做结束标志
	if(newhead != NULL)
	{
		newtail->next = NULL;
	}
	oldhead->next = newhead;//接到原来的头节点上
}


/*****************************************************************************
*根据中奖金额额排序(选择排序)
*head:头节点
******************************************************************************/
void get_money_sort(TNODE *head)
{
	if(head == NULL)
		return;

	TNODE *oldhead = NULL;
	TNODE *min = NULL;//中间变量，存放最小值
	TNODE *p = NULL;//链表中参加比较的数
	TNODE *min_p = NULL;//存放最小值前面的指针
	TNODE *newhead = NULL;
	TNODE *newtail = NULL;//新链表的尾指针

	oldhead = head;
	head = head -> next;
	//对原链表进行循环，找出最小值
	while(head != NULL)
	{
		//循环一次，找到一个最小值
		for(min = head,p=head;p->next != NULL;p=p->next)
		{
			if(p->next->ticket.money < min->ticket.money)
			{
				min=p->next;
				min_p = p;
			}
		}
		if(NULL == newhead)
		{
			newhead = min;//新节点存放最小值节点的指针
		}
		else
		{
			newtail->next = min;
		}
		newtail = min;
		//找到最小值后，将原链表中的这个值删除
		if(min == head)
		{				//关键步骤,保证head指向的不是被删除过的节点
			head = head->next;
		}
		else
		{
			min_p->next = min->next;
		}
	}
	//排序完成后，为新的链表的最后一个节点做结束标志
	if(newhead != NULL)
	{
		newtail->next = NULL;
	}
	oldhead->next = newhead;
}


/******************************************************************************
 * 已购彩票信息堆内存释放函数(不保留头节点)
 * head:已购彩票信息链表头节点
 * 无返回值
 *******************************************************************************/
void free_all_ticket(TNODE *head)
{
	if(head == NULL)
		return;
	TNODE *pre = NULL;
	//head = head->next;//保留头节点
	while(head != NULL)
	{
		pre = head;//寄存head节点
		head = head->next;//head节点前移
		free(pre);//释放原来head指向的堆内存
	}
	//循环结束后，head为空
	pre = NULL;//防止产生悬空指针
}

