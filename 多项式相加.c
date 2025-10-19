#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;
typedef struct LNode
{
    ElemType data;
    ElemType info;
    ElemType info2;
    struct LNode *next;
} LNode, *LinkList;

// 初始化
LNode *InitList(LNode *L)
{
    L = (LNode *)malloc(sizeof(LNode));
    L->data = 0;
    L->info = 0;
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
LNode *TialInsert(LNode *L, ElemType e, ElemType info)
{
    LNode *P = (LNode *)malloc(sizeof(LNode));
    P->data = e;
    P->info = info;
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
        printf("%dx^%d ", L->data, L->info);
        L = L->next;
    }
    printf("\n");
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

LNode *Order1(LNode *L)
{
    /*
     * Order1: 在链表中寻找未被标记的最大指数结点并返回该结点指针
     * 参数:
     *   L - 指向带头结点的多项式链表（函数内部会跳过头结点开始遍历）
     * 返回值:
     *   返回指向具有当前最大指数（info）的结点的指针
     * 副作用:
     *   1) 将找到的结点的 info2 设为原始 info（保存原指数），
     *   2) 将该结点的 info 标记为 -100 以表示已被选取（避免重复选取）。
     * 说明:
     *   这个函数用于配合 Order2 对链表按指数从大到小重排。它并不创建新结点，
     *   而是通过标记已选结点来逐步找到下一个最大指数结点并返回它。
     */
    LNode *q = NULL;
    L = L->next; /* 跳过头结点，从第一个真实结点开始 */
    int Max = -999;
    int Length = Getlength(L);
    for (int i = 0; i < Length + 1; i++)
    {
        if (L->info > Max && L->info != -100)
        {
            Max = L->info;
            q = L;
        }
        L = L->next;
    }
    if (q != NULL)
    {
        q->info2 = q->info; /* 备份指数到 info2 */
        q->info = -100;     /* 标记为已被选择 */
    }
    return q;
}

LNode *Order2(LNode *L)
{
    /*
     * Order2: 根据 Order1 多次选择最大指数结点，构造一个新的按指数从大到小排列的链表
     * 参数:
     *   L - 指向带头结点的多项式链表（会被 Order1 的标记操作修改）
     * 返回值:
     *   返回一个新的带头结点的链表，该链表按指数从大到小排列。
     * 说明与副作用:
     *   - Order1 会把已选结点的 info 设为 -100，Order2 利用这一点逐次获取最大指数结点。
     *   - Order2 在新链表中为每个选取的结点分配新的结点，并把原结点的数据（系数）和
     *     存在于 info2 的原始指数拷贝过去。
     */
    LNode *head = InitList(NULL);
    LNode *p = head;
    LNode *head0 = head;
    int Length = Getlength(L);
    for (int i = 0; i < Length + 1; i++)
    {
        LNode *q = (LNode *)malloc(sizeof(LNode));
        LNode *s = Order1(L); /* 找到下一个最大指数的原结点（会被标记） */
        if (s == NULL)
        { /* 如果没有更多结点，提前结束 */
            free(q);
            break;
        }
        q->info = s->info2; /* 使用备份的原始指数 */
        q->info2 = 0;
        q->data = s->data; /* 拷贝系数 */
        q->next = NULL;
        p->next = q;
        p = p->next;
    }
    /* 如果新链表长度与原链表长度不符，去掉尾部多余的空结点 */
    if (Getlength(head0) != Length)
    {
        while (head0->next->next != NULL)
        {
            head0 = head0->next;
        }
        head0->next = NULL;
    }
    return head;
}

// 多项式相加
LNode *Add(LNode *p1, LNode *p2)
{
    /*
     * Add: 将两个多项式链表相加，返回结果链表（带头结点）
     * 参数:
     *   p1, p2 - 指向带头结点的多项式链表，假定两者均按指数从大到小排序
     * 返回值:
     *   返回新的多项式链表的头指针（带头结点）。实际实现复用原结点，
     *   将它们按指数比较后直接拼接到结果链表上；当指数相同时把系数相加并使用 p1 的结点。
     * 注意事项（副作用）:
     *   - 函数内部会改变传入链表的结点 next 指针（把结点拼接到结果中），因此原链表结构会被破坏。
     */
    p1 = p1->next; /* 跳过头结点，指向第一个真实结点 */
    p2 = p2->next;
    LNode *p = InitList(NULL);
    LNode *head = p;
    while (p1 != NULL && p2 != NULL)
    {
        if (p1->info > p2->info)
        {
            p->next = p1; /* p1 指数更大，直接接入结果 */
            p1 = p1->next;
            p = p->next;
        }
        else if (p1->info < p2->info)
        {
            p->next = p2; /* p2 指数更大，接入结果 */
            p2 = p2->next;
            p = p->next;
        }
        else
        {
            /* 指数相同，系数相加，把合并后的结点接入结果（使用 p1 的结点） */
            p1->data = p1->data + p2->data;
            p->next = p1;
            p = p->next;
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    /* 把剩余结点接入结果（如果一方先遍历完） */
    while (p1 != NULL)
    {
        p->next = p1;
        p1 = p1->next;
        p = p->next;
    }
    while (p2 != NULL)
    {
        p->next = p2;
        p2 = p2->next;
        p = p->next;
    }
    return head;
}
int main()
{
    LNode *head1 = InitList(NULL);
    LNode *tial = head1;
    tial = TialInsert(tial, 3, 4);
    tial = TialInsert(tial, 5, 2);
    tial = TialInsert(tial, 6, 1);
    tial = TialInsert(tial, 8, 0);
    tial = TialInsert(tial, 7, -1);
    print(head1);
    LNode *head2 = InitList(NULL);
    tial = head2;
    tial = TialInsert(tial, 4, 5);
    tial = TialInsert(tial, 2, 4);
    tial = TialInsert(tial, 1, 3);
    tial = TialInsert(tial, 3, 1);
    tial = TialInsert(tial, 4, -1);
    print(head2);
    LNode *head3 = Add(head1, head2);
    print(head3);

    LNode *head4 = InitList(NULL);
    tial = head4;
    tial = TialInsert(tial, 3, 2);
    tial = TialInsert(tial, 5, 4);
    tial = TialInsert(tial, 6, 1);
    tial = TialInsert(tial, 8, 3);
    tial = TialInsert(tial, 7, 0);
    head4 = Order2(head4);
    print(head4);
    LNode *head5 = InitList(NULL);
    tial = head5;
    tial = TialInsert(tial, 4, 4);
    tial = TialInsert(tial, 2, 5);
    tial = TialInsert(tial, 1, 3);
    tial = TialInsert(tial, 3, 1);
    tial = TialInsert(tial, 4, 0);
    tial = TialInsert(tial, 7, 2);
    head5 = Order2(head5);
    print(head5);
    LNode *head6 = Add(head4, head5);
    print(head6);

    return 0;
}