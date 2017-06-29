#include<stdio.h>
#include<stdlib.h>
#include <sys/socket.h>
//#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include"getConf.h"

#define MAXLINE 153600
#define LISTENQ 20

char TCPServerIP[24] = {0};
int TCPServerPort = 0;

int InitConfig()
{
    char *str;
    str = GetIniKeyString("TCPServer","IP","./net.ini");
    if(str!=NULL)
    {
        snprintf(TCPServerIP,24,"%s",str);
    }
    else
    {
        return -1;
    }
    TCPServerPort = GetIniKeyInt("TCPServer","PORT","./net.ini");
    if(TCPServerPort==-1)
    {
        return -1;
    }
    return 0;
}

int TCPclient(int *clifd)
{
    int nRet;
    struct sockaddr_in cliaddr;
    
    *clifd = socket(AF_INET,SOCK_STREAM,0);
    if(clifd<0)
    {
        printf("socket error!\n");
        return -1;
    }
    
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_addr.s_addr = inet_addr(TCPServerIP);
    cliaddr.sin_port = htons(TCPServerPort);
    
    nRet = connect(*clifd,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
    if(nRet<0)
    {
        printf("client connet is error!\n");
        return -1;
    }
    
    return 0;
}

int TCPserver(int *serfd)
{
    int nRet = 0,on = 1;
    int nSockfd = 0;
	
	struct sockaddr_in se_addr;
	memset(&se_addr,0,sizeof(se_addr));
	
	se_addr.sin_family=AF_INET;
	se_addr.sin_port=htons(TCPServerPort);
	se_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	nSockfd=socket(AF_INET,SOCK_STREAM,0);
	if(nSockfd < 0)
	{ 
	    printf("TCP socket error!\n");
		nRet = -1;
		return nRet; 
	}
	
	if((nRet = setsockopt(nSockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)))!=0) 
	{
	    printf("TCP setsockopt error!\n");
		nRet = -1;
		return nRet;
	}
	
	if((bind(nSockfd,(struct sockaddr*)&se_addr,sizeof(se_addr)))<0)
	{
	    printf("TCP bind error!\n");
		nRet = -1;
		return nRet;
	}

	if((listen(nSockfd,10))<0)
	{
	    printf("TCP listen error!\n");
		nRet = -1;
		return nRet;
	}
	
	struct sockaddr_in cl_addr;
	int nSize=sizeof(cl_addr);
	memset(&cl_addr,0x00, nSize);
	
	*serfd=accept(nSockfd,(struct sockaddr*)&cl_addr,(socklen_t*)&nSize);
    if(*serfd<0)
	{  
	    printf("TCP accept error!\n"); 
		nRet=-1;
		return nRet;  
	}
	
	return 0;
}

void TCPs_r(int *fd,int type)
{
    int s2,fsize,nRet;
    FILE *fp;
    char *s_buf,flag[128] = {0};
    char r_buf[153600] = {0};
    while(1)
    {
        system("clear");
        if(type==1)
        {
            printf("**********************************************\n"
                   "***********        TCP�ͻ���       ***********\n"
                   "*                                            *\n"
                   "*      1.����      2.�ȴ�����      3.����    *\n"
                   "**********************************************\n"
                   "��ѡ��");
        }
        else if(type==2)
        {
            printf("**********************************************\n"
                   "***********        TCP�����       ***********\n"
                   "*                                            *\n"
                   "*      1.����      2.�ȴ�����      3.����    *\n"
                   "**********************************************\n"
                   "��ѡ��");
        }
        scanf("%d",&s2);
        if(s2==1)
        {
            fp = fopen("mes.txt","r");
            if(fp==NULL)
            {
                printf("Ҫ���͵���Ϣ�ļ�mes.txt�����ڣ�\n");
                sleep(1);
                continue;
            }
            
            fseek(fp,0,SEEK_END);
            fsize = ftell(fp);
            s_buf = (char*)malloc(fsize+1);
            if(s_buf==NULL)
            {
                printf("�ռ����ʧ�ܣ�\n");
                fclose(fp);
                continue;
            }
            fseek(fp,0,SEEK_SET);
            fread(s_buf,fsize,1,fp);
            s_buf[fsize] = '\0';
            
            nRet = send(*fd,s_buf,fsize+1,0);
            if(nRet<0)
            {
                printf("���ʹ���\n");
            }
            else
            {
                printf("���ͳɹ���\n");
            }
            fclose(fp);
            free(s_buf);
            s_buf = NULL;
        }
        else if(s2==2)
        {
            nRet = recv(*fd,r_buf,sizeof(r_buf),0);
            if(nRet<0)
            {
                printf("���մ���\n");
            }
            else
            {
                printf("�������ݣ�%s\n",r_buf);
                printf("����y����:");
                while(1)
                {
                    scanf("%s",flag);
                    if(flag[0]=='y'||flag[0]=='Y')
                    {
                        break;
                    }
                }
            }
        }
        else if(s2==3)
        {
            break;
        }
        else
        {
            printf("��������������룡\n");
        }
        sleep(1);
    }
}

