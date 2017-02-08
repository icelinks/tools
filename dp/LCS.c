#include<stdio.h>

int main()
{
    int i,begin = 0,end = 0;
    int data[] = {1,-2,3,-1,7};
    int sum = 0;
    int max = data[0];
    
    for(i = 0;i<sizeof(data)/sizeof(data[0]);i++)
    {
        sum+=data[i];
        if(sum>=max)
        {
            max = sum;
            end = i;
        }
        if(sum<0)
        {
            begin = i+1;
            sum = 0;
        }
    }    
    printf("%d\n",max);
    printf("begin:%d\nend:%d",begin+1,end+1);
    return 0;
}

