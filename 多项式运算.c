#include <stdio.h>
#include <stdlib.h>

typedef struct LNode
{
    int coef;
    int exp;
    int visited;
    struct LNode *next;
} LNode, *LinkList;

void FreeList(LNode *L)
{
    LNode *p;
    while (L)
    {
        p = L;
        L = L->next;
        free(p);
    }
}

LNode *InitList(LNode *L)
{
    L = (LNode *)malloc(sizeof(LNode));
    if (L == NULL)
    {
        fprintf(stderr, "Error: malloc failed in InitList.\n");
        exit(EXIT_FAILURE);
    }
    L->coef = 0;
    L->exp = 0;
    L->next = NULL;
    return L;
}

LNode *GetTail(LNode *L)
{
    while (L->next != NULL)
    {
        L = L->next;
    }
    return L;
}

LNode *TailInsert(LNode *L, int coef, int exp)
{
    LNode *P = (LNode *)malloc(sizeof(LNode));
    if (P == NULL)
    {
        fprintf(stderr, "Error: malloc failed in TailInsert.\n");
        exit(EXIT_FAILURE);
    }
    P->coef = coef;
    P->exp = exp;
    P->visited = 0;
    P->next = NULL;
    L->next = P;
    return P;
}

void print(LNode *L)
{
    L = L->next;
    while (L != NULL)
    {
        printf("%dx^%d ", L->coef, L->exp);
        L = L->next;
    }
    printf("\n");
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

LNode *Select(LNode *L)
{
    LNode *q = (LNode *)malloc(sizeof(LNode));
    if (q == NULL)
    {
        fprintf(stderr, "Error: malloc failed in Select.\n");
        exit(EXIT_FAILURE);
    }
    int Max = -999;
    L = L->next;
    LNode *p = L;
    while (L)
    {
        if (L->exp > Max && L->visited != 1)
        {
            Max = L->exp;
            q->coef = L->coef;
            q->exp = L->exp;
        }
        L = L->next;
    }
    while (p)
    {
        if (p->exp == Max)
        {
            p->visited = 1;
            break;
        }
        p = p->next;
    }
    q->next = NULL;
    return q;
}

LNode *Sort(LNode *L)
{
    LNode *head = InitList(NULL);
    LNode *p = head;
    int Length = Getlength(L);
    for (int i = 0; i < Length; i++)
    {
        LNode *q = InitList(NULL);
        LNode *s = Select(L);
        if (s == NULL)
        {
            free(q);
            break;
        }
        q->exp = s->exp;
        q->coef = s->coef;
        p->next = q;
        p = p->next;
        free(s);
    }
    return head;
}

LNode *Add(LNode *p1, LNode *p2)
{
    p1 = p1->next;
    p2 = p2->next;
    LNode *head = InitList(NULL);
    LNode *p = head;
    while (p1 != NULL && p2 != NULL)
    {
        LNode *temp = InitList(NULL);
        if (p1->exp > p2->exp)
        {
            temp->coef = p1->coef;
            temp->exp = p1->exp;
            p1 = p1->next;
        }
        else if (p1->exp < p2->exp)
        {
            temp->coef = p2->coef;
            temp->exp = p2->exp;
            p2 = p2->next;
        }
        else
        {
            temp->coef = p1->coef + p2->coef;
            temp->exp = p1->exp;
            p1 = p1->next;
            p2 = p2->next;
        }
        p->next = temp;
        p = p->next;
    }
    while (p1 != NULL)
    {
        LNode *temp = InitList(NULL);
        temp->coef = p1->coef;
        temp->exp = p1->exp;
        p->next = temp;
        p1 = p1->next;
        p = p->next;
    }
    while (p2 != NULL)
    {
        LNode *temp = InitList(NULL);
        temp->coef = p2->coef;
        temp->exp = p2->exp;
        p->next = temp;
        p2 = p2->next;
        p = p->next;
    }
    return head;
}

LNode *Subtract(LNode *p1, LNode *p2)
{
    LNode *p0 = InitList(NULL);
    LNode *head0 = InitList(NULL);
    p0->next = head0;
    p2 = p2->next;
    LNode *p;
    while (p2 != NULL)
    {
        head0->coef = -p2->coef;
        head0->exp = p2->exp;
        head0->next = InitList(NULL);
        p = head0;
        head0 = head0->next;
        p2 = p2->next;
    }
    p->next = NULL;
    return Add(p1, p0);
}

int checkexp(int exp[], int n, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (exp[i] == n)
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
    int Length= Getlength(p1) * Getlength(p2);
    int exp[Length];
    int coef[Length];
    for (int i = 0; i < Length; i++)
        coef[i] = 0;
    int length = 0;
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
            if (current == NULL)
            {
                fprintf(stderr, "Error: malloc failed in Multiply.\n");
                exit(EXIT_FAILURE);
            }
            current->coef = p1->coef * p2->coef;
            current->exp = p1->exp + p2->exp;
            current->next = NULL;
            p->next = current;
            p = p->next;
            p2 = p2->next;
        }
        p1 = p1->next;
        p2 = begin;
    }
    LNode *un1 = head->next;
    int k = 0;
    while (un1 != NULL)
    {
        if (checkexp(exp, un1->exp, length))
        {
            exp[k++] = un1->exp;
            length++;
        }
        un1 = un1->next;
    }
    qsort(exp, length, sizeof(int), cmp);
    LNode *un2 = head->next;
    while (un2 != NULL)
    {
        for (int i = 0; i < length; i++)
        {
            if (un2->exp == exp[i])
                coef[i] += un2->coef;
        }
        un2 = un2->next;
    }
    FreeList(head);
    LNode *result = InitList(NULL);
    LNode *tail = InitList(NULL);
    result->next = tail;
    LNode *P;
    for (int i = 0; i < length; i++)
    {
        tail->coef = coef[i];
        tail->exp = exp[i];
        tail->next = InitList(NULL);
        P = tail;
        tail = tail->next;
    }
    P->next = NULL;
    return result;
}

