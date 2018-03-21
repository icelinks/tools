/*
 *Description:A simple example for heap sort
 *Author:by icelinks
 *Date:2018-03-21
 *
 *LastChange:2018-03-21
 *@author mail :icelinks1994@gmail.com
 */
#include <stdio.h>

void maxHeapify(int array[],int index,int heapSize);
void swap(int array[],int i,int j);
void buildMaxHeap(int array[],int heapSize);
void heapSort(int array[],int heapSize);

void
maxHeapify(int array[],int index,int heapSize){
    int iMax,iLeft,iRight;
    iMax = index;
    iLeft = 2 * index + 1;
    iRight = 2 * (index + 1);

    if(iLeft < heapSize && array[iLeft] > array[iMax]){
        iMax = iLeft;
    }

    if(iRight < heapSize && array[iRight] > array[iMax]){
        iMax = iRight;
    }

    if(iMax!=index){
        swap(array,index,iMax);
        maxHeapify(array,iMax,heapSize);
    }
}

void
swap(int array[],int i,int j){
    int temp;
    temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void
buildMaxHeap(int array[],int heapSize){
    int i;
    int iParent;
    iParent = (heapSize - 1) / 2;

    for(i = iParent;i>=0;i--){
        maxHeapify(array,iParent,heapSize);
    }
}

void
heapSort(int array[],int heapSize){
    int i;
    buildMaxHeap(array,heapSize);
    for(i = heapSize - 1; i > 0; i--){
        swap(array,0,i);
        maxHeapify(array,0,i);
    }
}

int main(int argc,char* argv[])
{
    int i;
    int array[10] = {16,14,10,8,7,9,3,2,4,1};
    heapSort(array,10);
    for(i = 0;i < 10;i++){
        printf("%d\n",array[i]);
    }
    return 0;
}