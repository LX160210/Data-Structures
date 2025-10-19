#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

typedef char ElemType;

typedef struct
{
	ElemType data[MAXSIZE];
	int top;
} Sqstack;

// 初始化
void InitStack(Sqstack *s)
{
	s->top = -1;
}

// 入栈
void push(Sqstack *s, ElemType e)
{
	if (s->top >= MAXSIZE - 1)
	{
		printf("满了\n");
		return;
	}
	s->data[s->top + 1] = e;
	s->top++;
	return;
}

// 出栈
ElemType pop(Sqstack *s)
{
	ElemType e;
	if (s->top <= -1)
	{
		printf("栈空\n");
		return -1;
	}
	e = s->data[s->top];
	s->top--;
	return e;
}

// 取栈顶元素
ElemType get(Sqstack *s)
{
	ElemType e;
	if (s->top <= -1)
	{
		printf("栈空\n");
		return -1;
	}
	e = s->data[s->top];
	return e;
}

// 检查栈空栈满
void check(Sqstack *s)
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

// 清空栈
void clear(Sqstack *s)
{
	s->top = -1;
}

int main()
{
	Sqstack *s = (Sqstack *)malloc(sizeof(Sqstack));
	InitStack(s);
	push(s, 'a');
	push(s, 'b');
	push(s, 'c');
	printf("%c\n", s->data[s->top]);
	printf("%c\n", pop(s));
	printf("%d\n", s->top);
	printf("%c\n", get(s));
	check(s);
	clear(s);
	check(s);
	return 0;
}