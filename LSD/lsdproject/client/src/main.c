/*
 *�ͻ������������
 */

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "../include/fun.h"

int sockfd = -1;		//����һ���׽���

int fd[2] = {0};		//����ܵ����ļ�������Ϊȫ�ֱ���

char login_user[20] = "";	//�Ĵ��¼���û���


int main(int argc,char **argv)
{
	if(signal(SIGALRM,sighandlle) == SIG_ERR)
	{
		printf("ע���ź�ʧ��\n");
	}
	//ע���ź�
	if(signal(SIGINT,sighandlle) == SIG_ERR)
	{
		printf("SIGINT�ź�ע��ʧ��\n");
	}
	if(signal(SIGTSTP,sighandlle) == SIG_ERR)
	{
		printf("SIGTSTP�ź�ע��ʧ��\n");
	}
	//�����ܵ�
	pipe(fd);

	struct sockaddr_in ser;         //����һ����ַ��Ϣ�ṹ��
	memset(&ser,0,sizeof(ser));
	socket_init(&sockfd, &ser);
	//�������������������
	if(connect(sockfd,(struct sockaddr *)&ser,sizeof(struct sockaddr_in)) < 0)
	{
		printf("����ʧ��\n");
		return 1;
	}
		
	/*
	 * ����һ���µ��̣߳����̸߳������׽���д������ ����һ���̸߳�����׽��ֶ����������Ļ�Ӧ
         * Ȼ���������ܵ������̴߳ӹܵ���ȡ��������Ӧ���������׽���д���µ�����
         */
	pthread_t new_thread;
	create_new_pthread(&new_thread,&sockfd);
	//��ʾ�˵�
        client_menu(&sockfd);

	return 0;
}






