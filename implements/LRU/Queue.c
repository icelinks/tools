#include"Queue.h"

/*Init the round-robin queue*/
int initQueue(queueRecv *p)
{
    p->rear = p->front = 0;
    return 0;
}

/*Data enqueue*/
int enQueue(queueRecv *p,dataInfo *e)
{
    if((p->rear+1)%MAX_QUEUE==p->front)
    {
        printf("Queue is full!\n");
        return -1;
    }
    else
    {
        p->rear = (p->rear+1)%MAX_QUEUE;
        p->data[p->rear] = (dataInfo*)calloc(1,sizeof(dataInfo));
        memcpy(p->data[p->rear],e,sizeof(dataInfo));
        return p->rear;
    }
}

/*Data dequeue*/
int deQueue(queueRecv *p,dataInfo *e)
{
    if(p->rear==p->front)
    {
        printf("Queue is empty!\n");
        return -1;
    }
    else
    {
        p->front = (p->front+1)%MAX_QUEUE;
        memcpy(e,p->data[p->front],sizeof(dataInfo));
        free(p->data[p->front]);
        return p->front;
    }
}

/*Search the queue*/
int searchQueue(queueRecv *p,char *key)
{
    int i;
    for(i=p->rear;i>p->front;--i){
        if(strcmp((p->data[i])->key,key)==0)return i;
    }
    return -1;
}

/*Bubble the queue*/
void bubbleQueue(queueRecv *p,int position)
{
    int i;
    dataInfo temp;

    for(i=position;i>p->front+1;--i){
       memcpy(&temp,p->data[i],sizeof(dataInfo));
       memcpy(p->data[i],p->data[i-1],sizeof(dataInfo));
       memcpy(p->data[i-1],&temp,sizeof(dataInfo));
    }
}