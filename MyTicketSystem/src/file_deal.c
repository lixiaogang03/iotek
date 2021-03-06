
/*******************************************************************************
 * file_deal.c
 * 文件处理
 *  Created on: 2014年4月27日
 *      Author: lxg
 *******************************************************************************/
#include "../include/file_deal.h"


/********************************************************************************
 * 保存用户信息链
 * head:用户信息链头节点
 ********************************************************************************/
void save_user_txt(UNODE *head)
{
	if(head == NULL)
		return;

	FILE *fp = fopen("ticketfile/user.txt","wt");
	if(fp == NULL)
	{
		printf("打开失败\n");
		return;
	}
	//只向文件中写入用户信息的内容
	do
	{
		head = head->next;
		fprintf(fp,"%s\t%s\t%d\n",head->user.uid,head->user.pwd,head->user.money);
	}while(head->next);
	fclose(fp);
}


/****************************************************************************************
 * 将用户信息装载到堆内存链表
 * head :用户信息链头节点
 ****************************************************************************************/
void load_user_txt(UNODE *head)
{
	if(head == NULL)
		return;

	FILE *fp = fopen("ticketfile/user.txt","rt");
	if(fp == NULL)
	{
		printf("打开失败\n");
		return;
	}
	//寄存用户信息结构体
	USER *temp = NULL;
	temp = (USER *)malloc(sizeof(USER));
	if(temp == NULL)
	{
		printf("创建内存失败\n");
		return;
	}
	//结构体初始化
	memset(temp,0,sizeof(USER));
	int res = 0;//文件末尾标志
	do
	{
		res = fscanf(fp,"%s\t%s\t%d\n",temp->uid,temp->pwd,&temp->money);
		if(res <=0)
			break;
		insert_user_after(head,temp);//将寄存的信息读入新创建的链表节点
	} while (1);
	free(temp);
	fclose(fp);
}


/*************************************************************************************
 * 保存已购彩票信息链到文件ticket.txt
 * head:已购彩票信息链头节点
 *************************************************************************************/
void save_ticket_txt(TNODE *head)
{
	if(head == NULL)
		return;

	FILE *fp = fopen("ticketfile/ticket.txt","wt");
	if(fp == NULL)
	{
		printf("打开失败\n");
		return;
	}
	//只向文件中写入用户信息的内容
	while(head->next)
	{
		head = head->next;
		fprintf(fp,"%s\t%d\t",head->ticket.uid,head->ticket.timeid);
		fprintf(fp,"%d %d",head->ticket.buyid[0],head->ticket.buyid[1]);
		fprintf(fp," %d %d\t",head->ticket.buyid[2],head->ticket.buyid[3]);
		fprintf(fp,"%d\t%d\t",head->ticket.bnum,head->ticket.kflag);
		fprintf(fp,"%d\t%d\n",head->ticket.zflag,head->ticket.money);
	}
	fclose(fp);
}

/************************************************************************************
 * 装载已购彩票信息链
 * head :已购彩票信息链头节点
 ************************************************************************************/
void load_ticket_txt(TNODE *head)
{
	if(head == NULL)
		return;

	FILE *fp = fopen("ticketfile/ticket.txt", "rt");
	if (fp == NULL)
	{
		printf("打开失败\n");
		return;
	}
	//寄存已购彩票信息结构体
	TICKET *temp = NULL;
	temp = (TICKET *) malloc(sizeof(TICKET));
	if (temp == NULL)
	{
		printf("创建内存失败\n");
		return;
	}
	//结构体初始化
	memset(temp, 0, sizeof(TICKET));
	int res = 0; //文件末尾标志
	do
	{
		fscanf(fp,"%s\t%d\t",temp->uid,&temp->timeid);
		fscanf(fp,"%d %d",&temp->buyid[0],&temp->buyid[1]);
		fscanf(fp," %d %d\t",&temp->buyid[2],&temp->buyid[3]);
		fscanf(fp,"%d\t%d\t",&temp->bnum,&temp->kflag);
		res = fscanf(fp,"%d\t%d\n",&temp->zflag,&temp->money);
		if (res <= 0)
			break;
		insert_ticket_after(head,temp); //将寄存的信息读入新创建的链表节点
	} while (1);
	free(temp);
	fclose(fp);
}


/*********************************************************************************
 * 开奖信息保存成winner.txt
 * head:已开奖信息链头节点
 *********************************************************************************/
void save_winner_txt(WNODE *head)
{
	if(head == NULL)
		return;

	FILE *fp = fopen("ticketfile/winner.txt", "wt"); 
	if (fp == NULL)
	{
		printf("打开失败\n");
		return;
	}
	//写入开奖信息的内容
	while (head->next)
	{
		head = head->next;
		fprintf(fp,"%d\t",head->winner.timeid);
		fprintf(fp,"%d %d ",head->winner.zid[0],head->winner.zid[1]);
		fprintf(fp,"%d %d\t",head->winner.zid[2],head->winner.zid[3]);
		fprintf(fp,"%s",head->winner.ktime);//自带回车符
	}
	fclose(fp);
}


/*********************************************************************************
 * 加载已开奖信息到内存
 * head:已开奖信息链头节点
 *********************************************************************************/
void load_winner_txt(WNODE *head)
{
	if(head == NULL)
		return;

	FILE *fp = fopen("ticketfile/winner.txt", "rt");
	if (fp == NULL)
	{
		printf("打开失败\n");
		return;
	}
	//寄存开奖信息结构体
	WINNER *temp = NULL;
	temp = (WINNER *) malloc(sizeof(WINNER));
	if (temp == NULL)
	{
		printf("创建内存失败\n");
		return;
	}
	//结构体初始化
	memset(temp, 0, sizeof(WINNER));
	int res = 0; //文件末尾标志
	do {
		res = fscanf(fp,"%d\t",&temp->timeid);
		fscanf(fp,"%d %d ", &temp->zid[0], &temp->zid[1]);
		fscanf(fp,"%d %d\t", &temp->zid[2], &temp->zid[3]);
		fgets(temp->ktime,sizeof(temp->ktime),fp);
		if (res <= 0)
			break;
		insert_winner_after(head,temp); //将寄存的信息读入新创建的链表节点

	} while (1);
	free(temp);
	fclose(fp);
}