int main(int argc,char *argv)
{
    int nRet;
    int s1;
    int clifd,serfd;
    FILE *fp;
    char msg[100];
    nRet = InitConfig();
    if(nRet==-1)
    {
        return -1;
    }
    
    while(1)
    {
        system("clear");
        printf("**********************************************\n"
               "***********  Socket���Թ���ver1.0  ***********\n"
               "*                                            *\n"
               "*1.TCP�ͻ���  2.TCP�����  3.�޸�����  4.�˳�*\n"
               "**********************************************\n"
               "��ѡ��");
        scanf("%d",&s1);
        if(s1==1)
        {
            //�����ͻ���
            nRet = TCPclient(&clifd);
            if(nRet!=0)
            {
                printf("�ͻ�������ʧ�ܣ�����ѡ��...\n");
                sleep(1);
                continue;
            }
            else
            {
                printf("�ͻ������ӳɹ�����������...\n");
                sleep(1);
            }
        }
        else if(s1==2)
        {
            //���������
	        printf("�ȴ��ͻ�������...");
            nRet = TCPserver(&serfd);
            if(nRet!=0)
            {
                printf("����˿���ʧ�ܣ�����ѡ��...\n");
                sleep(1);
                continue;
            }
            else
            {
                printf("����˿����ɹ�����������...\n");
                sleep(1);
            }
        }
        else if(s1==3)
        {
            //�޸����ô���
            printf("IP:\n");
            scanf("%s",TCPServerIP);
            printf("PORT:\n");
            scanf("%d",&TCPServerPort);
            
            fp =fopen("net.ini","w");
	        if(fp==NULL)
	        {
	            printf("net.ini is not exist!\n");
		        return -1;
	        }
	        
	        fputs("[TCPServer]\n", fp);
	        
	        memset(msg,0,sizeof(msg));
	        snprintf(msg,sizeof(msg),"IP=%s\n",TCPServerIP);
	        fputs(msg, fp);
	        
	        memset(msg,0,sizeof(msg));
	        snprintf(msg,sizeof(msg),"PORT=%d\n",TCPServerPort);
	        fputs(msg, fp);
	        
	        fclose(fp);
	        
	        printf("�����޸ĳɹ�!\n");
	        sleep(1);
            
            continue;
        }
        else if(s1==4)
        {
            system("clear");
            break;
        }
        else
        {
            printf("��������������룡\n");
            sleep(1);
            continue;
        }
        
        //printf("s1:%d\n",s1);
        system("clear");
        if(s1==1)
        {
            TCPs_r(&clifd,s1);
        
            if(clifd!=0)
            {
                close(clifd);
            }
        }
        else if(s1==2)
        {
            TCPs_r(&serfd,s1);
        
            if(serfd!=0)
            {
                close(serfd);
            }
        }
    }
    
    return 0;
}
