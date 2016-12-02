#include<stdio.h>
#include<string.h>
#define MAX 1000
#define NONE "\033[m"
#define RED "\033[0;32;31m"

int KMP(char* s,char* p,int next[]){
   int slen=strlen(s);
   int plen=strlen(p);
   
   int i=0,j=0;
   while(i<slen&&j<plen){
     if(j==-1||s[i]==p[j]){
	    i++;
		j++;
	 }
     else{
	    j=next[j];  
	 }
   }
   	 if(j==plen){return i-j;}
	 else{return -1;}
}

int Getnext(char* p,int next[]){
    int plen=strlen(p);
	next[0]=-1;
    int k=-1;
	int j=0;
	
    while(j<plen-1||p[j]==p[k]){
		if(k==-1||p[j]==p[k]){
		    ++k;
		    ++j;
		    next[j]=k;
		}
		else{
			k=next[k];
		}
	}
     return 0;	
}

int main(){
  char s[MAX];
  char p[MAX];
  int next[MAX];
  int nRet = 0;
  int i;  

  scanf("%s",s);
  scanf("%s",p);
  Getnext(p,next);
  nRet = KMP(s,p,next);
  if(nRet==-1){printf("%s\n","not found");}
  else
  {
  	for(i=0;i<strlen(s);i++)
	{
    	if(nRet<=i&&i<(nRet+strlen(p)))
		{
			printf(RED"%c"NONE,s[i]);
		}
		else 
		{printf("%c",s[i]);}	
    }
	printf("\n");
   }
   return 0;
}

