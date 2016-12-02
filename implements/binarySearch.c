#include<stdio.h>

int binarySearch(int p[],int low,int high,int key)
{
	int mid;

	mid = low+(high-low)/2;
	if(low>high)
	{
		return -1;
	}
	if(key<p[mid])
	{
		binarySearch(p,low,mid-1,key);
	}
	else if(p[mid]<key)
	{
		binarySearch(p,mid+1,high,key);
	}
	else
	{
		return mid;
	}
}

int main()
{
	int p[]={1,3,5,6,9};
	int target = 9;
 	int low = 0;
    int high = 4;
	printf("%d\n",binarySearch(p,low,high,target));	

	return 0;
}

