/************************************
 Name:recv the message from interface

 Author:by fh

 Date:2017-3-10
 ***********************************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<termios.h>
#include<errno.h>

#define DEVICE "/dev/ttyS0"

int ser_fd = 0;

/****************************
 Function: init the interface
 
 Input:NULL
 
 Output:NULL
 
 Return:
	the result of the 
    function
    (0 is ok/-1 is error)
 ***************************/
int init_ser(void)
{
	if((ser_fd = open(DEVICE,O_RDWR | O_NOCTTY | O_NDELAY))<0)
	{
		printf("open serial error\n");
		return -1;
	}
	
	//set the interface attribute
	struct termios attr;
	
	tcgetattr(ser_fd,&attr);
	attr.c_cflag |= (CLOCAL|CREAD); //set the control flag
	attr.c_cflag &= ~CSIZE;        //block the size
	attr.c_cflag &= ~CRTSCTS;    
	attr.c_cflag |= CS8;        //set the datalen
	attr.c_cflag &= ~CSTOPB;    //1 bit stop
	attr.c_iflag |=IGNPAR;      //ignore the check
	attr.c_oflag = 0;
	attr.c_lflag = 0;
	cfsetospeed(&attr,B115200); //set the bps

	tcflush(ser_fd,TCIFLUSH);   //flush the input
	tcsetattr(ser_fd,TCSANOW,&attr); //change the set immediately
	return 0;	
}

/****************************
 Function:receive the message

 Input:
    s_fd(interface descriptor)
	datalen(the length of data)
	
 Output:
	data(buffer for saving the message)
 
 Return:
	the result of the 
    function
    (0 is ok/-1 is error)
****************************/
int ser_recv(int s_fd,char *data,int datalen)
{
	fd_set fd_read;
	FD_ZERO(&fd_read);
	FD_SET(s_fd,&fd_read);
	int nRet = 0;

	nRet = select(s_fd+1,&fd_read,NULL,NULL,NULL);
	
	if(FD_ISSET(s_fd,&fd_read))
	{
		read(s_fd,data,datalen);
		return 0;
	}

	return 0;		
}

int main(int argc,char **argv)
{
	char data[10];
	int datalen = 10;
	while(1)
	{
		if(init_ser()!=0)
		{
			printf("init is error\n");
			return -1;
		}
		if(ser_recv(ser_fd,data,datalen)==0)
		{	
			printf("The message is %s\n",data);
			close(ser_fd);
		}
	}
	return 0;
}

