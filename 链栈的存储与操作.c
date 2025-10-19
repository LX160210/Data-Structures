#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

typedef char ElemType;

typedef struct Stack
{
    ElemType data;
    struct Stack *next;
    int top;
} Stack;

// 初始化
void InitStack(Stack *s)
{
    s->next = NULL;
    s->top = -1;
}

// 入栈
Stack *push(Stack *s, ElemType e)
{
    if (s->top >= MAXSIZE - 1)
    {
        printf("栈满\n");
        return NULL;
    }
    struct Stack *p = (Stack *)malloc(sizeof(Stack));
    p->next = s;
    p->data = e;
    p->top = s->top + 1;
    return p;
}

// 出栈
Stack *pop(Stack *s)
{
    if (s->top <= -1)
    {
        printf("栈空\n");
        return NULL;
    }
    Stack *p = s;
    s = p->next;
    free(p);
    return s;
}

// 取栈顶元素
ElemType get(Stack *s)
{
    ElemType e;
    if (s->top <= -1)
    {
        printf("栈空\n");
        return -1;
    }
    e = s->data;
    return e;
}

// 检查栈空栈满
void check(Stack *s)
{
    if (s->top == -1)
    {
        printf("栈空\n");
        return;
    }
    else if (s->top == MAXSIZE - 1)
    {
        printf("栈满\n");
        return;
    }
    else
    {
        printf("栈不空也不满\n");
        return;
    }
}

// 检验清空栈
Stack *clear(Stack *s)
{
    if (s->top == -1)
    {
        printf("栈空\n");
        return NULL;
    }
    while (s->top != -1)
    {
        Stack *p = s;
        s = s->next;
        free(p);
    }
    return s;
}

int main()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    InitStack(s);
    s = push(s, 'a');        // a 0
    s = push(s, 'b');        // a b 1
    s = push(s, 'c');        // a b c 2
    printf("%c\n", s->data); // c
    printf("%d\n", s->top);  // 2
    s = pop(s);              // a b 1
    printf("%c\n", s->data); // b
    printf("%d\n", s->top);  // 1
    printf("%c\n", get(s));  // b
    check(s);                // 栈不空也不满
    s = clear(s);            // 清空栈
    printf("%d\n", s->top);  //-1
    clear(s);                // 清空栈
    check(s);                // 栈空
    return 0;
}