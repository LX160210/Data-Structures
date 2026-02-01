#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode
{
    int data;
    struct QueueNode *next;
    struct QueueNode *rear;
} QueueNode;

QueueNode *InitQueue()
{
    QueueNode *q = (QueueNode *)malloc(sizeof(QueueNode));
    q->next = NULL;
    q->rear = q;
    return q;
}

int EnQueue(QueueNode *q, int x)
{
    QueueNode *new = (QueueNode *)malloc(sizeof(QueueNode));
    new->data = x;
    new->next = NULL;
    q->rear->next = new;
    q->rear = new;
    return 1;
}

int DeQueue(QueueNode *q, int *x)
{
    if (q->next)
    {
        QueueNode *toDe = q->next;
        *x = toDe->data;
        q->next = toDe->next;
        free(toDe);
        if (q->next == NULL)
            q->rear = q;
        printf("DeQUeue: %d\n", *x);
        return 1;
    }
    printf("Empty\n");
    return -1;
}

int IsEmpty(QueueNode *q)
{
    if (q->next)
    {
        printf("Not Empty\n");
        return 0;
    }
    printf("Empty\n");
    return 1;
}

int main()
{
    QueueNode *q = InitQueue();
    EnQueue(q, 10);
    EnQueue(q, 20);
    EnQueue(q, 30);
    int x;
    DeQueue(q, &x);
    DeQueue(q, &x);
    IsEmpty(q);
    DeQueue(q, &x);
    IsEmpty(q);
    return 0;
}
