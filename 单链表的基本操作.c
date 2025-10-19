#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;
typedef struct LNode
{
	ElemType data;
	struct LNode *next;
} LNode, *LinkList;

// 初始化
LNode *InitList(LNode *L)
{
	L = (LNode *)malloc(sizeof(LNode));
	L->data = 0;
	L->next = NULL;
	return L;
}

// 获取尾部结点
LNode *GetTial(LNode *L)
{
	while (L->next != NULL)
	{
		L = L->next;
	}
	return L;
}

// 尾插法
LNode *TialInsert(LNode *L, ElemType e)
{
	LNode *P = (LNode *)malloc(sizeof(LNode));
	P->data = e;
	P->next = NULL;
	L->next = P;
	return P;
}

// 遍历
void print(LNode *L)
{
	L = L->next;
	while (L != NULL)
	{
		printf("%d  ", L->data);
		L = L->next;
	}
	printf("end\n");
}

// 获取链表长度
int Getlength(LNode *L)
{
	L = L->next;
	int length = 0;
	while (L != NULL)
	{
		length++;
		L = L->next;
	}
	return length;
}

// 按位置查找
ElemType searchlocation(LNode *L, int pos)
{
	for (int i = 0; i < pos; i++)
	{
		L = L->next;
	}
	return L->data;
}

// 按值查找
int searchvalue(LNode *L, ElemType e)
{
	int pos = 0;
	while (L != NULL)
	{
		if (L->data == e)
		{
			return pos;
		}
		L = L->next;
		pos++;
	}
	return -1;
}

// 指定位置插入
void Insert(LNode *L, int pos, ElemType e)
{
	for (int i = 0; i < pos - 1; i++)
	{
		L = L->next;
	}
	LNode *P = (LNode *)malloc(sizeof(LNode));
	P->data = e;
	P->next = L->next;
	L->next = P;
}

// 删除节点
LNode *Delete(LNode *L0, int pos)
{
	LNode *L = L0;
	for (int i = 0; i < pos - 1; i++)
	{
		if (L == NULL)
			return NULL;
		L = L->next;
	}
	if (L == NULL || L->next == NULL)
		return NULL;
	LNode *P = L->next;
	L->next = P->next;
	free(P);
	return L0;
}

// 释放链表
LNode *Des(LNode *L)
{
	LNode *p;
	while (L != NULL)
	{
		p = L;
		L = L->next;
		free(p);
	}
	return 0;
}

// 两个链表合并：p2接到p1尾部
LNode *Add(LNode *p1, LNode *p2)
{
	LNode *tial = GetTial(p1);
	tial->next = p2->next;
	free(p2);
	return p1;
}

// 指定位置合并：p2接到p1的pos位置后
LNode *add(LNode *p1, LNode *p2, int pos)
{
	LNode *p = p1;
	for (int i = 0; i < pos; i++)
	{
		if (p == NULL)
			return p1;
		p = p->next;
	}
	LNode *p3 = p->next;
	LNode *p4 = GetTial(p2);
	p4->next = p3;
	p->next = p2->next;
	free(p2);
	return p1;
}

int main()
{
	LNode *head = InitList(NULL);
	LNode *tial = GetTial(head);
	tial = TialInsert(tial, 8);
	tial = TialInsert(tial, 9);
	tial = TialInsert(tial, 10);
	tial = TialInsert(tial, 11);
	tial = TialInsert(tial, 12);
	printf("head:\n");
	print(head);
	printf("链表长度为：%d\n", Getlength(head));
	printf("第3个元素为:%d\n", searchlocation(head, 3));
	printf("值为11的元素的位置为:%d\n", searchvalue(head, 11));
	Insert(head, 4, 15);
	printf("在第4个位置插入15:\n");
	print(head);
	Delete(head, 4);
	printf("删除第4个元素:\n");
	print(head);
	LNode *head2 = InitList(NULL);
	LNode *tial2 = GetTial(head2);
	tial2 = TialInsert(tial2, 20);
	tial2 = TialInsert(tial2, 21);
	tial2 = TialInsert(tial2, 22);
	tial2 = TialInsert(tial2, 23);
	tial2 = TialInsert(tial2, 24);
	printf("head2:\n");
	print(head2);
	// head=Add(head,head2);
	// print(head);
	head = add(head, head2, 3);
	printf("在head第3个元素后插入head2的整体元素:\n");
	print(head);
	Des(head);
}