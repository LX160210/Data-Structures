#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode
{
    int data;
    struct StackNode *next;
} StackNode;

StackNode *InitStack()
{
    StackNode *s = (StackNode *)malloc(sizeof(StackNode));
    s->next = NULL;
    return s;
}

int Push(StackNode *s, int x)
{
    StackNode *new = (StackNode *)malloc(sizeof(StackNode));
    new->data = x;
    new->next = s->next;
    s->next = new;
    return 1;
}

int Pop(StackNode *s)
{
    if (s->next)
    {
        StackNode *toPop = s->next;
        int info = toPop->data;
        s->next = toPop->next;
        free(toPop);
        return info;
    }
    printf("栈空\n");
    return -1;
}

int GetTop(StackNode *s)
{
    if (s->next)
    {
        int info = s->next->data;
        return info;
    }
    printf("栈空\n");
    return -1;
}

int main()
{
    StackNode *s = InitStack();
    Push(s, 10);
    Push(s, 20);
    Push(s, 30);
    printf("栈顶元素为:%d\n", GetTop(s));
    printf("出栈元素为:%d\n", Pop(s));
    printf("栈顶元素为:%d\n", GetTop(s));
    return 0;
}
