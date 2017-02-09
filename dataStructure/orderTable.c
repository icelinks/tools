/***********************************
  name:数据结构顺序表构造及相关操作
  author:Mr.Fu
  date:2017-2-9
************************************/
#include<stdio.h>

#define MAX 100
typedef int DataType;  //线性表数据类型，此处为int
typedef struct         //线性表结构
{
    DataType data[MAX];
    int length;
}List;

/*初始化顺序表*/
void InitList(List *l)
{
    l->length = 0;
}

/*得到顺序表长度*/
int GetLength(List *l)
{
    return l->length;
}

/*取出第i个元素*/
DataType GetNode(List *l,int i)
{
    if(i<1||i>l->length)
    {
        printf("超出顺序表数据范围\n");
        return -1;
    }
    return l->data[i-1];
}

/*查找值为e的结点,找不到则返回-1*/
int Locate(List *l,DataType e)
{
    int i;
    for(i = 0;i<l->length;i++)
    {
        if(l->data[i]==e)return i+1;
    }
    return -1;
}

/*在第i个位置插入值为e的新元素*/
int InsertList(List *l,int i,DataType e)
{
    int j;
    if(i<1||i>l->length+1)
    {
        printf("超出顺序表范围\n");
        return -1;        
    }
    if(l->length==MAX)
    {
        printf("顺序表空间不够\n");
        return -1;
    }
    for(j = l->length-1;j>=i-1;j--)
    {
        l->data[j+1] = l->data[j];
    }
    l->data[i-1] = e;
    l->length++;
    return 0;
}

/*删除顺序表中的第i个元素*/
int DeleteList(List *l,int i)
{
    int j;
    if(i<1||i>l->length)
    {
        printf("超出数据范围\n");
        return -1;    
    }
    for(j=i;j<l->length-1;j++)
    {
        l->data[j-1] = l->data[j];
    }
    l->length--;
    return 0;
}

/*清空顺序表*/
void ClearList(List *l)
{
    l->length = 0;
}

int main()
{
    List *l;
    DataType e = 5;
    InitList(l);
    InsertList(l,1,e);
    InsertList(l,2,e);
    printf("%d",GetNode(l,1));
    DeleteList(l,1);
    printf("%d",GetNode(l,1));
    printf("%d",Locate(l,e));
    ClearList(l);
    return 0;
}

