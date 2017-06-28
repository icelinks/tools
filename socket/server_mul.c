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

    //����epoll_event�ṹ��ı���,ev����ע���¼�,�������ڻش�Ҫ������¼�
    struct epoll_event ev,events[20];
    
    //�������ڴ���accept��epollר�õ��ļ�������
    epfd=epoll_create(256);
    struct sockaddr_in clientaddr;
    struct sockaddr_in serveraddr;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    //�����׽���ѡ��ΪSO_REUSEADDR����socket������ (����׽���ѡ��֪ͨ�ںˣ�����˿�æ����TCP״̬λ�� TIME_WAIT ���������ö˿�)
	int opt=1;
	setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    //������Ҫ������¼���ص��ļ�������
    ev.data.fd=listenfd;
    
    //����Ҫ������¼�����
    ev.events=EPOLLIN|EPOLLET;

    //ע��epoll�¼�
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
        //�ȴ�epoll�¼��ķ���
        nfds=epoll_wait(epfd,events,20,500);
        
        //�����������������¼�
        for(i=0;i<nfds;++i)
        {
            if(events[i].data.fd==listenfd)//����¼�⵽һ��SOCKET�û����ӵ��˰󶨵�SOCKET�˿ڣ������µ����ӡ�
            {
                connfd = accept(listenfd,(struct sockaddr *)&clientaddr,&clilen);
                if(connfd<0){
                    perror("connfd<0");
                    exit(1);
                }

                char *str = inet_ntoa(clientaddr.sin_addr);
                printf("accapt a connection from %s\n",str);
                //�������ڶ��������ļ�������
                ev.data.fd=connfd;
                
                //��������ע��Ķ������¼�
                ev.events=EPOLLIN|EPOLLET;
                //ev.events=EPOLLIN;

                //ע��ev
                epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&ev);
            }
            else if(events[i].events&EPOLLIN)//������Ѿ����ӵ��û��������յ����ݣ���ô���ж��롣
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
                //��������д�������ļ�������
                ev.data.fd=sockfd;
                
                //��������ע���д�����¼�
                ev.events=EPOLLOUT|EPOLLET;
            }
            else if(events[i].events&EPOLLOUT) // ��������ݷ���
            {
                sockfd = events[i].data.fd;
                write(sockfd, line, n);
                
                //�������ڶ��������ļ�������
                ev.data.fd=sockfd;
                
                //��������ע��Ķ������¼�
                ev.events=EPOLLIN|EPOLLET;
                
                //�޸�sockfd��Ҫ������¼�ΪEPOLIN
                epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev);
            }
        }
    }
    return 0;
}