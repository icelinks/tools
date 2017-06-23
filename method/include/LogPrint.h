/*
 *Head file for logprint.c
 *
 *This function is used to print the log file
 *with time,filename,line,detail message and 
 *so on.
 */
#ifndef __LOGPRINT_H__
#define __LOGPRINT_H__

#define APP_DEBUG 0
#define APP_WARNING 1
#define APP_ERROR 2
#define APP_INFO 3

#define DEBUGFILE_PATH "./logs/debug/"
#define WARNINGFILE_PATH "./logs/warning/"
#define ERRORFILE_PATH "./logs/error/"
#define INFOFILE_PATH "./logs/info/"

#define DEBUGFILE "D.log"
#define WARNINGFILE "W.log"
#define ERRORFILE "E.log"
#define INFOFILE "I.log"

#ifdef __cplusplus
extern "C" {
#endif

int LogPrint(int sign,char *file,int line,char *format,...);

#ifdef __cplusplus
}
#endif

#endif