#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
int visited[MAXSIZE];

// 图的顶点结构体
typedef struct Vertice
{
    char v[20];
} Vertice;

// 图的邻接矩阵结构体
typedef struct AMGraph
{
    Vertice V[MAXSIZE];
    int A[MAXSIZE][MAXSIZE];
} AMGraph;

// 队列结构体
typedef struct Queue
{
    int front;
    int rear;
    Vertice data[MAXSIZE];
} Queue;

// 初始化队列
void InitQueue(Queue *q)
{
    q->front = 0;
    q->rear = 0;
}

// 入队
void EnQueue(Queue *q, Vertice v)
{
    if ((q->rear + 1) % MAXSIZE == q->front)
    {
        printf("队满\n");
    }
    q->data[q->rear] = v;
    q->rear = (q->rear + 1) % MAXSIZE;
}

// 出队
Vertice DeQueue(Queue *q)
{
    if (q->rear == q->front)
    {
        printf("队空\n");
    }
    Vertice v = q->data[q->front];
    q->front = (q->front + 1) % MAXSIZE;
    return v;
}

// 初始化图的顶点
void InitGraph(AMGraph *G, int n)
{
    for (int i = 0; i < n; i++)
    {
        G->V[i].v[0] = 'V';
        G->V[i].v[1] = i + '1';
        G->V[i].v[2] = '\0';
    }
}

// 创建图的邻接矩阵
void CreateGraph(AMGraph *G, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            G->A[i][j] = 0;
        }
    }
    G->A[0][1] = 1;
    G->A[0][2] = 1;
    G->A[0][4] = 1;
    G->A[1][5] = 1;
    G->A[2][3] = 1;
    G->A[2][4] = 1;
    G->A[3][4] = 1;
    G->A[3][5] = 1;
    G->A[4][5] = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            G->A[j][i] = G->A[i][j];
        }
    }
}

// 深度优先搜索
void DFS(AMGraph *G, int v, int n)
{
    visited[v] = 1;
    printf("Visiting: %s\n", G->V[v].v);
    for (int i = 0; i < n; i++)
    {
        if (G->A[v][i] == 1 && visited[i] == 0)
        {
            DFS(G, i, n);
        }
    }
}

// 广度优先搜索
void BFS(AMGraph *G, Queue *q, int v, int n)
{
    visited[v] = 1;
    printf("Visiting: ");
    EnQueue(q, G->V[v]);
    while (q->rear != q->front)
    {
        Vertice current = DeQueue(q);
        int v = current.v[1] - '0';
        printf("%s ", current.v);
        for (int i = 0; i < n; i++)
        {
            if (G->A[v][i] == 1 && visited[i] == 0)
            {
                EnQueue(q, G->V[i]);
                visited[i] = 1;
            }
        }
    }
}

int main()
{
    AMGraph G;
    InitGraph(&G, 6);
    CreateGraph(&G, 6);
    for (int i = 0; i < 6; i++)
    {
        visited[i] = 0;
    }
    DFS(&G, 1, 6);
    Queue Q;
    InitQueue(&Q);
    AMGraph G2;
    InitGraph(&G2, 6);
    CreateGraph(&G2, 6);
    for (int i = 0; i < 6; i++)
    {
        visited[i] = 0;
    }
    BFS(&G2, &Q, 1, 6);
    return 0;

}
