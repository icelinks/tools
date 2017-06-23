/************************
 Name:get the config file

 Author:by fh

 Date:2017-4-7
 
 LastChange:2017-4-20
 ***********************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"getConf.h"

/***************************************
 Function:get the key value(string)
 
 Input:title(name of title)
       key(name of key)
       filename(config name)

 Output:

 Return:
       the value of the key
***************************************/
char *GetIniKeyString(char *title,char *key,char *filename)   
{   
    FILE *fp;   
    char szLine[1024] = {0};  
    static char tmpstr[1024];  
    int rtnval;  
    int i = 0;   
    int flag = 0;   
    char *tmp;  
  
    if((fp = fopen(filename, "r")) == NULL)   
    {   
        printf("Error:CONFIG FILE IS NOT EXIST!\n");  
        return "";   
    }  
    while(!feof(fp))   
    {   
        rtnval = fgetc(fp);   
        if(rtnval==EOF&&strlen(szLine)==0)   
        {  
            break;   
        }   
        else   
        {   
            szLine[i++] = rtnval;   
        }   
        if(rtnval=='\n'||rtnval==EOF)   
        {                  
            szLine[--i] = '\0';  
            i = 0;   
            tmp = strchr(szLine, '=');   
  
            if(( tmp != NULL )&&(flag == 1))   
            {   
                if(strstr(szLine,key)!=NULL&&strlen(key)==(tmp-szLine))   
                {
                    if ('#' == szLine[0])  
                    {  
                    }  
                    else  
                    {    
                        strcpy(tmpstr,tmp+1);   
                        fclose(fp);  
                        return tmpstr;   
                    }  
                }
                else
                {
                    memset(szLine,0,sizeof(szLine));
                }   
            }  
            else   
            {   
                strcpy(tmpstr,"[");   
                strcat(tmpstr,title);   
                strcat(tmpstr,"]");  
                if(strstr(szLine,tmpstr)!=NULL)   
                {    
                    flag = 1;   
                }  
            }  
        }  
    }  
    fclose(fp);   
    return "";   
}

/***************************************
 Function:get the key value(int)
 
 Input:title(name of title)
       key(name of key)
       filename(config name)

 Output:

 Return:
       the value of the key
***************************************/
int GetIniKeyInt(char *title,char *key,char *filename)  
{  
    if(GetIniKeyString(title,key,filename)!=NULL)
    {
        return atoi(GetIniKeyString(title,key,filename));
    }
    else
    {
        return -1;
    }  
}
