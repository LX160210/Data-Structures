#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;
ElemType ch[] = "ABDH###EIL###J##CF##G#K##";
int idx = 0;

// 二叉树结点定义
typedef struct Tree
{
    ElemType data;
    struct Tree *left;
    struct Tree *right;
} Tree;

// 队列定义
typedef struct Queue
{
    Tree *data[10];
    int front;
    int rear;
} Queue;

// 初始化队列
void InitQueue(Queue *q)
{
    q->front = 0;
    q->rear = 0;
}

// 入队
void EnQueue(Queue *q, Tree *T)
{
    if ((q->rear + 1) % 10 == q->front)
    {
        printf("队列满\n");
        return;
    }
    if (!T)
    {
        return;
    }
    q->data[q->rear] = T;
    q->rear = (q->rear + 1) % 10;
}

// 出队
Tree *DeQueue(Queue *q)
{
    if (q->front == q->rear)
    {
        printf("队列空\n");
        return NULL;
    }
    Tree *t = q->data[q->front];
    q->front = (q->front + 1) % 10;
    return t;
}

// 前序创建二叉树
void CreateTree(Tree **T)
{
    ElemType e;
    e = ch[idx++];
    if (e == '#')
    {
        *T = NULL;
    }
    else
    {
        *T = (Tree *)malloc(sizeof(Tree));
        (*T)->data = e;
        CreateTree(&(*T)->left);
        CreateTree(&(*T)->right);
    }
}

// 前序遍历
void PreOrder(Tree *T)
{
    if (T)
    {
        printf("%c ", T->data);
        PreOrder(T->left);
        PreOrder(T->right);
    }
}

// 中序遍历
void InOrder(Tree *T)
{
    if (T)
    {
        InOrder(T->left);
        printf("%c ", T->data);
        InOrder(T->right);
    }
}

// 后序遍历
void PostOrder(Tree *T)
{
    if (T)
    {
        PostOrder(T->left);
        PostOrder(T->right);
        printf("%c ", T->data);
    }
}

// 层序遍历
void LevelOrder(Tree *T)
{
    if (!T)
    {
        printf("该树为空");
        return;
    }
    Queue *q = (Queue *)malloc(sizeof(Queue));
    InitQueue(q);
    EnQueue(q, T);
    while (q->rear != q->front)
    {
        Tree *t = DeQueue(q);
        printf("%c ", t->data);
        if (t->left)
            EnQueue(q, t->left);
        if (t->right)
            EnQueue(q, t->right);
    }
    printf("\n");
}

// 清空二叉树
void Clear(Tree **T)
{
    if (*T)
    {
        Clear(&(*T)->left);
        Clear(&(*T)->right);
        *T = NULL;
        free(*T);
    }
}
int main()
{
    Tree *T;
    CreateTree(&T);
    PreOrder(T);
    printf("\n");
    InOrder(T);
    printf("\n");
    PostOrder(T);
    printf("\n");
    LevelOrder(T);
    Clear(&T);
    LevelOrder(T);
    return 0;
}
