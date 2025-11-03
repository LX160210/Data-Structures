#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
#define M 1000
int N = 7;
int visited[MAXSIZE];

// 图的顶点结构体
typedef struct Vertice
{
    char v[MAXSIZE];
    int weight;
} Vertice;

// 邻接矩阵表示的有向图
typedef struct AMGraph
{
    Vertice V[MAXSIZE];
    int A[MAXSIZE][MAXSIZE];
} AMGraph;

// 队列结构体
typedef struct Queue
{
    Vertice data[MAXSIZE];
    int front;
    int rear;
    int length;
} Queue;

// 重置访问数组
void ResetVisited()
{
    for (int i = 0; i < MAXSIZE; i++)
    {
        visited[i] = 0;
    }
}

// 初始化队列
void InitQueue(Queue *q)
{
    q->front = 0;
    q->rear = 0;
    q->length = 20;
}

// 入队
void EnQueue(Queue *q, Vertice v)
{
    if ((q->rear + 1) % q->length == q->front)
    {
        printf("队列满\n");
        return;
    }
    q->data[q->rear] = v;
    q->rear = (q->rear + 1) % q->length;
}

// 出队
Vertice DeQueue(Queue *q)
{
    if (q->front == q->rear)
    {
        printf("队列空\n");
        return (Vertice){0};
    }
    Vertice V = q->data[q->front];
    q->front = (q->front + 1) % q->length;
    return V;
}

// 初始化图的邻接矩阵
void InitGraph(AMGraph *G, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            G->A[i][j] = M;
        }
    }
    for (int i = 0; i < n; i++)
    {
        G->A[i][i] = 0;
    }
    G->A[1][2] = 5;
    G->A[1][4] = 7;
    G->A[2][3] = 4;
    G->A[3][1] = 8;
    G->A[3][6] = 9;
    G->A[4][3] = 5;
    G->A[4][6] = 6;
    G->A[5][4] = 5;
    G->A[6][1] = 3;
    G->A[6][5] = 1;
}

// 初始化图的顶点信息
void InitVertices(AMGraph *G, int n)
{
    for (int i = 0; i < n; i++)
    {
        G->V[i].v[0] = 'V';
        G->V[i].v[1] = i + '0';
        G->V[i].v[2] = '\0';
    }
}
// 深度优先搜索
void DFS(AMGraph *G, int v, int n)
{
    visited[v] = 1;
    printf("Visiting: %s/%d\n", G->V[v].v, G->V[v].weight);
    for (int i = 0; i < n; i++)
    {
        if (G->A[v][i] != 0 && G->A[v][i] != M && visited[i] == 0)
        {
            G->V[i].weight = G->A[v][i];
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
    while (q->front != q->rear)
    {
        Vertice current = DeQueue(q);
        int pos = current.v[1] - '0';
        printf("%s/%d ", current.v, current.weight);
        for (int i = 0; i < n; i++)
        {
            if (G->A[pos][i] != 0 && G->A[pos][i] != M && visited[i] == 0)
            {
                G->V[i].weight = G->A[pos][i];
                EnQueue(q, G->V[i]);
                visited[i] = 1;
            }
        }
    }
}

int main()
{
    AMGraph *G1 = (AMGraph *)malloc(sizeof(AMGraph));
    InitGraph(G1, N);
    InitVertices(G1, N);
    ResetVisited();
    DFS(G1, 1, N);

    Queue q;
    InitQueue(&q);
    AMGraph *G2 = (AMGraph *)malloc(sizeof(AMGraph));
    InitGraph(G2, N);
    InitVertices(G2, N);
    ResetVisited();
    BFS(G2, &q, 1, N);

    free(G1);
    free(G2);
    return 0;
}