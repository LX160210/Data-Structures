#include <stdio.h>
#include <stdlib.h>

typedef struct DNode
{
    int data;
    struct DNode *prior;
    struct DNode *next;
} DNode;

DNode *InitList();                  // 初始化双向循环链表
int InsertTail(DNode *L, int x);    // 尾插
int DeleteByValue(DNode *L, int x); // 删除值为 x 的结点
void PrintList(DNode *L);           // 正向输出
void PrintListReverse(DNode *L);    // 反向输出

DNode *InitList()
{
    DNode *D = (DNode *)malloc(sizeof(DNode));
    D->next = D;
    D->prior = D;
    return D;
}

int InsertTail(DNode *D, int x)
{
    DNode *tail = D->prior;
    DNode *newnode = (DNode *)malloc(sizeof(DNode));
    newnode->data = x;
    tail->next = newnode;
    newnode->next = D;
    newnode->prior = tail;
    D->prior = newnode;
    return 1;
}

int DeleteByValue(DNode *D, int x)
{
    DNode *p = D->next;
    while (p->data != x)
    {
        if (p->next == D)
        {
            printf("没有值为%d的结点\n", x);
            return -1;
        }
        p = p->next;
    }
    p->prior->next = p->next;
    p->next->prior = p->prior;
    free(p);
    return 1;
}

void PrintList(DNode *D)
{
    DNode *p = D->next;
    while (p != D)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
    return;
}

void PrintListReverse(DNode *D)
{
    DNode *p = D->prior;
    while (p != D)
    {
        printf("%d ", p->data);
        p = p->prior;
    }
    printf("\n");
    return;
}

int main()
{
    DNode *D = InitList();
    InsertTail(D, 1);
    InsertTail(D, 2);
    InsertTail(D, 3);
    PrintList(D);
    PrintListReverse(D);
    DeleteByValue(D, 2);
    PrintList(D);
    PrintListReverse(D);
    return 0;
}