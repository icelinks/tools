#include"ReadData.h"

void readString(queueRecv *cache,dataInfo *data,readType func) {
    int nRet;
    dataInfo temp;

    /*search the round-robin queue*/
    nRet = searchQueue(cache,data->key);
    if(nRet==-1){
        /* if didn't find the key,read the data by func and enqueue cache*/
        func(data);
        if(enQueue(cache,data)==-1){
            deQueue(cache,&temp);
            enQueue(cache,data);
        }
        bubbleQueue(cache,cache->rear);
    } else {
        /*if find the key,read the data from cache and update cache*/
        snprintf(data->value,MAX_QUEUE_LENGTH,"%s",(cache->data[nRet])->value);
        bubbleQueue(cache,nRet);
    }
}