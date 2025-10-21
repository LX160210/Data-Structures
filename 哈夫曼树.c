#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char ElemType;

int weight[9] = {0, 5, 29, 7, 8, 14, 23, 3, 11};
ElemType data[9] = {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

typedef struct HuffmanTree
{
    ElemType data;
    int weight;
    int parent;
    int Left;
    int Right;
} HuffmanTree;

bool check(HuffmanTree HT[], int p)
{
    int count = 0;
    for (int i = 1; i < p; i++)
    {
        if (HT[i].parent == 0)
        {
            count++;
        }
    }
    if (count > 1)
    {
        return true;
    }
    return false;
}

int select(HuffmanTree HT[], int p)
{
    int MIN = 999;
    int pos = 0;
    for (int i = 1; i < p; i++)
    {
        if (HT[i].parent == 0 && HT[i].weight < MIN && HT[i].weight != 0)
        {
            MIN = HT[i].weight;
            pos = i;
        }
    }
    return pos;
}

HuffmanTree *Create(int n)
{
    int m = 2 * n - 1;
    HuffmanTree *HT = (HuffmanTree *)malloc((m + 1) * sizeof(HuffmanTree));
    for (int i = 1; i < m + 1; i++)
    {
        HT[i].data = ' ';
        HT[i].weight = 0;
        HT[i].parent = 0;
        HT[i].Left = 0;
        HT[i].Right = 0;
    }
    for (int i = 1; i < n + 1; i++)
    {
        HT[i].data = data[i];
        HT[i].weight = weight[i];
    }
    int p = n + 1;
    while (check(HT, p))
    {
        int s1 = select(HT, p);
        HT[s1].parent = p;
        int s2 = select(HT, p);
        HT[s2].parent = p;
        HT[p].weight = HT[s1].weight + HT[s2].weight;
        HT[p].Left = s1;
        HT[p].Right = s2;
        p++;
    }
    return HT;
}

void print(HuffmanTree *HT, int n)
{
    for (int i = 1; i < 2 * n; i++)
    {
        printf("%d  %c  weight:%d  parent:%d  Left:%d  Right:%d  \n", i, HT[i].data, HT[i].weight, HT[i].parent, HT[i].Left, HT[i].Right);
    }
    return;
}
int main()
{
    HuffmanTree *T = Create(8);
    print(T, 8);
    return 0;
}