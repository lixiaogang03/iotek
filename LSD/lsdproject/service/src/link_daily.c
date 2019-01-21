/*
 日志链表操作函数
 作者：lxg
 时间：2014年5月22日
*/

#include "../include/link_daily.h"

/*
 * 创建单个空节点
 * data :日志信息结构体指针
 * 返回创建的节点指针
 */
DNODE *create_daily(DAILY *data)
{
	if(data == NULL)
	{
		printf("节点指针传入失败\n");
		return NULL;
	}

	DNODE *newnode = NULL;
	newnode = (DNODE *)malloc(sizeof(DNODE));
	if(newnode == NULL)
	{
		printf("创建内存失败\n");
		return NULL;
	}
	newnode->daily = *data;
	newnode->next = NULL;

	return newnode;
}


/*
 *尾部链接一个节点
 *head:链表的头节点指针
 *daily:日志信息结构体指针
 *返回新节点指针
 */
DNODE *insert_daily_after(DNODE *head,DAILY *data)
{
	if(head == NULL)
	{
		return NULL;
	}
	DNODE *newcode = NULL;
	while(head->next!=NULL)
	{
		head = head->next;
	}
	
	newcode = create_daily(data);
	head->next = newcode;

	return newcode;
}


/*
 * 打印某一日志信息
 * usr :日志信息节点指针
 */
void print_one_daily(DNODE *usr)
{
	if(usr == NULL)
	{
		return;
	}
	printf("%s\t%s\t",usr->daily.name,usr->daily.log_time);
	printf("%s\t%s\n",usr->daily.off_time,usr->daily.off_state);
}


/*
 * 打印所有日志信息
 * head:链表头节点
 */
void print_daily_all(DNODE *head)
{
	if(head == NULL)
	{
		return;
	}
	printf("用户名\t登陆时间\t\t\t下线时间\t\t下线状态\n");
	while(head->next != NULL)
	{
		head = head->next;
		print_one_daily(head);
	}
}

/*
 * 根据用户名（字符串）查找
 * head:头节点指针
 * str[]:要查找的用户名
 * 返回所在节点前一个节点的指针
 */
DNODE *search_daily_name(DNODE *head,char str[])
{
	if(head == NULL)
	{
		return NULL;
	}
	DNODE *pre = NULL;
	while (head->next)
	{
		pre = head;
		head = head->next;
		if (!strcmp(head->daily.name,str))
		{
			return pre;
		}
	}
	return NULL;
}

/*
 * 日志信息堆内存释放函数(不保留头节点)
 * head:日志信息链表头节点
 */
void free_all_daily(DNODE *head)
{
	if(head == NULL)
	{
		return;
	}
	DNODE *pre = NULL;
	while(head != NULL)
	{
		pre = head;//寄存head节点
		head = head->next;//head节点前移
		free(pre);//释放原来head指向的堆内存
	}
	pre = NULL;
}


/*
 * 保存日志信息链
 * head:日志信息链头节点
 */
void save_daily_txt(DNODE *head)
{
	if(head == NULL)
	{
		return;
	}
	FILE *fp = fopen("data/daily.txt","wt");
	if(fp == NULL)
	{
		printf("打开失败\n");
		return;
	}
	//只向文件中写入用户信息的内容
	while(head->next)
	{
		head = head->next;
		fprintf(fp,"%s\t",head->daily.name);
		fprintf(fp,"%s\t%s\t%s\n",head->daily.log_time,head->daily.off_time,head->daily.off_state);

	}
	fclose(fp);
}

/*
 *从文件加载所有日志信息
 *head:日志信息链头节点
 *无返回
 */
void load_all_daily(DNODE *head)
{
	FILE *fp = fopen("data/daily.txt","rt");
	if(fp == NULL)
	{
		printf("打开失败\n");
		return;
	}
	//寄存用户信息结构体
	DAILY *temp = NULL;
	temp = (DAILY *)malloc(sizeof(DAILY));
	if(temp == NULL)
	{
		printf("创建内存失败\n");
		return;
	}
	time_t curtime = time(NULL);
	//结构体初始化
	memset(temp,0,sizeof(DAILY));
	int res = 0;//文件末尾标志
	while(1)
	{
		//fgets(temp->name,20,fp);
		fscanf(fp,"%s\t",temp->name);
		fgets(temp->log_time,strlen(ctime(&curtime)),fp);
		fscanf(fp,"\t");
		fgets(temp->off_time,strlen(ctime(&curtime)),fp);
		fscanf(fp,"\t");
		res = fscanf(fp,"%s\n",temp->off_state);
		if(res <=0)
		{
			break;
		}
		insert_daily_after(head,temp);//将寄存的信息读入新创建的链表节点
	}
	//print_daily_all(head);
	free(temp);
	fclose(fp);
}




