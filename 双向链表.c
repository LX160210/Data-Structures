#include <stdio.h>
#include <stdlib.h>

typedef struct DNode
{
    int data;
    struct DNode *prior;
    struct DNode *next;
} DNode;

// 初始化双向链表头结点
void InitList(DNode *D)
{
    D->data = 0;
    D->prior = NULL;
    D->next = NULL;
}
// 在 p 后插入新节点，值为 x
int InsertNext(DNode *p, int x)
{
    if (p->next)
    {
        DNode *q = p->next;
        DNode *P = (DNode *)malloc(sizeof(DNode));
        P->data = x;
        p->next = P;
        P->prior = p;
        P->next = q;
        q->prior = P;
    }
    else
    {
        DNode *P = (DNode *)malloc(sizeof(DNode));
        P->data = x;
        p->next = P;
        P->prior = p;
        P->next = NULL;
    }
    return 0;
} // 在 p 后插入

// 在 p 前插入新节点，值为 x
int InsertPrior(DNode *p, int x)
{
        DNode *q = p->prior;
        DNode *P = (DNode *)malloc(sizeof(DNode));
        P->data = x;
        p->prior = P;
        P->next = p;
        P->prior = q;
        q->next = P;
    return 0;
} // 在 p 前插入

// 删除 p 本身
int DeleteNode(DNode *p)
{
    if (p->next)
    {
        p->prior->next = p->next;
        p->next->prior = p->prior;
        free(p);
    }
    else
    {
        p->prior->next = NULL;
        free(p);
    }
    return 0;
} // 删除 p 本身

// 正向输出链表
void PrintList(DNode *D)
{
    D = D->next;
    while (D)
    {
        printf("%d ", D->data);
        D = D->next;
    }
    printf("\n");
} // 正向输出

// 定位到尾节点
DNode *gettail(DNode *D)
{
    while (D->next)
    {
        D = D->next;
    }
    return D;
}

// 反向输出链表
void PrintListReverse(DNode *D)
{
    D = gettail(D);
    while (D->prior)
    {
        printf("%d ", D->data);
        D = D->prior;
    }
    printf("\n");
}

int main()
{
    DNode *D = (DNode *)malloc(sizeof(DNode));
    InitList(D);
    InsertNext(D, 1);
    InsertNext(D->next, 2);
    InsertNext(D->next->next, 3);
    PrintList(D);
    PrintListReverse(D);
    DeleteNode(D->next->next);
    PrintList(D);
    PrintListReverse(D);
    InsertPrior(D->next, 4);
    PrintList(D);
    PrintListReverse(D);
    return 0;
}