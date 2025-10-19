#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 5

typedef char ElemType;

typedef struct Queue
{
    ElemType data[MAXSIZE];
    int front;
    int rear;
} Queue;

// 初始化
void InitQueue(Queue *q)
{
    q->front = 0;
    q->rear = 0;
}

// 入队
void EnQueue(Queue *q, ElemType e)
{
    if (q->front == ((q->rear + 1) % MAXSIZE))
    {
        printf("队列满\n");
        return;
    }
    q->data[q->rear] = e;
    q->rear = (q->rear + 1) % MAXSIZE;
    return;
}

// 出队
void DeQueue(Queue *q, ElemType *e)
{
    if (q->front == q->rear)
    {
        printf("队列空\n");
        return;
    }
    *e = q->data[q->front];
    q->front = (q->front + 1) % MAXSIZE;
    return;
}

// 遍历
void print(Queue *q)
{
    if (q->front == q->rear)
    {
        printf("队列空\n");
        return;
    }
    int info = q->front;
    printf("队列元素：");
    while (info != q->rear)
    {
        printf("%c ", q->data[info]);
        info = (info + 1) % MAXSIZE;
    }
    printf("\n");
    return;
}

// 检查队空队满
void check(Queue *q)
{
    if (q->front == q->rear)
    {
        printf("队空\n");
        return;
    }
    else if (q->front == ((q->rear + 1) % MAXSIZE))
    {
        printf("队满\n");
        return;
    }
    else
    {
        printf("队不空也不满\n");
        return;
    }
}

// 清空队列
void DsQueue(Queue *q)
{
    if (q->front == q->rear)
    {
        printf("队列空\n");
        return;
    }
    q->front = 0;
    q->rear = 0;
    return;
}
int main()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    InitQueue(q);
    EnQueue(q, 'a');
    printf("%c\n", q->data[(q->rear - 1 + MAXSIZE) % MAXSIZE]);
    EnQueue(q, 'b');
    printf("%c\n", q->data[(q->rear - 1 + MAXSIZE) % MAXSIZE]);
    EnQueue(q, 'c');
    EnQueue(q, 'd');
    EnQueue(q, 'e');
    EnQueue(q, 'f');
    check(q);
    print(q);
    ElemType e;
    DeQueue(q, &e);
    printf("出队元素：%c\n", e);
    EnQueue(q, 'g');
    print(q);
    DsQueue(q);
    print(q);
    free(q);
    return 0;
}