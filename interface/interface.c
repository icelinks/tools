/************************
 Name:Function for serial

 Author:F

 Date:2017-6-21
 
 LastChange:2017-6-22
 ***********************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<termios.h>
#include<errno.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include"Socket.h"

/****************************SERIAL**********************************/
int speed_arr[] = {B115200, B57600, B38400, B19200, B9600, B4800, B2400, B1800, B1200, B600, B300, B200, B150, B134, B110, B75, B50, B0};
int name_arr[] = {115200, 57600, 38400, 19200, 9600, 4800, 2400, 1800, 1200, 600, 300, 200, 150, 134, 110, 75, 50, 0};

int InitSerial(int *SerialFd,DATA_SERIAL *serial)
{
    int nRet = 0;
    int i;
    struct termios attr;
	bzero(&attr, sizeof(attr));

	if((*SerialFd = open(serial->port,O_RDWR | O_NOCTTY | O_NDELAY))<0)
	{
	    LogPrint(APP_ERROR,__FILE__,__LINE__,"open serial error!");
		return -1;
	}
	
	//set the interface attribute
	
	tcgetattr(*SerialFd,&attr);

	for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++)
	{
		if  (serial->speed == name_arr[i])
		{
			tcflush(*SerialFd, TCIOFLUSH);
			cfsetispeed(&attr, speed_arr[i]);
			cfsetospeed(&attr, speed_arr[i]);
			int status = tcsetattr(*SerialFd, TCSANOW, &attr);
			if  (status != 0)
			{
			    LogPrint(APP_ERROR,__FILE__,__LINE__,"set speed error!");
				return -2;
			}
		}
		tcflush(*SerialFd,TCIOFLUSH);
   }
   attr.c_cflag &= ~CSIZE;
  
	switch (serial->databits)
	{
	    case 5:
			attr.c_cflag |= CS5;
			break;
		case 6:
			attr.c_cflag |= CS6;
			break;
		case 7:
			attr.c_cflag |= CS7;
			break;
		case 8:
			attr.c_cflag |= CS8;
			break;
	    default:
	        LogPrint(APP_ERROR,__FILE__,__LINE__,"databits is undefined!");		    
		    return -3;
	}
	attr.c_cflag |= (CLOCAL | CREAD);
	attr.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	attr.c_oflag &= ~(OPOST);
	switch (serial->stopbits)
	{
	    case 1:
		    attr.c_cflag &= ~CSTOPB;    //1 bit stop
		    break;
	    case 2:
	        attr.c_cflag |= CSTOPB;    //2 bit stop
		    break;
	    default:
	        LogPrint(APP_ERROR,__FILE__,__LINE__,"stopbits is undefined!");	
		    return -4;
	}
	
	switch (serial->parity[0])     //set the parity
	{
	    case 'n':
		case 'N':
			attr.c_cflag &= ~PARENB;   /* Clear parity enable */
			attr.c_iflag &= ~INPCK;     /* Enable parity checking */
			break;
		case 'o':
		case 'O':
			attr.c_cflag |= (PARODD | PARENB);  /* odd*/ 
			attr.c_iflag |= INPCK;             /* Disnable parity checking */
			break;
		case 'e':
		case 'E':
			attr.c_cflag |= PARENB;     /* Enable parity */
			attr.c_cflag &= ~PARODD;   /* even*/  
			attr.c_iflag |= INPCK;       /* Disnable parity checking */
			break;
		case 'S':
		case 's':  /*as no parity*/
			attr.c_cflag &= ~PARENB;
			attr.c_cflag &= ~CSTOPB;
			break;
	    default:
	        LogPrint(APP_ERROR,__FILE__,__LINE__,"parity is undefined!");
		    return -5;
	}
	
	if (serial->parity[0] != 'n')
	{
		attr.c_iflag |= INPCK;
	}
  		
    attr.c_cc[VTIME] = 10; 
    attr.c_cc[VMIN] = 0;
    attr.c_lflag  &= ~(ICANON | ECHO | ECHOE | ISIG);  /*raw input*/

	tcflush(*SerialFd,TCIFLUSH); /* Update the attr and do it NOW */
	if (tcsetattr(*SerialFd,TCSANOW,&attr) != 0)
  	{
  	    LogPrint(APP_ERROR,__FILE__,__LINE__,"set raw input error!");
		return -6;
	}
	

	tcflush(*SerialFd,TCIFLUSH);   //flush the input
	nRet = tcsetattr(*SerialFd,TCSANOW,&attr); //change the set immediately
	if (nRet!=0)
	{
	    LogPrint(APP_ERROR,__FILE__,__LINE__,"set serial error!");
	    return -7;
	}
	
	return 0;	
}

int RecvSerial(int s_fd,char *buf,int datalen)
{
	fd_set fd_read;
	FD_ZERO(&fd_read);
	FD_SET(s_fd,&fd_read);
	int nRet = 0;

	nRet = select(s_fd+1,&fd_read,NULL,NULL,NULL);
	
	if(nRet<0)
	{
	    LogPrint(APP_ERROR,__FILE__,__LINE__,"select is error,the error code is %d",nRet);
	    return -1;
	}
	
	if(FD_ISSET(s_fd,&fd_read))
	{
		nRet = read(s_fd,buf,datalen);
		if(nRet<0)
		{
		    LogPrint(APP_ERROR,__FILE__,__LINE__,"read is error,error code is %d",nRet);
			return -1;
		}
		return 0;
	}

	return 0;		
}

int GetOneSerial(DATA_SERIAL* serial)
{
	int SerialFd;
	char temp[SOURCE_DATA_MAX_SIZE] = {0};
	char buf[8] = {0};
	int datalen = 1;
	if(InitSerial(&SerialFd,serial)!=0)
	{
	    LogPrint(APP_ERROR,__FILE__,__LINE__,"init serial is error");
		return -1;
	}
	LogPrint(APP_INFO,__FILE__,__LINE__,"open serial %s success!",serial->port);
	while(RecvSerial(SerialFd,buf,datalen)==0)
	{
		printf("The source message is %s\n",buf);
		if(strlen(temp)<SOURCE_DATA_MAX_SIZE)
		{
		    strncat(temp,buf,1);
		}
		else
		{    
		    LogPrint(APP_INFO,__FILE__,__LINE__,"The source message from serial %s is %s",serial->port,temp);
		    memset(temp,0,sizeof(temp));
		}
		//´¦Àíº¯Êý
		
		memset(buf,0,8);
	}
	
	close(SerialFd);
	return 0;
}