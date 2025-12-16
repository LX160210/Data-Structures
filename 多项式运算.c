#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;
typedef struct LNode
{
    ElemType data;
    ElemType info;
    ElemType info2;
    struct LNode *next;
} LNode, *LinkList;

LNode *InitList(LNode *L)
{
    L = (LNode *)malloc(sizeof(LNode));
    L->data = 0;
    L->info = 0;
    L->next = NULL;
    return L;
}

LNode *GetTial(LNode *L)
{
    while (L->next != NULL)
    {
        L = L->next;
    }
    return L;
}

LNode *TialInsert(LNode *L, ElemType e, ElemType info)
{
    LNode *P = (LNode *)malloc(sizeof(LNode));
    P->data = e;
    P->info = info;
    P->next = NULL;
    L->next = P;
    return P;
}

void print(LNode *L, int n)
{
    if (n == 0)
    {
        L = L->next;
        while (L != NULL)
        {
            printf("%dx^%d ", L->data, L->info);
            L = L->next;
        }
        printf("\n");
    }
    else
    {
        while (L->next != NULL)
        {
            printf("%dx^%d ", L->data, L->info);
            L = L->next;
        }
        printf("\n");
    }
}

int Getlength(LNode *L)
{
    L = L->next;
    int length = 0;
    while (L != NULL)
    {
        length++;
        L = L->next;
    }
    return length;
}

LNode *Order1(LNode *L)
{
    LNode *q = NULL;
    L = L->next;
    int Max = -999;
    int Length = Getlength(L);
    for (int i = 0; i < Length + 1; i++)
    {
        if (L->info > Max && L->info != -100)
        {
            Max = L->info;
            q = L;
        }
        L = L->next;
    }
    if (q != NULL)
    {
        q->info2 = q->info;
        q->info = -100;
    }
    return q;
}

LNode *Order2(LNode *L)
{
    LNode *head = InitList(NULL);
    LNode *p = head;
    LNode *head0 = head;
    int Length = Getlength(L);
    for (int i = 0; i < Length + 1; i++)
    {
        LNode *q = (LNode *)malloc(sizeof(LNode));
        LNode *s = Order1(L);
        if (s == NULL)
        {
            free(q);
            break;
        }
        q->info = s->info2;
        q->info2 = 0;
        q->data = s->data;
        q->next = NULL;
        p->next = q;
        p = p->next;
    }
    if (Getlength(head0) != Length)
    {
        while (head0->next->next != NULL)
        {
            head0 = head0->next;
        }
        head0->next = NULL;
    }
    return head;
}

