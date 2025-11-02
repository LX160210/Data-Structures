#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char ElemType;

ElemType E[] = "aaaaaaabbbbbccdddd\0";
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
    printf("\n");
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
    printf("\n");
    return;
}

// 统计字符出现频率
void valuewieght(ElemType *e, int n)
{
    int count[26];
    for (int i = 0; i < 26; i++)
    {
        count[i] = 0;
    }
    while (*e)
    {

        if (*e == 'a')
        {
            count[0]++;
        }
        else if (*e == 'b')
        {
            count[1]++;
        }
        else if (*e == 'c')
        {
            count[2]++;
        }
        else if (*e == 'd')
        {
            count[3]++;
        }
        e++;
    }
    for (int i = 0; i < 9; i++)
    {
        weight[i] = 0;
        data[i] = ' ';
    }
    for (int i = 0; i < n; i++)
    {
        data[i + 1] = 'a' + i;
        weight[i + 1] = count[i];
    }
}

// 编码
char *translate1(ElemType *e)
{
    char *code = (char *)malloc(100 * sizeof(char));
    char *head = code;
    while (*e)
    {
        if (*e == 'a')
        {
            *code = '0';
            code++;
        }
        else if (*e == 'b')
        {
            *code = '1';
            code++;
            *code = '0';
            code++;
        }
        else if (*e == 'c')
        {
            *code = '1';
            code++;
            *code = '1';
            code++;
            *code = '0';
            code++;
        }
        else if (*e == 'd')
        {
            *code = '1';
            code++;
            *code = '1';
            code++;
            *code = '1';
            code++;
        }
        e++;
    }
    *code = '\0';
    printf("%s\n", head);
    return head;
}

// 解码
char *translate2(HuffmanTree *HT, char *code, int n)
{
    ElemType *str = (ElemType *)malloc(100 * sizeof(ElemType));
    ElemType *head = str;
    HuffmanTree *p = &HT[2 * n - 1];
    HuffmanTree *current;
    while (*code)
    {
        current = p;
        while (current->Left != 0 && current->Right != 0)
        {
            if (*code == '0')
            {
                current = &HT[current->Left];
                if (current->Left == 0 && current->Right == 0)
                {
                    *str = current->data;
                    str++;
                }
            }
            else if (*code == '1')
            {
                current = &HT[current->Right];
                if (current->Left == 0 && current->Right == 0)
                {
                    *str = current->data;
                    str++;
                }
            }
            code++;
        }
    }
    *str = '\0';
    printf("%s\n", head);
    return head;
}

int main()
{
    HuffmanCode HuffmanCodes[9];
    HuffmanStack HuffmanStacks[9];
    HuffmanTree *T = Create(8);
    Printtree(T, 8);
    Buildcode(T, 8, HuffmanStacks, HuffmanCodes);
    Printcode(HuffmanCodes, 8, T);

    HuffmanCode HuffmanCodes2[5];
    HuffmanStack HuffmanStacks2[5];
    valuewieght(E, 4);
    HuffmanTree *T2 = Create(4);
    Printtree(T2, 4);
    Buildcode(T2, 4, HuffmanStacks2, HuffmanCodes2);
    Printcode(HuffmanCodes2, 4, T2);
    char *code = translate1(E);
    char *decoded = translate2(T2, code, 4);
    return 0;
}