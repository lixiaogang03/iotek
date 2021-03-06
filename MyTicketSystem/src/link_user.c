/*********************************************************************
*程序功能：历史注册用户信息链表基本操作函数
*作者：lxg
*源程序名：link_user.h
*创建日期：2014-4-21
*最后更新日期：2014-4-21
*********************************************************************/
//文件包含
#include "../include/link_user.h"

/*********************************************************************
 *创建单个空节点
 *data :用户信息结构体指针
 *返回创建的节点指针
 ********************************************************************/
UNODE *create_user(USER *data)
{
	if(data == NULL)
	{
		printf("节点指针传入失败\n");
		return NULL;
	}
	//新结点指针
	UNODE *newnode = NULL;
	newnode = (UNODE *)malloc(sizeof(UNODE));
	//检查是否创建成功
	if(newnode == NULL)
	{
		printf("创建内存失败\n");
		return NULL;
	}
	//数据域内容赋值
	newnode->user = *data;
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
UNODE *insert_user_after(UNODE *head,USER *data)
{
	if(head == NULL)
		return NULL;
	//创建一个新节点
	UNODE *newcode = NULL;
	//找到插入的位置
	while(head->next!=NULL)
	{
		head = head->next;
	}
	//数据域
	newcode = create_user(data);
	//指针域
	head->next = newcode;

	return newcode;
}


/************************************************************************
 * 打印某一彩民信息
 * usr :彩民信息节点指针
 ************************************************************************/
void print_oneusr(UNODE *usr)
{
	if(usr == NULL)
		return;
	printf("%s\t%s\t%d\n",usr->user.uid,usr->user.pwd,usr->user.money);
}


/**************************************************************************
 * 打印链表内容
 * head:链表头节点
 **************************************************************************/
void print_user_all(UNODE *head)
{
	if(head == NULL)
		return;
	printf("用户名\t密码\t余额(元)\n");
	while(head->next != NULL)
	{
		head = head->next;
		print_oneusr(head);
	}
}


/***************************************************************************
 * 根据账户名（字符串）查找
 * head:头节点指针
 * str[]:要查找的用户名
 * 返回所在节点前一个节点的指针
 ***************************************************************************/
UNODE *search_username(UNODE *head,char str[])
{
	if(head == NULL)
		return NULL;

	UNODE *pre = NULL;
	while (head->next)
	{
		pre = head;
		head = head->next;
		if (!strcmp(head->user.uid,str))
		{
			return pre;
		}
	}
	return NULL;
}


/*************************************************************************************
 * 根据账户查询某一彩民的信息（账户唯一）
 * head :用户信息链头节点
 *************************************************************************************/
void search_usrname_one(UNODE *head)
{
	if(head == NULL)
		return;

	char usrname[20] = "";
	UNODE *temp = NULL;

	printf("请输入要查询的用户名：");
	scanf("%s",usrname);
	while(getchar()!='\n')
		;

	temp = search_username(head,usrname);
	if(temp == NULL)
	{
		printf("要查找的用户不存在\n");
		return;
	}
	printf("用户名\t密码\t余额(元)\n");
	print_oneusr(temp->next);
}


/*********************************************************************************
*根据账户排序(选择排序)
*head:头节点
**********************************************************************************/
void usr_name_sort(UNODE *head)
{
	if(head == NULL)
		return;
	UNODE *oldhead = NULL;
	UNODE *min = NULL;//中间变量，存放最小值
	UNODE *p = NULL;//链表中参加比较的数
	UNODE *min_p = NULL;//存放最小值前面的指针
	UNODE *newhead = NULL;//
	UNODE *newtail = NULL;//先链表的尾指针

	oldhead = head;
	head = head -> next;
	//对原链表进行循环，找出最小值
	while(head != NULL)
	{
		//循环一次，找到一个最小值
		for(min = head,p=head;p->next != NULL;p=p->next) //判断p是否到了链表尾部，p前移一个节点
		{
			if(strcmp(p->next->user.uid,min->user.uid) < 0)
			{
				min=p->next;
				min_p = p;
			}
		}		      
		//找到最小值后，将最小值（min:最小值所在节点的指针）放入新的链表中，采用后向插入法
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
		{					//关键步骤,保证head指向的不是被删除过的节点
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
	oldhead->next = newhead;
}


/**********************************************************************************
*根据余额排序(选择排序)
*head:头节点
***********************************************************************************/
void usr_money_sort(UNODE *head)
{
	if(head == NULL)
		return;
	UNODE *oldhead = NULL;
	UNODE *min = NULL;//中间变量，存放最小值
	UNODE *p = NULL;//链表中参加比较的数
	UNODE *min_p = NULL;//存放最小值前面的指针
	UNODE *newhead = NULL;//
	UNODE *newtail = NULL;//先链表的尾指针

	oldhead = head;
	head = head -> next;
	while(head != NULL)
	{
		for(min = head,p=head;p->next != NULL;p=p->next)
		{
			if(p->next->user.money<min->user.money)
			{
				min=p->next;
				min_p = p;
			}
		}
		if(NULL == newhead)
		{
			newhead = min;
		}
		else
		{
			newtail->next = min;
		}
		newtail = min;
		if(min == head)
		{
			head = head->next;
		}
		else
		{
			min_p->next = min->next;

		}
	}
	if(newhead != NULL)
	{
		newtail->next = NULL;
	}
	oldhead->next = newhead;
}


/******************************************************************************
 * 用户信息堆内存释放函数(不保留头节点)
 * head:用户信息链表头节点
 * 无返回值
 *******************************************************************************/
void free_all_usr(UNODE *head)
{
	if(head == NULL)
		return;
	UNODE *pre = NULL;
	
	while(head != NULL)
	{
		pre = head;//寄存head节点
		head = head->next;//head节点前移
		free(pre);//释放原来head指向的堆内存
	}
	pre = NULL;
}





