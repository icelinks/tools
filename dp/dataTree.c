#include<stdio.h>

int main()
{
    int i,j;
    int data[5][5] = {
        {9,0,0,0,0},
        {12,15,0,0,0},
        {10,6,8,0,0},
        {2,18,9,5,0},
        {19,7,10,4,16}
    };

    for(i = 4;i>0;i--)
        for(j = 0;j<i;j++)
	    data[i-1][j]+=data[i][j]>data[i][j+1]?data[i][j]:data[i][j+1];

    printf("%d",data[0][0]);

    return 0;
}

