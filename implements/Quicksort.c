#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 1000

/*快排实现，使用字符串数组*/

void swap(char *p,char *q){
	char temp;
	temp=*p;
	*p=*q;
	*q=temp;
}

int merge(int low,int high,char s[]){
	int pi=s[low];
	while(low<high&&s[high]>=pi)high--;
	swap(&s[low],&s[high]);
	while(low<high&&s[low]<=pi)low++;
	swap(&s[low],&s[high]);
	return low;
}

void Quicksort(int low,int high,char s[]){
	int pi=merge(low,high,s);
	if(low<high){
	Quicksort(low,pi-1,s);
	Quicksort(pi+1,high,s);
	}
}

int main() 
{
	int n;
	char s[MAX];
    scanf("%d",&n);
    scanf("%s",&s);
	Quicksort(0,n-1,s);
	printf("%s",s);
	return 0;
}