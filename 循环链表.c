#include <stdio.h>
#include <stdlib.h>

typedef struct LNode
{
    int data;
    struct LNode *next;
} LNode;

LNode *InitLNode()
{
    LNode *L = (LNode *)malloc(sizeof(LNode));
    L->next = L;
    return L;
}

// 定位到尾节点
LNode *gettailcircular(LNode *L)
{
    LNode *p = L;
    while (p->next != L)
    {
        p = p->next;
    }
    return p;
}

// 尾插
int InsertTail(LNode *L, int x)
{
    LNode *l = gettailcircular(L);
    LNode *p = (LNode *)malloc(sizeof(LNode));
    p->data = x;
    l->next = p;
    p->next = L;
    return 0;
}

// 删除值为 x 的结点
int DeleteByValue(LNode *L, int x)
{
    if (L->next == L)
    {
        printf("链表为空，无法删除\n");
        return -1;
    }
    LNode *q = L;
    //q = q->next;
    while (q->next->data != x)
    {
        q = q->next;
        if (q->next == L)
        {
            printf("没有值为%d的结点\n", x);
            return -1;
        }
    }
    LNode *toDelete = q->next;
    q->next = toDelete->next;
    free(toDelete);
    return 0;
}

// 顺序输出
void PrintList(LNode *L)
{
    LNode *p = L->next;
    while (p != L)
    {
        printf("%d ", p->data);
        p = p->next;
    }
}
int main()
{
    LNode *L = InitLNode();
    InsertTail(L, 1);
    InsertTail(L, 2);
    InsertTail(L, 3);
    PrintList(L);
    printf("\n");
    DeleteByValue(L, 2);
    PrintList(L);
    return 0;
}