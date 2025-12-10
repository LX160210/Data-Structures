#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
#define M 1000
#define N 6 // 顶点数为6，只用1~6号顶点
int visited[MAXSIZE];
int parent[MAXSIZE];
int count = 0;

typedef struct Vertice
{
    char v[MAXSIZE];
    int weight;
} Vertice;

typedef struct AMGraph
{
    Vertice V[MAXSIZE];
    int A[MAXSIZE][MAXSIZE];
} AMGraph;

void InitGraph(AMGraph *G, int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
                G->A[i][j] = 0;
            else
                G->A[i][j] = M;
        }
    }
    // 只赋值一遍
    G->A[1][2] = 5;
    G->A[1][3] = 8;
    G->A[1][4] = 7;
    G->A[1][6] = 3;
    G->A[2][3] = 4;
    G->A[2][5] = 2;
    G->A[3][4] = 5;
    G->A[3][6] = 9;
    G->A[4][6] = 6;
    G->A[4][5] = 5;
    G->A[5][6] = 1;

    // 统一对称赋值
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            G->A[j][i] = G->A[i][j];
        }
    }
}

void InitVertices(AMGraph *G, int n)
{
    for (int i = 1; i <= n; i++)
    {
        G->V[i].v[0] = 'V';
        G->V[i].v[1] = i + '0';
        G->V[i].v[2] = '\0';
    }
}

void Resetvisited()
{
    for (int i = 1; i <= N; i++)
    {
        visited[i] = 0;
    }
}

int check()
{
    for (int i = 1; i <= N; i++)
    {
        if (visited[i] == 0)
            return 1;
    }
    return 0;
}

void Prim(AMGraph *G, int v)
{
    Resetvisited();
    visited[v] = 1;
    int k, p;
    while (check())
    {
        int MIN = M + 1;
        k = -1;
        p = -1;
        for (int i = 1; i <= N; i++)
        {
            if (visited[i])
            {
                for (int j = 1; j <= N; j++)
                {
                    if (!visited[j] && G->A[i][j] < MIN)
                    {
                        MIN = G->A[i][j];
                        k = j;
                        p = i;
                    }
                }
            }
        }
        if (k != -1 && p != -1)
        {
            visited[k] = 1;
            parent[k] = p;
            printf("(%s,%s) weight:%d\n", G->V[p].v, G->V[k].v, G->A[p][k]);
        }
    }
}

int main()
{
    AMGraph *G = (AMGraph *)malloc(sizeof(AMGraph));
    InitVertices(G, N);
    InitGraph(G, N);
    Prim(G, 1);
    free(G);
    return 0;
}