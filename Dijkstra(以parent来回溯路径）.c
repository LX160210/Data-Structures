#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100
#define INF 9999
#define N 8
int visited[MAXSIZE];
int path[MAXSIZE];
int parent[MAXSIZE];

// 顶点结构体
typedef struct Vertice
{
    char v[MAXSIZE]; // 顶点名称
} Vertice;

// 邻接矩阵
typedef struct AMGraph
{
    Vertice V[MAXSIZE];           // 顶点数组
    int weight[MAXSIZE][MAXSIZE]; // 邻接矩阵权值
} AMGraph;

// 初始化顶点信息
void InitVertice(AMGraph *G)
{
    strcpy(G->V[1].v, "信科大楼");
    strcpy(G->V[2].v, "数字图书馆");
    strcpy(G->V[3].v, "二教");
    strcpy(G->V[4].v, "中心食堂");
    strcpy(G->V[5].v, "宁静苑十舍");
    strcpy(G->V[6].v, "二维码实验大楼");
    strcpy(G->V[7].v, "老图书馆");
}

// 初始化邻接矩阵权值
void Initweight(AMGraph *G)
{
    for (int i = 1; i < N; i++)
    {
        for (int j = 1; j < N; j++)
        {
            if (i == j)
                G->weight[i][j] = 0;
            else
                G->weight[i][j] = INF;
        }
    }
    G->weight[1][2] = 2;
    G->weight[1][3] = 4;
    G->weight[1][6] = 7;
    G->weight[2][4] = 3;
    G->weight[2][5] = 6;
    G->weight[2][7] = 1;
    G->weight[3][4] = 1;
    G->weight[3][6] = 5;
    G->weight[4][5] = 8;
    G->weight[4][6] = 2;
    G->weight[4][7] = 2;
    G->weight[5][6] = 3;
    G->weight[5][7] = 1;
    G->weight[6][7] = 4;
    for (int i = 1; i < N; i++)
    {
        for (int j = 1; j < N; j++)
        {
            G->weight[j][i] = G->weight[i][j];
        }
    }
}

// 重置访问数组
void Resetvisited()
{
    for (int i = 0; i < N; i++)
    {
        visited[i] = 0;
    }
}

// 检查是否还有未访问的顶点
int check()
{
    for (int i = 1; i < N; i++)
    {
        if (visited[i] == 0)
            return 1;
    }
    return 0;
}

// 打印路径函数
void printpath(AMGraph *G, int v)
{
    if (parent[v] == -1)
    {
        printf("%s-->", G->V[v].v);
        return;
    }
    printpath(G, parent[v]);
    printf("%s-->", G->V[v].v);
}

// 打印最短路径和距离
void print(AMGraph *G, int v)
{
    for (int i = 1; i < N; i++)
    {
        printf("从 %s 到 %s 的最短路径: %dkm\n", G->V[v].v, G->V[i].v, path[i]);
    }
    for (int i = 1; i < N; i++)
    {
        printpath(G, i);
        printf("NULL\n");
    }
}

// Dijkstra 算法实现
void Dijkstra(AMGraph *G, int v)
{
    Resetvisited();
    for (int i = 1; i < N; i++)
    {
        parent[i] = -1;
    }
    for (int i = 1; i < N; i++)
    {
        path[i] = INF;
    }
    path[v]=0;
    while (check())
    {
        int min = INF;
        int k;
        for (int i = 1; i < N; i++)
        {
            if (path[i] < min && visited[i] == 0)
            {
                min = path[i];
                k = i;
            }
        }
        visited[k] = 1;
        for (int i = 1; i < N; i++)
        {
            if (G->weight[k][i] + path[k] < path[i] && visited[i] == 0)
            {
                path[i] = path[k] + G->weight[k][i];
                parent[i] = k;
            }
        }
    }
    print(G, v);
}

// 主函数
int main()
{
    AMGraph *G = (AMGraph *)malloc(sizeof(AMGraph));
    InitVertice(G);
    Initweight(G);
    Dijkstra(G, 1);
    free(G);
    return 0;
}
