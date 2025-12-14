#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
#define N 8
#define INF 9999

typedef struct Edge
{
    int u, v, w;
} Edge;

Edge edges[MAXSIZE];
int parent[MAXSIZE];
int cnt;

typedef struct Vertice
{
    char v[4];
} Vertice;

typedef struct AMGraph
{
    Vertice V[MAXSIZE];
    int weight[MAXSIZE][MAXSIZE];
} AMGraph;

void InitVertice(AMGraph *G)
{
    for (int i = 1; i <= N; i++)
    {
        G->V[i].v[0] = 'V';
        G->V[i].v[1] = i + '0';
        G->V[i].v[2] = '\0';
    }
}

void Initweight(AMGraph *G)
{
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            if (i == j)
                G->weight[i][j] = 0;
            else
                G->weight[i][j] = INF;
        }
    }
    G->weight[1][2] = 4;
    G->weight[1][3] = 3;
    G->weight[1][4] = 2;
    G->weight[1][7] = 7;
    G->weight[2][3] = 1;
    G->weight[2][4] = 2;
    G->weight[2][6] = 5;
    G->weight[2][8] = 5;
    G->weight[3][4] = 4;
    G->weight[3][5] = 2;
    G->weight[3][8] = 6;
    G->weight[4][5] = 3;
    G->weight[4][6] = 2;
    G->weight[5][6] = 3;
    G->weight[5][7] = 1;
    G->weight[6][7] = 4;
    G->weight[6][8] = 7;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            G->weight[j][i] = G->weight[i][j];
        }
    }
}

void InitAMGraph(AMGraph *G)
{
    InitVertice(G);
    Initweight(G);
    printf("The adjacency matrix weights are as follows:\n");
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            if (G->weight[i][j] == INF)
                printf("INF ");
            else
                printf(" %d  ", G->weight[i][j]);
        }
        printf("\n");
    }
}

void Prepare(AMGraph *G, Edge edges[])
{
    cnt = 0;
    for (int i = 1; i < N + 1; i++)
    {
        for (int j = i + 1; j < N + 1; j++)
        {
            if (G->weight[i][j] != INF && G->weight[i][j] != 0)
            {
                edges[cnt].u = i;
                edges[cnt].v = j;
                edges[cnt].w = G->weight[i][j];
                cnt++;
            }
        }
    }
}

int cmp(const void *a, const void *b)
{
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;
    return e1->w - e2->w;
}

int find(int x)
{
    if (parent[x] != x)
    {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_sets(int u, int v)
{
    int fu = find(u);
    int fv = find(v);
    if (fu != fv)
        parent[fu] = fv;
}

void Kruskal(AMGraph *G, Edge edges[])
{
    Prepare(G, edges);
    qsort(edges, cnt, sizeof(Edge), cmp);
    for (int i = 1; i < N + 1; i++)
        parent[i] = i;
    int k = 0;
    int total_weight = 0;
    for (int i = 0; i < cnt && k < N - 1; i++)
    {
        Edge edge = edges[i];
        if (find(edge.u) != find(edge.v))
        {
            union_sets(edge.u, edge.v);
            k++;
            total_weight += edge.w;
            printf("Edge:(%d,%d) Weight:%d\n", edge.u, edge.v, edge.w);
        }
    }
    printf("Total weight of MST: %d\n", total_weight);
}

int main()
{
    AMGraph *G = (AMGraph *)malloc(sizeof(AMGraph));
    InitAMGraph(G);
    Kruskal(G, edges);
    free(G);
    return 0;
}