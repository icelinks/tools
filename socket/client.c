#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#define Default_port 8000
#define MAXLINE 4096
#define S_ip "127.0.0.1"

int main(int argc,char **argv){
	int sock_fd,n,recv_fd;
	struct sockaddr_in servaddr;
	char sendline[MAXLINE],recvline[MAXLINE];
	char buf[MAXLINE];

	if((sock_fd=socket(AF_INET,SOCK_STREAM,0))<0){
		printf("socket is error");
		exit(0);
	}

	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(Default_port);
	servaddr.sin_addr.s_addr=inet_addr(S_ip);

	if(connect(sock_fd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
		printf("connect is error %d",errno);
		exit(0);
	}

	fgets(sendline,MAXLINE,stdin);
	if(send(sock_fd,sendline,strlen(sendline),0)<0){
		printf("send is error");
		exit(0);
	}
	if((recv_fd=recv(sock_fd,buf,MAXLINE,0))==-1){
		printf("recv is error");
		exit(1);
	}
	buf[recv_fd]='\0';
	printf("received: %s",buf);
	close(sock_fd);
	exit(0);
}
