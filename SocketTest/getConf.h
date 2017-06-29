#ifndef _GETCONF_H_
#define _GETCONF_H_

typedef struct
{
    char num[20];
}ChangChun_num;

#ifdef __cplusplus
extern "C" {
#endif

char *GetIniKeyString(char *title,char *key,char *filename);
int GetIniKeyInt(char *title,char *key,char *filename);

#ifdef __cplusplus
}
#endif

#endif