int main()
{
    printf("Example1:\n");
    LNode *poly1 = InitList(NULL);
    LNode *tail = poly1;
    tail = TailInsert(tail, 3, 4);
    tail = TailInsert(tail, 5, 2);
    tail = TailInsert(tail, 6, 1);
    tail = TailInsert(tail, 8, 0);
    tail = TailInsert(tail, 7, -1);
    print(poly1);
    LNode *poly2 = InitList(NULL);
    tail = poly2;
    tail = TailInsert(tail, 4, 5);
    tail = TailInsert(tail, 2, 4);
    tail = TailInsert(tail, 1, 3);
    tail = TailInsert(tail, 3, 1);
    tail = TailInsert(tail, 4, -1);
    print(poly2);
    LNode *sum = Add(poly1, poly2);
    printf("Addition Result:\n");
    print(sum);

    printf("Example2:\n");
    LNode *poly4 = InitList(NULL);
    tail = poly4;
    tail = TailInsert(tail, 3, 2);
    tail = TailInsert(tail, 5, 4);
    tail = TailInsert(tail, 6, 1);
    tail = TailInsert(tail, 8, 3);
    tail = TailInsert(tail, 7, 0);
    poly4 = Sort(poly4);
    print(poly4);
    LNode *poly5 = InitList(NULL);
    tail = poly5;
    tail = TailInsert(tail, 4, 4);
    tail = TailInsert(tail, 2, 5);
    tail = TailInsert(tail, 1, 3);
    tail = TailInsert(tail, 3, 1);
    tail = TailInsert(tail, 4, 0);
    tail = TailInsert(tail, 7, 2);
    poly5 = Sort(poly5);
    print(poly5);
    printf("Subtraction Result:\n");
    LNode *diff = Subtract(poly4, poly5);
    print(diff);

    printf("Example3:\n");
    LNode *poly7 = InitList(NULL);
    tail = poly7;
    tail = TailInsert(tail, 1, 1);
    tail = TailInsert(tail, 2, 0);
    tail = TailInsert(tail, 3, 2);
    tail = TailInsert(tail, 4, 3);
    print(poly7);
    LNode *poly8 = InitList(NULL);
    tail = poly8;
    tail = TailInsert(tail, 4, 1);
    tail = TailInsert(tail, 5, 0);
    tail = TailInsert(tail, 6, 2);
    print(poly8);
    printf("Multiplication Result:\n");
    LNode *product = Multiply(poly7, poly8);
    print(product);

    FreeList(poly1);
    FreeList(poly2);
    FreeList(sum);
    FreeList(poly4);
    FreeList(poly5);
    FreeList(diff);
    FreeList(poly7);
    FreeList(poly8);
    FreeList(product);
    return 0;
}