LNode *Add(LNode *p1, LNode *p2)
{
    p1 = p1->next;
    p2 = p2->next;
    LNode *p = InitList(NULL);
    LNode *head = p;
    while (p1 != NULL && p2 != NULL)
    {
        if (p1->info > p2->info)
        {
            p->next = p1;
            p1 = p1->next;
            p = p->next;
        }
        else if (p1->info < p2->info)
        {
            p->next = p2;
            p2 = p2->next;
            p = p->next;
        }
        else
        {
            LNode *temp = InitList(NULL);
            temp->data = p1->data + p2->data;
            temp->info = p1->info;
            p->next = temp;
            p = p->next;
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    while (p1 != NULL)
    {
        p->next = p1;
        p1 = p1->next;
        p = p->next;
    }
    while (p2 != NULL)
    {
        p->next = p2;
        p2 = p2->next;
        p = p->next;
    }
    return head;
}

LNode *Subtract(LNode *p1, LNode *p2)
{
    LNode *p0 = p2->next;
    while (p0 != NULL)
    {
        p0->data = -p0->data;
        p0 = p0->next;
    }
    return Add(p1, p2);
}

int info[100];
int data[100] = {0};
int length = 0;

int checkinfo(int info[], int n)
{
    for (int i = 0; i < length; i++)
    {
        if (info[i] == n)
            return 0;
    }
    return 1;
}

int cmp(const void *a, const void *b)
{
    return -(*(int *)a - *(int *)b);
}

LNode *Multiply(LNode *p1, LNode *p2)
{
    LNode *begin;
    p1 = p1->next;
    begin = p2 = p2->next;
    LNode *head = InitList(NULL);
    LNode *p = head;
    while (p1 != NULL)
    {
        while (p2 != NULL)
        {
            LNode *current = (LNode *)malloc(sizeof(LNode));
            current->data = p1->data * p2->data;
            current->info = p1->info + p2->info;
            p->next = current;
            p = p->next;
            p2 = p2->next;
        }
        p1 = p1->next;
        p2 = begin;
    }
    LNode *un1 = head;
    int k = 0;
    while (un1 != NULL)
    {
        if (checkinfo(info, un1->info))
        {
            info[k++] = un1->info;
            length++;
        }
        un1 = un1->next;
    }
    qsort(info, length, sizeof(int), cmp);
    LNode *un2 = head;
    while (un2 != NULL)
    {
        for (int i = 0; i < length; i++)
        {
            if (un2->info == info[i])
                data[i] += un2->data;
        }
        un2 = un2->next;
    }
    LNode *result = (LNode *)malloc(sizeof(LNode));
    LNode *tail = result;
    for (int i = 0; i < length; i++)
    {
        tail->data = data[i];
        tail->info = info[i];
        tail = tail->next = (LNode *)malloc(sizeof(LNode));
    }
    tail->next = NULL;
    return result;
}

int main()
{
    printf("Example1:\n");
    LNode *head1 = InitList(NULL);
    LNode *tial = head1;
    tial = TialInsert(tial, 3, 4);
    tial = TialInsert(tial, 5, 2);
    tial = TialInsert(tial, 6, 1);
    tial = TialInsert(tial, 8, 0);
    tial = TialInsert(tial, 7, -1);
    print(head1, 0);
    LNode *head2 = InitList(NULL);
    tial = head2;
    tial = TialInsert(tial, 4, 5);
    tial = TialInsert(tial, 2, 4);
    tial = TialInsert(tial, 1, 3);
    tial = TialInsert(tial, 3, 1);
    tial = TialInsert(tial, 4, -1);
    print(head2, 0);
    LNode *head3 = Add(head1, head2);
    printf("Addition Result:\n");
    print(head3, 0);

    printf("Example2:\n");
    LNode *head4 = InitList(NULL);
    tial = head4;
    tial = TialInsert(tial, 3, 2);
    tial = TialInsert(tial, 5, 4);
    tial = TialInsert(tial, 6, 1);
    tial = TialInsert(tial, 8, 3);
    tial = TialInsert(tial, 7, 0);
    head4 = Order2(head4);
    print(head4, 0);
    LNode *head5 = InitList(NULL);
    tial = head5;
    tial = TialInsert(tial, 4, 4);
    tial = TialInsert(tial, 2, 5);
    tial = TialInsert(tial, 1, 3);
    tial = TialInsert(tial, 3, 1);
    tial = TialInsert(tial, 4, 0);
    tial = TialInsert(tial, 7, 2);
    head5 = Order2(head5);
    print(head5, 0);
    printf("Subtraction Result:\n");
    LNode *head6 = Subtract(head4, head5);
    print(head6, 0);

    printf("Example3:\n");
    LNode *head7 = InitList(NULL);
    tial = head7;
    tial = TialInsert(tial, 1, 1);
    tial = TialInsert(tial, 2, 0);
    tial = TialInsert(tial, 3, 2);
    print(head7, 0);
    LNode *head8 = InitList(NULL);
    tial = head8;
    tial = TialInsert(tial, 4, 1);
    tial = TialInsert(tial, 5, 0);
    print(head8, 0);
    printf("Multiplication Result:\n");
    LNode *head9 = Multiply(head7, head8);
    print(head9, 1);

    return 0;
}
