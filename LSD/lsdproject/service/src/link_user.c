

#include "../include/link_user.h"

/*
 * 创建单个空节点
 * data :用户信息结构体指针
 * 返回创建的节点指针
 */
UNODE *create_user(USER *data)
{
	if(data == NULL)
	{
		printf("节点指针传入失败\n");
		return NULL;
	}

	UNODE *newnode = NULL;
	newnode = (UNODE *)malloc(sizeof(UNODE));
	if(newnode == NULL)
	{
		printf("创建内存失败\n");
		return NULL;
	}
	newnode->user = *data;
	newnode->next = NULL;

	return newnode;
}

/*
 *尾部链接一个节点
 *head:链表的头节点指针
 *user:用户信息结构体指针
 *返回新节点指针
 */
UNODE *insert_user_after(UNODE *head,USER *data)
{
	if(head == NULL)
	{
		return NULL;
	}
	UNODE *newcode = NULL;
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

/*
 * 打印某一用户信息
 * usr :用户信息节点指针
 */
void print_oneusr(UNODE *usr)
{
	if(usr == NULL)
		return;
	printf("%s\t%s\n",usr->user.name,usr->user.pwd);
}

/*
 * 打印所有用户信息
 * head:链表头节点
 */
void print_user_all(UNODE *head)
{
	if(head == NULL)
	{
		return;
	}
	printf("用户名\t密码\n");
	while(head->next != NULL)
	{
		head = head->next;
		print_oneusr(head);
	}
}

/*
 * 根据用户名（字符串）查找
 * head:头节点指针
 * str[]:要查找的用户名
 * 返回所在节点前一个节点的指针
 */
UNODE *search_username(UNODE *head,char str[])
{
	if(head == NULL)
	{
		return NULL;
	}
	UNODE *pre = NULL;
	while (head->next)
	{
		pre = head;
		head = head->next;
		if (!strcmp(head->user.name,str))
		{
			return pre;
		}
	}
	return NULL;
}


/*
 * 修改密码
 * usr : 当前登录用户信息链节点
 */
void update_usrpwd(UNODE *usr)
{
	if(usr == NULL)
	{
		return;
	}
	char oldpwd[20] = "";
	char newpwd1[20] = "";
	char newpwd2[20] = "";
	char cho = '\0';

	printf("请输入原来的密码：");
	scanf("%s",oldpwd);
	while(getchar()!='\n')
		;
	if(strcmp(usr->user.pwd,oldpwd))
	{
		printf("输入的密码不正确\n");
		return;
	}
	while(1)
	{
		printf("请输入新的密码：");
		scanf("%s",newpwd1);
		while(getchar()!='\n')
			;
		printf("请再次输入新的密码：");
		scanf("%s",newpwd2);
		while(getchar()!='\n')
			;
		if(!strcmp(newpwd1,newpwd2))
		{
			printf("确定要修改吗？(y/n)");
			scanf(" %c",&cho);
			while(getchar()!='\n')
				;
			if(cho == 'y' || cho == 'Y')
			{
				strcpy(usr->user.pwd,newpwd1);
				return;
			}
		}
		else
		{
			printf("两次密码输入不一致，请重新输入\n");
		}
	}
}

/*
 * 用户信息堆内存释放函数(不保留头节点)
 * head:用户信息链表头节点
 */
void free_all_usr(UNODE *head)
{
	if(head == NULL)
	{
		return;
	}
	UNODE *pre = NULL;
	while(head != NULL)
	{
		pre = head;//寄存head节点
		head = head->next;//head节点前移
		free(pre);//释放原来head指向的堆内存
	}
	pre = NULL;
}

/*
 * 保存用户信息链
 * head:用户信息链头节点
 */
void save_user_txt(UNODE *head)
{
	if(head == NULL)
	{
		return;
	}
	FILE *fp = fopen("data/user.txt","wt");
	if(fp == NULL)
	{
		printf("打开失败\n");
		return;
	}
	//只向文件中写入用户信息的内容
	while(head->next)
	{
		head = head->next;
		fprintf(fp,"%s\t%s\n",head->user.name,head->user.pwd);
	}
	fclose(fp);
}

/*
 *从文件加载所有注册用户信息
 *head:用户信息链头节点
 *无返回
 */
void load_all_user(UNODE *head)
{
	FILE *fp = fopen("data/user.txt","rt");
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
	while(1)
	{
		//fgets(temp->name,20,fp);
		res = fscanf(fp,"%s\t%s\n",temp->name,temp->pwd);
		if(res <=0)
		{
			break;
		}
		insert_user_after(head,temp);//将寄存的信息读入新创建的链表节点
	}
	//print_user_all(head);
	free(temp);
	fclose(fp);
}

	
