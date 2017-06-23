/***********************
 Name:Print the log file

 Author:by fh

 Date:2017-4-7
 
 LastChange:2017-6-15
 **********************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdarg.h>
#include"LogPrint.h"

/***************************************
 Function:Print the log file like printf
 
 Input:sign(log type)
       file(__FILE__)
       line(__LINE__)
       format(like printf)

 Output:

 Return:
       0(ok)
       -1(error)
***************************************/
int LogPrint(int sign,char *file,int line,char *format,...)
{   
    FILE *fp;
    va_list va;
    char str[1024] = {0};
    char filename[48] = {0};     
    //get the time
    time_t timep;
	struct tm *p;
    time(&timep);
	p = localtime(&timep);
	
	//set the format
    va_start(va,format);
    vsprintf(str,format,va);
    va_end(va);

    //choose the log type
    switch(sign)
    {
        case APP_DEBUG:
            snprintf(filename,sizeof(filename),"%s%04d%02d%02d%s",DEBUGFILE_PATH,1900+p->tm_year,1+p->tm_mon,p->tm_mday,DEBUGFILE);
            break;
            
        case APP_WARNING:
            snprintf(filename,sizeof(filename),"%s%04d%02d%02d%s",WARNINGFILE_PATH,1900+p->tm_year,1+p->tm_mon,p->tm_mday,WARNINGFILE);
            break;
            
        case APP_ERROR:
            snprintf(filename,sizeof(filename),"%s%04d%02d%02d%s",ERRORFILE_PATH,1900+p->tm_year,1+p->tm_mon,p->tm_mday,ERRORFILE);
            break;
            
        case APP_INFO:
            snprintf(filename,sizeof(filename),"%s%04d%02d%02d%s",INFOFILE_PATH,1900+p->tm_year,1+p->tm_mon,p->tm_mday,INFOFILE);
            break;
            
        default:
            return -1;
    }
    
    fp = fopen(filename,"a+");
    if(fp==NULL)
    {
        return -1;
    }
    //print the log
    fprintf(fp,"[%04d-%02d-%02d %02d:%02d:%02d]%s[%d]:%s\n",
        1900+p->tm_year,1+p->tm_mon,p->tm_mday,
        p->tm_hour,p->tm_min,p->tm_sec,
        file,line,str);
    fflush(fp);
    if(fp!=NULL)fclose(fp);
    return 0;
}