
#ifndef _VIEW_H
#define _VIEW_H

/*
 *与输入输出相关的功能函数
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include "../include/link_user.h"
#include "../include/link_online.h"
#include "../include/link_daily.h"

extern UNODE *uhead;
extern ONODE *ohead;
extern DNODE *dhead;


//管理员线程处理函数：帐户名和密码核对
extern void pthread_admin_deal();

//服务器二级菜单(管理员登录成功后)
extern void admin_login();


#endif
