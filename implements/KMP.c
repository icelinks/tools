#include<stdio.h>
#include<string.h>
#define MAX 1000

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
  
  scanf("%s",s);
  scanf("%s",p);
  Getnext(p,next);
  if(KMP(s,p,next)==-1){printf("%s\n","not found");}
  else{printf("%d\n",KMP(s,p,next));}
}