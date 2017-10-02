/*************************************************************************
 
  
  > File Name: cli.c
  > Author: 许四杰
  > Mail: xusijie1211@163.com 
  > Created Time: 2016年07月12日 星期二 14时48分32秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <string.h> 
#include <sys/types.h>   
#include<sys/socket.h>
#include<arpa/inet.h>
#include <errno.h> 
int main(int argc, const char *argv[])
{
	int sock_fd;
	char buf[200];
	if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket error");
		exit(-1);
	}

	struct sockaddr_in ser_addr;
	memset(&ser_addr, 0, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(8888);
	ser_addr.sin_addr.s_addr = inet_addr("192.168.5.102");

	socklen_t len;
	len = sizeof(ser_addr);
		printf("connect error");
	if(connect(sock_fd, (struct sockaddr *)&ser_addr, len) < 0)
	{
		perror("connect error");
		exit(-1);
	}

		printf("connect ok");



	while(1)
	{
		memset(buf, 0, sizeof(buf));
		printf("please into->");
		scanf("%s", buf);
		getchar();
		if(send(sock_fd, buf, sizeof(buf), 0) < 0)
		{
			perror("send error");
			exit(-1);
		}
	}
	return 0;
}
