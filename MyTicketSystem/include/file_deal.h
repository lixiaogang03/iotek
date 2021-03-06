/********************************************************************************
 * file_deal.h
 *
 *  Created on: 2014年4月23日
 *      Author: lxg
 ********************************************************************************/

#ifndef FILE_DEAL_H_
#define FILE_DEAL_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/fun.h"
#include "../include/menu.h"


//函数声明
void save_user_txt(UNODE *head);//保存为user.txt文件

void load_user_txt(UNODE *head);//装载用户信息到内存

void save_ticket_txt(TNODE *head);//保存已购彩票信息

void load_ticket_txt(TNODE *head);//装载已购彩票信息

void save_winner_txt(WNODE *head);//保存已开奖信息到文件

void load_winner_txt(WNODE *head);//加载已开奖信息岛内存



#endif /* FILE_DEAL_H_ */
