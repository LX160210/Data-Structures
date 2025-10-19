#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

char *E1 = "(1-2*3)+4/2#";
char *E2 = "1+2+3-4#";
char *E3 = "3-4+(5*6-7)*8#";

typedef struct OPND
{
    int data[MAXSIZE];
    int top;
} OPND;

typedef struct OPTR
{
    char data[MAXSIZE];
    int top;
} OPTR;

void InitOPND(OPND *s)
{
    s->top = -1;
}

void InitOPTR(OPTR *s)
{
    s->top = 0;
    s->data[s->top] = '#';
}

void pushOPND(OPND *s, int e)
{
    if (s->top > MAXSIZE - 1)
    {
        printf("操作数栈满\n");
        return;
    }
    s->top++;
    s->data[s->top] = e;
}

void pushOPTR(OPTR *s, char e)
{
    if (s->top > MAXSIZE - 1)
    {
        printf("符号栈满\n");
        return;
    }
    s->top++;
    s->data[s->top] = e;
}

int popOPND(OPND *s)
{
    if (s->top < 0)
    {
        printf("操作数栈空\n");
        return -1;
    }
    int e = s->data[s->top];
    s->top--;
    return e;
}

char popOPTR(OPTR *s)
{
    if (s->top < 0)
    {
        printf("符号栈空\n");
        return -1;
    }
    char e = s->data[s->top];
    s->top--;
    return e;
}

int getvalue(char str)
{
    char a = str;

    if (a == '+' || a == '-')
    {
        return 1;
    }
    else if (a == '*' || a == '/')
    {
        return 2;
    }
    else if (a == '(')
    {
        return 0;
    }
    else if (a == ')')
    {
        return 3;
    }
    else if (a == '#')
    {
        return -1;
    }
    else
    {
        return 5;
    }
    return -2;
}

void check(char *str, OPND *s1, OPTR *s2)
{
    while (*str != '#')
    {
        if (getvalue(*str) < 4)
        {
            if ((getvalue(*str) <= getvalue(s2->data[s2->top]) && getvalue(*str) < 4 && getvalue(*str) != 0) || getvalue(*str) == 3)
            {
                if (getvalue(*str) != 3)
                {
                    char c = popOPTR(s2);
                    int b = popOPND(s1);
                    int a = popOPND(s1);
                    if (c == '+')
                        pushOPND(s1, a + b);
                    else if (c == '-')
                        pushOPND(s1, a - b);
                    else if (c == '*')
                        pushOPND(s1, a * b);
                    else if (c == '/')
                        pushOPND(s1, a / b);
                }
                else
                {
                    while (getvalue(s2->data[s2->top]) != 0)
                    {
                        char c = popOPTR(s2);
                        int b = popOPND(s1);
                        int a = popOPND(s1);
                        if (c == '+')
                            pushOPND(s1, a + b);
                        else if (c == '-')
                            pushOPND(s1, a - b);
                        else if (c == '*')
                            pushOPND(s1, a * b);
                        else if (c == '/')
                            pushOPND(s1, a / b);
                    }
                    if (s2->data[s2->top] == '(')
                    {
                        popOPTR(s2);
                    }
                }
            }
            if (getvalue(*str) != 3)
            {
                pushOPTR(s2, *str);
            }
            str++;
        }
        else if (getvalue(*str) == 5)
        {
            int e = *str - '0';
            str++;
            while (getvalue(*str) == 5)
            {
                int NUM = *str - '0';
                e = e * 10 + NUM;
                str++;
            }
            pushOPND(s1, e);
        }
    }
    while (s2->data[s2->top] != '#')
    {
        char c = popOPTR(s2);
        int b = popOPND(s1);
        int a = popOPND(s1);
        if (c == '+')
            pushOPND(s1, a + b);
        else if (c == '-')
            pushOPND(s1, a - b);
        else if (c == '*')
            pushOPND(s1, a * b);
        else if (c == '/')
            pushOPND(s1, a / b);
    }
    printf("结果为:%d\n", s1->data[s1->top]);
}

int main()
{
    OPND *s1 = (OPND *)malloc(sizeof(OPND));
    InitOPND(s1);
    OPTR *s2 = (OPTR *)malloc(sizeof(OPTR));
    InitOPTR(s2);
    check(E2, s1, s2);
    OPND *s3 = (OPND *)malloc(sizeof(OPND));
    InitOPND(s3);
    OPTR *s4 = (OPTR *)malloc(sizeof(OPTR));
    InitOPTR(s4);
    check(E1, s3, s4);
    OPND *s5 = (OPND *)malloc(sizeof(OPND));
    InitOPND(s5);
    OPTR *s6 = (OPTR *)malloc(sizeof(OPTR));
    InitOPTR(s6);
    check(E3, s5, s6);
    return 0;
}