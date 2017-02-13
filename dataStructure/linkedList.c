/***********************************
  name:数据结构单链表构造及相关操作
       (需要注意内存的释放)
  author:Mr.Fu
  date:2017-2-10
************************************/
#include<stdio.h>
#include<stdlib.h>

typedef char DataType;  //单链表数据类型，此处为char
typedef struct node        //单链表结构
{
    DataType data;
    struct node *next;
}ListNode,* LinkList;

/*尾插法建立单链表*/
LinkList CreateList_B(void)
{
    char ch;
    ListNode *p,*r;
    LinkList head = (ListNode*)malloc(sizeof(ListNode));
    r = head;
    while((ch= getchar())!='\n')
    {
        p = (ListNode*)malloc(sizeof(ListNode));
        p->data = ch;
        r->next = p;
        r = p;
    }
    r->next = NULL;
    return head;
}

/*头插法建立单链表*/
LinkList CreateList_F(void)
{
    char ch;
    ListNode *p;
    LinkList head = (ListNode*)malloc(sizeof(ListNode));
    while((ch = getchar())!='\n')
    {
        p = (ListNode*)malloc(sizeof(ListNode));
        p->data = ch;
        p->next = head->next;
        head->next = p;
    }
    return head;
}

/*得到单链表的长度*/
int GetLength(LinkList l)
{
    int i = 0;
    ListNode *p;
    p = l->next;
    while(p!=NULL)
    {
        p = p->next;
        i++;
    }
    return i;
}

/*在单链表中查找第i个结点*/
ListNode* GetNode(LinkList l,int i)
{
    int j = 0;
    ListNode *p;
    if(i<1||i>GetLength(l))
    {
        printf("结点位置超过范围\n");
        exit(-1);
    }
    p = l;
    while(p!=NULL&&j<i)
    {
        p = p->next;
        j++;
    }
    return p;
}

/*在单链表中查找值为e的结点*/
ListNode* GetNode_V(LinkList l,DataType e)
{
    ListNode *p;
    p = l;
    while(p->data!=e)
    {
        p = p->next;
        if(p==NULL)
        {
            printf("链表中不存在值为e的结点\n");
            exit(0);
        }
    }
    return p;
}

/*在单链表第i个位置插入结点e*/
void InsertList(LinkList head,DataType e,int i)
{
    ListNode *p,*q,*s;
    int j;
    p = head;
    if(i<1||i>GetLength(head))
    {
        printf("超出链表数据范围\n");
        exit(-1);
    }
    for(j = 0;j<i;j++)
    {
        q = p;
        p = p->next;
    }
    s = (ListNode*)malloc(sizeof(ListNode));
    s->data = e;
    s->next = q->next;
    q->next = s;
}

/*删除单链表中第i个结点*/
void DeleteList(LinkList head,int i)
{
    ListNode *p,*q;
    int j;
    p = head;
    if(i<1||i>GetLength(head))
    {
        printf("超出链表数据范围\n");
        exit(-1);
    }
    for(j = 1;j<i-1;j++)
    {
        p = p->next;
    }
    q = p->next;
    p->next = q->next;
    free(q);
}

int main()
{
    LinkList p;
    ListNode *s;
    p = CreateList_B();
    s = GetNode(p,3);
    printf("%d\n",GetLength(p));
    printf("%c\n",s->data);
    InsertList(p,'a',3);
    s = GetNode(p,3);
    printf("%c\n",s->data);
    DeleteList(p,3);
    s = GetNode(p,3);
    printf("%c\n",s->data);
    free(p);
    free(s);
    return 0;
}

