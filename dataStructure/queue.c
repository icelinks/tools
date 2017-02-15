/***********************************
  name:循环队列基本操作
  author:Mr.Fu
  date:2017-2-15
************************************/
#include<stdio.h>

#define MAX 100

typedef int datatype;
typedef struct
{
    datatype data[MAX];
    int front,rear;
}queue;

/*初始化队列*/
int InitQueue(queue *p)
{
    p->rear = p->front = 0;
    return 0;
}

/*入队操作*/
int InQueue(queue *p,datatype e)
{
    if((p->rear+1)%MAX==p->front)
    {
        printf("队列已满\n");
        return -1;
    }
    else
    {
        p->rear = (p->rear+1)%MAX;
        p->data[p->rear] = e;
        return 0;
    }
}

/*出队操作*/
int OutQueue(queue *p,datatype *e)
{
    if(p->rear==p->front)
    {
        printf("队列为空\n");
        return -1;
    }
    else
    {
        p->front = (p->front+1)%MAX;
        *e = p->data[p->front];
        return 0;
    }
}

int main()
{
    queue *p;
    int j = 0;
    InitQueue(p);
    InQueue(p,1);
    InQueue(p,2);
    InQueue(p,3);
    OutQueue(p,&j);
    printf("%d\n",j);
    OutQueue(p,&j);
    printf("%d\n",j);
    OutQueue(p,&j);
    printf("%d\n",j);
    return 0;
}

