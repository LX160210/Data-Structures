#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
int visited[MAXSIZE];
int N = 7;

// 重置访问数组
void Resetvisited()
{
  for (int i = 0; i < N; i++)
  {
    visited[i] = 0;
  }
}

// 图的顶点结构体
typedef struct Vertice
{
  char v[MAXSIZE];
} Vertice;

// 邻接表的邻接点结构体
typedef struct Adjvex
{
  int data;            // 权值
  struct Adjvex *next; // 指向下一个邻接点
  int info;            // 邻接点编号
  // int p;
} Adjvex;

// 邻接表表示的有向图
typedef struct AMGraph
{
  Vertice V[MAXSIZE];
  Adjvex head[MAXSIZE];
  Adjvex A[MAXSIZE][MAXSIZE];
} AMGraph;

// 队列结构体
typedef struct Queue
{
  int front;
  int rear;
  int length;
  Adjvex *data[MAXSIZE];
} Queue;

// 初始化队列
void InitQueue(Queue *q)
{
  q->front = 0;
  q->rear = 0;
  q->length = 20;
}

// 入队
void EnQueue(Queue *q, Adjvex *a)
{
  if ((q->rear + 1) % q->length == q->front)
  {
    printf("队列满\n");
    return;
  }
  q->data[q->rear] = a;
  q->rear = (q->rear + 1) % q->length;
}

// 出队
Adjvex *DeQueue(Queue *q)
{
  if (q->rear == q->front)
  {
    printf("队列空\n");
    return NULL;
  }
  Adjvex *a = q->data[q->front];
  q->front = (q->front + 1) % q->length;
  return a;
}

// 初始化图的顶点信息
void InitVertice(AMGraph *G, int n)
{
  for (int i = 1; i < n; i++)
  {
    G->V[i].v[0] = 'V';
    G->V[i].v[1] = i + '0';
    G->V[i].v[2] = '\0';
  }
}

// 初始化图的邻接表
void InitAdjvex(AMGraph *G, int n)
{
  G->head[1].next = &G->A[1][2];
  G->head[1].info = 1;
  G->A[1][2].data = 5;
  G->A[1][2].info = 2;
  G->A[1][2].next = &G->A[1][4];
  G->A[1][4].data = 7;
  G->A[1][4].info = 4;
  G->A[1][4].next = NULL;
  G->head[2].next = &G->A[2][3];
  G->head[2].info = 2;
  G->A[2][3].data = 4;
  G->A[2][3].info = 3;
  G->A[2][3].next = NULL;
  G->head[3].next = &G->A[3][1];
  G->head[3].info = 3;
  G->A[3][1].data = 8;
  G->A[3][1].info = 1;
  G->A[3][1].next = &G->A[3][6];
  G->A[3][6].data = 9;
  G->A[3][6].info = 6;
  G->A[3][6].next = NULL;
  G->head[4].next = &G->A[4][3];
  G->head[4].info = 4;
  G->A[4][3].data = 5;
  G->A[4][3].info = 3;
  G->A[4][3].next = &G->A[4][6];
  G->A[4][6].data = 6;
  G->A[4][6].info = 6;
  G->A[4][6].next = NULL;
  G->head[5].next = &G->A[5][4];
  G->head[5].info = 5;
  G->A[5][4].data = 5;
  G->A[5][4].info = 4;
  G->A[5][4].next = NULL;
  G->head[6].next = &G->A[6][1];
  G->head[6].info = 6;
  G->A[6][1].data = 3;
  G->A[6][1].info = 1;
  G->A[6][1].next = &G->A[6][5];
  G->A[6][5].data = 1;
  G->A[6][5].info = 5;
  G->A[6][5].next = NULL;
  // continue
}

// 深度优先搜索
void DFS(AMGraph *G, int v, int n)
{
  visited[v] = 1;
  printf("Visiting: %s\n", G->V[v].v);
  Adjvex *current = G->head[v].next;
  while (visited[current->info] == 1)
  {
    current = current->next;
    if (!current)
    {
      return;
    }
  }
  for (int i = 1; i < N; i++)
  {
    if (current->info == i && visited[i] == 0)
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
  EnQueue(q, &G->head[v]);
  while (q->rear != q->front)
  {
    Adjvex *current = DeQueue(q);
    int pos = current->info;
    printf("%s ", G->V[pos].v);
    while (current != NULL)
    {
      current = current->next;
      if(!current)
      {
        break;
      }
      if (visited[current->info] == 0)
      {
        EnQueue(q, &G->head[current->info]);
        visited[current->info] = 1;
      }
    }
  }
}

int main()
{
  AMGraph G;
  InitVertice(&G, N);
  InitAdjvex(&G, N);

  Resetvisited();
  printf("Depth First Search:\n");
  DFS(&G, 1, N);

  Resetvisited();
  Queue q;
  InitQueue(&q);
  printf("\nBreadth First Search:\n");
  BFS(&G, &q, 1, N);

  return 0;
}
