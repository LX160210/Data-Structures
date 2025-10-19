#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;
int idx = 0;
ElemType ch[] = "ABDH#K###E##CFI###G#J##";

typedef struct Tree
{
    ElemType data;
    struct Tree *LTree;
    struct Tree *RTree;
} Tree;

void InitTree(Tree *T)
{
    T->LTree = NULL;
    T->RTree = NULL;
}

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
        CreateTree(&((*T)->LTree));
        CreateTree(&((*T)->RTree));
    }
}

void print(Tree *T)
{
    if (T != NULL)
    {
        printf("%c ", T->data);
        print(T->LTree);
        print(T->RTree);
    }
}

int main()
{
    Tree *T;
    InitTree(T);
    CreateTree(&T);
    print(T);
    return 0;
}