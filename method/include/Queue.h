/*
 * .h for Queue.c
 *
 * this function is about a round-robin queue
 */
#ifndef _QUEUE_H_
#define _QUEUE_H_

#define MAX_QUEUE 1000
#define MAX_QUEUE_LENGTH 10240

typedef struct
{
    char *data[MAX_QUEUE];
    int front,rear;
}queueRecv;

int InitQueue(queueRecv *p);
int EnQueue(queueRecv *p,char *e);
int DeQueue(queueRecv *p,char *e);

#endif