#include<stdio.h>
#include<stdlib.h>
#include"../include/Queue.h"

/*Init the round-robin queue*/
int InitQueue(queueRecv *p)
{
    p->rear = p->front = 0;
    return 0;
}

/*Data enqueue*/
int EnQueue(queueRecv *p,char *e)
{
    if((p->rear+1)%MAX_QUEUE==p->front)
    {
        printf("Queue is full!\n");
        return -1;
    }
    else
    {
        p->rear = (p->rear+1)%MAX_QUEUE;
        p->data[p->rear] = (char*)calloc(MAX_QUEUE_LENGTH,sizeof(char));
        snprintf(p->data[p->rear],MAX_QUEUE_LENGTH,"%s",e);
        return 0;
    }
}

/*Data dequeue*/
int DeQueue(queueRecv *p,char *e)
{
    if(p->rear==p->front)
    {
        printf("Queue is empty!\n");
        return -1;
    }
    else
    {
        p->front = (p->front+1)%MAX_QUEUE;
        snprintf(e,MAX_QUEUE_LENGTH,"%s",p->data[p->front]);
        free(p->data[p->front]);
        return 0;
    }
}