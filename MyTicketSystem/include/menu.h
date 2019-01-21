/**********************************************************************
*程序功能：各级菜单函数
*作者：lxg
*源程序名：menu.h
*创建日期：2014-4-21
*最后更新日期：2014-4-27
***********************************************************************/
#ifndef MENU_H
#define MENU_H
//文件包含
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/fun.h"


//函数声明金额
void sys_login();  //一级菜单

void admin_login(); //管理员登陆->二级菜单

void user_login(); //彩民登陆->二级菜单

void admin_view();//管理员登陆->查看信息->三级菜单

void admin_update();//管理员登陆->修改信息->三级菜单

void admin_delate();//管理员登陆->删除信息->三级菜单

void admin_view_lottery();//管理员登陆->查看信息->彩票信息->四级菜单

void admin_view_user();//管理员登陆->查看信息->彩民信息->四级菜单

void admin_view_buy();//管理员登陆->查看信息->购票信息->四级菜单


#endif


