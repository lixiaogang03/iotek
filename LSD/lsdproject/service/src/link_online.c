/*
 在线用户链表操作函数源文件
 作者：lxg
 时间：2014年5月22日
*/
#include "../include/link_online.h"
/*
 * 创建单个空节点
 * data :在线用户信息结构体指针
 * 返回创建的节点指针
 */
ONODE *create_online(ONLINE *data)
{
	if(data == NULL)
	{
		printf("节点指针传入失败\n");
		return NULL;
	}

	ONODE *newnode = NULL;
	newnode = (ONODE *)malloc(sizeof(ONODE));
	if(newnode == NULL)
	{
		printf("创建内存失败\n");
		return NULL;
	}
	newnode->online = *data;
	newnode->next = NULL;

	return newnode;
}

/*
 *尾部链接一个节点
 *head:链表的头节点指针
 *data:在线用户信息结构体指针
 *返回新节点指针
 */
ONODE *insert_online_after(ONODE *head,ONLINE *data)
{
	if(head == NULL)
	{
		return NULL;
	}
	ONODE *newcode = NULL;
	while(head->next!=NULL)
	{
		head = head->next;
	}
	//数据域
	newcode = create_online(data);
	//指针域
	head->next = newcode;

	return newcode;
}


/*
 * 打印某一用户信息
 * usr :在线用户信息节点指针
 */
void print_one_online(ONODE *usr)
{
	if(usr == NULL)
		return;
	printf("%s\t%s\n",usr->online.name,usr->online.log_time);
}


/*
 * 打印所有在线用户信息
 * head:链表头节点
 */
void print_online_all(ONODE *head)
{
	if(head == NULL)
	{
		return;
	}
	printf("用户名\t上线时间\n");
	while(head->next != NULL)
	{
		head = head->next;
		print_one_online(head);
	}
}

/*
 * 根据用户名（字符串）查找
 * head:头节点指针
 * str[]:要查找的用户名
 * 返回所在节点前一个节点的指针
 */
ONODE *search_online_name(ONODE *head,char str[])
{
	if(head == NULL)
	{
		return NULL;
	}
	ONODE *pre = NULL;
	while (head->next)
	{
		pre = head;
		head = head->next;
		if (!strcmp(head->online.name,str))
		{
			return pre;
		}
	}
	return NULL;
}


/*
 * 按用户名删除在线用户
 * head:在线用户信息链头节点
 * name:要删除的在线用户名
 */
void delete_online_user(ONODE *head,char name[20])
{
	if(head == NULL)
	{
		return;
	}
	
	ONODE *temp = NULL;
	ONODE *pre = NULL;
	while(1)
	{
		pre = search_online_name(head,name);
		if (pre == NULL)
		{
			break;
		}
		//删除
		temp = pre->next;
		pre->next = temp->next;
		free(temp);
	}
	//printf("删除成功\n");
	temp = NULL; 
}



/*
 * 用户信息堆内存释放函数(不保留头节点)
 * head:在线用户信息链表头节点
 */
void free_all_online(ONODE *head)
{
	if(head == NULL)
	{
		return;
	}
	ONODE *pre = NULL;
	while(head != NULL)
	{
		pre = head;//寄存head节点
		head = head->next;//head节点前移
		free(pre);//释放原来head指向的堆内存
	}
	pre = NULL;
}






