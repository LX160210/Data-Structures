#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char ElemType;

int weight[9] = {0, 5, 29, 7, 8, 14, 23, 3, 11};
ElemType data[9] = {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

// 哈夫曼树结点定义
typedef struct HuffmanTree
{
    ElemType data;
    int weight;
    int parent;
    int Left;
    int Right;
    int info;
} HuffmanTree;

// 哈夫曼编码定义
typedef struct HuffmanCode
{
    char code[20];
} HuffmanCode;

// 哈夫曼编码栈定义
typedef struct HuffmanStack
{
    int data[20];
    int top;
} HuffmanStack;

// 栈初始化
void InitStack(HuffmanStack *hs)
{
    hs->top = 0;
}

// 入栈
void push(HuffmanStack *hs, int e)
{
    if (hs->top == 19)
    {
        printf("栈满");
        return;
    }
    hs->top++;
    hs->data[hs->top] = e;
}

// 出栈
int pop(HuffmanStack *hs)
{
    if (hs->top == 0)
    {
        printf("栈空");
        return -1;
    }
    int e = hs->data[hs->top];
    hs->top--;
    return e;
}

// 为哈夫曼树结点添加编码信息
/*void addHuffmancode(HuffmanTree *HT,int n){
    for(int i=n+1;i<2*n;i++){
        HT[HT[i].Left].info=0;
        HT[HT[i].Right].info=1;
    }
    return ;
}*/

// 构建哈夫曼编码
void Buildcode(HuffmanTree *HT, int n, HuffmanStack *HS, HuffmanCode *HC)
{
    // 为哈夫曼树结点添加编码信息
    for (int i = n + 1; i < 2 * n; i++)
    {
        HT[HT[i].Left].info = 0;
        HT[HT[i].Right].info = 1;
    }
    // 生成哈夫曼编码
    for (int i = 1; i < n + 1; i++)
    {
        int count = 1;
        int p = HT[i].parent;
        int j = i;
        InitStack(&HS[i]);
        while (p != 2 * n - 1)
        {
            p = HT[p].parent;
            count++;
        }
        while (count != 0)
        {
            push(&HS[i], HT[j].info);
            j = HT[j].parent;
            count--;
        }
    }
    for (int i = 1; i < n + 1; i++)
    {
        int k = 1;
        while (HS[i].top != 0)
        {
            HC[i].code[k] = pop(&HS[i]) + '0';
            k++;
        }
        HC[i].code[k] = '\0';
    }
}

// 打印哈夫曼编码
void Printcode(HuffmanCode *HC, int n, HuffmanTree *HT)
{
    for (int i = 1; i < n + 1; i++)
    {
        printf("%d  %c HuffmanCode:  ", i, HT[i].data);
        for (int j = 1; j < 20; j++)
        {
            if (HC[i].code[j] == '\0')
            {
                break;
            }
            printf("%c ", HC[i].code[j]);
        }
        printf("\n");
    }
}

// 检查是否还有未合并的结点
bool Check(HuffmanTree *HT, int p)
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

// 选择未合并的最小权重结点
int Select(HuffmanTree *HT, int p)
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

// 创建哈夫曼树
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
    while (Check(HT, p))
    {
        int s1 = Select(HT, p);
        HT[s1].parent = p;
        int s2 = Select(HT, p);
        HT[s2].parent = p;
        HT[p].weight = HT[s1].weight + HT[s2].weight;
        HT[p].Left = s1;
        HT[p].Right = s2;
        p++;
    }
    return HT;
}

// 打印哈夫曼树
void Printtree(HuffmanTree *HT, int n)
{
    for (int i = 1; i < 2 * n; i++)
    {
        printf("%d  %c  weight:%d  parent:%d  Left:%d  Right:%d  \n", i, HT[i].data, HT[i].weight, HT[i].parent, HT[i].Left, HT[i].Right);
    }
    return;
}

int main()
{
    HuffmanCode HuffmanCode[9];
    HuffmanStack HuffmanStack[9];
    HuffmanTree *T = Create(8);
    Printtree(T, 8);
    // addHuffmancode(T,8);
    Buildcode(T, 8, HuffmanStack, HuffmanCode);
    Printcode(HuffmanCode, 8, T);
    return 0;
}