#include "ReadData.h"

void readConf(dataInfo *data) {
    printf("read config!\n");
    snprintf(data->value,MAX_QUEUE_LENGTH,"hello");
}

int main()
{
    queueRecv cache;
    dataInfo temp;
    char value[128];
    char key[32];

    initQueue(&cache);
    snprintf(temp.key,MAX_KEY_LENGTH,"test");
    snprintf(temp.value,MAX_QUEUE_LENGTH,"test");
    enQueue(&cache,&temp);

    snprintf(temp.key,32,"test");
    readString(&cache,&temp,&readConf);
    printf("%s\n",temp.value);
    snprintf(temp.key,32,"hello");
    readString(&cache,&temp,&readConf);
    printf("%s\n",temp.value);
    readString(&cache,&temp,&readConf);
    printf("%s\n",temp.value);
    snprintf(temp.key,32,"test");
    readString(&cache,&temp,&readConf);
    printf("%s\n",temp.value);

    return 0;
}