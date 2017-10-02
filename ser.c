#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <string.h> 
#include <sys/types.h>   
#include<arpa/inet.h>
#include<sys/socket.h>
#include <errno.h> 
int main(int argc, const char *argv[])
{
	int sock_fd, cli_fd;
	char buf[200];
	socklen_t len;
	struct sockaddr_in ser_addr, cli_addr;
	if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{

		perror("SOCKET");
		exit(-1);
	}

	memset(&ser_addr, 0, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(8888);
	ser_addr.sin_addr.s_addr = inet_addr("192.168.5.102");
	if(bind(sock_fd, (struct sockaddr *)&ser_addr, sizeof(ser_addr)) < 0)
	{
		perror("BIND");
		exit(-1);
	}

	printf("bind ok \n");
	if(listen(sock_fd, 5) < 0)
	{
		perror("listen error");
		exit(-1);
	}
	printf("listen\n");
	len = sizeof(cli_addr);
	if((cli_fd =  accept(sock_fd, (struct sockaddr *)&cli_addr, &len)) < 0)
	{
		perror("accept error");
		exit(-1);
	}
	printf("accept ok....\n");

	while(1)
	{
		memset(buf, 0, sizeof(buf));
		if(recv(cli_fd, buf, sizeof(buf), 0) <0)
		{
			perror("recv error");
			exit(-1);
		}
		printf("revc = %s\n", buf);
	}
	return 0;
}
