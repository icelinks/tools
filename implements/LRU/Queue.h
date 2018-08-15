/*
 * .h for Queue.c
 *
 * this function is about a round-robin queue
 */
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_QUEUE 1000
#define MAX_QUEUE_LENGTH 10240
#define MAX_KEY_LENGTH 64

typedef struct
{
    char key[MAX_KEY_LENGTH];
    char value[MAX_QUEUE_LENGTH];
}dataInfo;

typedef struct
{
    dataInfo *data[MAX_QUEUE];
    int front,rear;
}queueRecv;

int initQueue(queueRecv *p);
int enQueue(queueRecv *p,dataInfo *e);
int deQueue(queueRecv *p,dataInfo *e);

int searchQueue(queueRecv *p,char *key);
void bubbleQueue(queueRecv *p,int position);

#endif