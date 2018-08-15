/*
 * .h for ReadData.c
 *
 * this function is about reading
 * data in LRU way
 */
#ifndef _READ_DATA_H_
#define _READ_DATA_H_

#include"Queue.h"

typedef void (*readType) (dataInfo *);

void readString(queueRecv *cache,dataInfo *data,readType func);

#endif