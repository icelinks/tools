/***********************************
  name:深度优先搜索
  author:Mr.Fu
  date:2017-3-2
************************************/
#include<stdio.h>
#define MAX 100

int visited[MAX];
typedef int datatype;
typedef struct ENode    //边表结点
{
    int addr;
    struct ENode *E_Next;
    int value;
}Enode;

typedef struct VNode    //顶点表结点
{
    datatype data;
    Enode *firstAddr;
}Vnode;

typedef struct
{
    Vnode adv[MAX];
    int VNum,ENum;  
}Node;

void DFS(Node P,int v)
{
    Enode *s;
    printf("%c\n",P.adv[v].data);
    visited[v] = 1;
    s = P.adv[v].firstAddr;
    while(s)
    {
        if(!visited[s->addr])DFS(P,s->addr);
        s = s->E_Next;
    }
}

int main()
{
    Node P;
    P.VNum = 6;
    P.ENum = 10;
    P.adv[0].data = 'A';
    P.adv[0].firstAddr = (Enode*)malloc(sizeof(Enode));
    P.adv[0].firstAddr->addr = 1;
    P.adv[1].data = 'B';
    P.adv[1].firstAddr = (Enode*)malloc(sizeof(Enode));
    P.adv[1].firstAddr->addr = 5;
    P.adv[2].data = 'C';
    P.adv[2].firstAddr = (Enode*)malloc(sizeof(Enode));
    P.adv[2].firstAddr->addr = 2;
    P.adv[3].data = 'D';
    P.adv[3].firstAddr = (Enode*)malloc(sizeof(Enode));
    P.adv[3].firstAddr->addr = 0;
    P.adv[4].data = 'E';
    P.adv[4].firstAddr = (Enode*)malloc(sizeof(Enode));
    P.adv[4].firstAddr->addr = 5;
    P.adv[5].data = 'F';
    P.adv[5].firstAddr = (Enode*)malloc(sizeof(Enode));
    P.adv[5].firstAddr->addr = 2;
    
    P.adv[0].firstAddr->E_Next = (Enode*)malloc(sizeof(Enode));
    P.adv[0].firstAddr->E_Next->addr = 2;
    P.adv[0].firstAddr->E_Next->E_Next = (Enode*)malloc(sizeof(Enode));
    P.adv[0].firstAddr->E_Next->E_Next->addr = 4;
    P.adv[0].firstAddr->E_Next->E_Next->E_Next = NULL;
    
    P.adv[1].firstAddr->E_Next = NULL;
    
    P.adv[2].firstAddr->E_Next = NULL;
    
    P.adv[3].firstAddr->E_Next = (Enode*)malloc(sizeof(Enode));
    P.adv[3].firstAddr->E_Next->addr = 4;
    P.adv[3].firstAddr->E_Next->E_Next = NULL;
    
    P.adv[4].firstAddr->E_Next = NULL;
    
    P.adv[5].firstAddr->E_Next = (Enode*)malloc(sizeof(Enode));
    P.adv[5].firstAddr->E_Next->addr = 0;
    P.adv[5].firstAddr->E_Next->E_Next = (Enode*)malloc(sizeof(Enode));
    P.adv[5].firstAddr->E_Next->E_Next->addr = 3;
    P.adv[5].firstAddr->E_Next->E_Next->E_Next = NULL;
    
    int i;
    for(i = 0;i<P.VNum;i++)
    {
        visited[i] = 0;
    }
    
    DFS(P,1);
    return 0;
}

