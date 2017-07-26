/*
 *Function:Multi client TCPserver
 *Author:Mr.Fu
 *Date:2017-5-16
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define MAXLINE 5
#define OPEN_MAX 100
#define LISTENQ 20
#define SERV_PORT 5000
#define INFTIM 1000

int main(int argc, char* argv[])
{
    int i, maxi, listenfd, connfd, sockfd,epfd,nfds, portnumber;
    ssize_t n;
    char line[MAXLINE];
    socklen_t clilen;

    if ( 2 == argc )
    {
        if( (portnumber = atoi(argv[1])) < 0 )
        {
            fprintf(stderr,"Usage:%s portnumber\a\n",argv[0]);
            return 1;
        }
    }
    else
    {
        fprintf(stderr,"Usage:%s portnumber\a\n",argv[0]);
        return 1;
    }

    //声明epoll_event结构体的变量,ev用于注册事件,数组用于回传要处理的事件
    struct epoll_event ev,events[20];
    
    //生成用于处理accept的epoll专用的文件描述符
    epfd=epoll_create(256);
    struct sockaddr_in clientaddr;
    struct sockaddr_in serveraddr;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    //设置套接字选项为SO_REUSEADDR，即socket可重用 (这个套接字选项通知内核，如果端口忙，但TCP状态位于 TIME_WAIT ，可以重用端口)
	int opt=1;
	setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    //设置与要处理的事件相关的文件描述符
    ev.data.fd=listenfd;
    
    //设置要处理的事件类型
    ev.events=EPOLLIN|EPOLLET;

    //注册epoll事件
    epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,&ev);
    bzero(&serveraddr, sizeof(serveraddr));
    
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port=htons(portnumber);
    
    int nRet = bind(listenfd,(struct sockaddr *)&serveraddr, sizeof(serveraddr));
	if(nRet<0)
	{
		printf("bind error!\n");
		return -1;
	}
    listen(listenfd, LISTENQ);
    maxi = 0;
	clilen = sizeof(clientaddr);
    while(1)
    {
        //等待epoll事件的发生
        nfds=epoll_wait(epfd,events,20,500);
        
        //处理所发生的所有事件
        for(i=0;i<nfds;++i)
        {
            if(events[i].data.fd==listenfd)//如果新监测到一个SOCKET用户连接到了绑定的SOCKET端口，建立新的连接。
            {
                connfd = accept(listenfd,(struct sockaddr *)&clientaddr,&clilen);
                if(connfd<0){
                    perror("connfd<0");
                    exit(1);
                }

                char *str = inet_ntoa(clientaddr.sin_addr);
                printf("accapt a connection from %s\n",str);
                //设置用于读操作的文件描述符
                ev.data.fd=connfd;
                
                //设置用于注测的读操作事件
                ev.events=EPOLLIN|EPOLLET;
                //ev.events=EPOLLIN;

                //注册ev
                epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&ev);
            }
            else if(events[i].events&EPOLLIN)//如果是已经连接的用户，并且收到数据，那么进行读入。
            {
                printf("EPOLLIN\n");
                if ( (sockfd = events[i].data.fd) < 0)
                    continue;
                if ( (n = read(sockfd, line, MAXLINE)) < 0) {
                    if (errno == ECONNRESET) {
                        close(sockfd);
                        events[i].data.fd = -1;
                    } else
                        printf("readline error\n");
                } else if (n == 0) {
                    close(sockfd);
                    events[i].data.fd = -1;
                }
                line[n] = '\0';
                printf("read %s\n",line);
                //设置用于写操作的文件描述符
                ev.data.fd=sockfd;
                
                //设置用于注测的写操作事件
                ev.events=EPOLLOUT|EPOLLET;
            }
            else if(events[i].events&EPOLLOUT) // 如果有数据发送
            {
                sockfd = events[i].data.fd;
                write(sockfd, line, n);
                
                //设置用于读操作的文件描述符
                ev.data.fd=sockfd;
                
                //设置用于注测的读操作事件
                ev.events=EPOLLIN|EPOLLET;
                
                //修改sockfd上要处理的事件为EPOLIN
                epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev);
            }
        }
    }
    return 0;
}