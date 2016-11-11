#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#define MAXLINE 4096
#define Default_port 8000

int main(int argc,char** argv){
	int sock_fd,n,connect_fd;
	struct sockaddr_in servaddr; 
	char buf[MAXLINE];
	//init socket
	if((sock_fd=socket(AF_INET,SOCK_STREAM,0))<0){
		printf("socket init is error");
		exit(1);
	}
	//init
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(Default_port);

	if(bind(sock_fd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
		printf("socket bind is error");
		exit(1);
	}

	if(listen(sock_fd,10)<0){
		printf("listen is error");
		exit(1);
	}
	while(1){
                struct sockaddr_in client_addr;
                socklen_t length = sizeof(client_addr);

		if((connect_fd=accept(sock_fd,(struct sockaddr*)&client_addr,&length))<0){
			printf("accept is error");
			continue;
		}
		n=recv(connect_fd,buf,MAXLINE,0);
		if(!fork()){
			if(send(connect_fd,"Welcome to server\n",30,0)<0)
			  printf("send is error");
			close(connect_fd);
			exit(0);
		}
		buf[n]='\0';
		printf("receive data is %s\n",buf);
		close(connect_fd);
	}
	close(sock_fd);
}	
