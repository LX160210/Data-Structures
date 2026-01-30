#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int id;
    struct Node *next;
} Node;

Node *InitList()
{
    Node *L = (Node *)malloc(sizeof(Node));
    L->id = 1;
    L->next = L;
    return L;
}

int InsertTail(Node *L, int x)
{
    Node *p = L;
    while (p->next != L)
    {
        p = p->next;
    }
    Node *newnode = (Node *)malloc(sizeof(Node));
    newnode->id = x;
    p->next = newnode;
    newnode->next = L;
    return 1;
}

Node *CreateJosephus(int n)
{
    Node *L = InitList();
    for (int i = 2; i < n + 1; i++)
    {
        InsertTail(L, i);
    }
    return L;
}

int Josephus(int n, int k)
{
    Node *p = CreateJosephus(n);
    if (k == 1)
    {
        return n;
    }
    else
    {
        int step = k - 2;
        while (p->next != p)
        {
            for (int i = 1; i < step + 1; i++)
            {
                p = p->next;
            }
            Node *toDelete = p->next;
            p->next = toDelete->next;
            free(toDelete);
            p = p->next;
        }
        return p->id;
    }
}

int main()
{
    printf("%d ", Josephus(5, 1));
    printf("%d ", Josephus(7, 3));
    printf("%d ", Josephus(10, 4));
    return 0;
}
