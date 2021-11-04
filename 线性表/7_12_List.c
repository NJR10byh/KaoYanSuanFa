#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MaxSize 10
// 顺序表
typedef struct seqList
{
    int maxLength; // 顺序表允许的最大元素个数
    int n;         // 顺序表当前元素个数
    int *element;  // 指向顺序表数组首地址的指针
} SeqList;
// 链表
typedef struct node
{
    int element;       // 结点数据域
    struct node *link; // 结点指针域
} Node;
typedef struct singleList
{
    Node *first; // 头指针
    int n;       // 单链表中元素个数
} SingleList;

// 非递归查找顺序表中元素
int SearchSeqList1(SeqList *L, int x)
{
    int i = 0;
    for (i = 0; i < L->n; i++)
    {
        if (L->element[i] == x)
            return i;
        if (L->element[i] > x)
            return -1; // 只要顺序表中有值大于x，循环结束
    }
    return -1;
}
// 递归查找顺序表中元素
int SearchSeqList2(SeqList *L, int left, int right, int x)
{
    if (left > right)
        return -1;
    if (L->element[left] == x)
        return left;
    else
        return SearchSeqList2(L, left + 1, right, x);
}
int Search(SeqList *L, int x)
{
    if (x < L->element[0] || x > L->element[L->n - 1])
        return -1;
    else
        return SearchSeqList2(L, 0, L->n - 1, x);
}

// 1.删除顺序表中值为x的元素
bool DeleteData(SeqList *L, int x)
{
    if (L->n == 0)
        return false;
    for (int i = 0; i < L->n; i++)
        if (L->element[i] == x)
        {
            for (int j = i; j < L->n - 1; j++)
                L->element[j] = L->element[j + 1];
            L->n--;
            return true;
        }
    return false;
}
// 2.顺序表逆置
bool ReverseList(SeqList *L)
{
    if (L->n == 0)
        return false;
    int i = 0, j = L->n - 1, temp;
    while (i < j)
    {
        temp = L->element[i];
        L->element[i] = L->element[j];
        L->element[j] = temp;
        i++;
        j--;
    }
    return true;
}
// 2.链表逆置(就地逆置)
bool ReverseNode1(SingleList *L)
{
    Node *head = NULL;
    Node *p = L->first;
    if (!p || !p->link)
    {
        return false;
    }
    while (p)
    {
        L->first = p->link;
        if (!head)
        {
            head = p;
            head->link = NULL;
        }
        else
        {
            p->link = head;
            head = p;
        }
        p = L->first;
    }
    return true;
}
// 2.链表逆置(借用数组逆置)
bool ReverseNode2(SingleList *L)
{
    int temp[MaxSize]; // 用于存放链表中所有元素的值
    int i = 0;
    Node *p = L->first;
    if (!p && !p->link)
        return false;
    while (p)
    {
        temp[i++] = p->element;
        p = p->link;
    }
    p = L->first;
    while (p)
    {
        p->element = temp[--i];
        p = p->link;
    }
    return true;
}
// 3.两个集合的并 集合采用顺序存储
void SeqAppendAB(SeqList *L1, SeqList *L2)
{
    int i, j;
    for (i = 0; i < L2->n; i++)
    {
        for (j = 0; j < L1->n; j++)
        {
            if (L2->element[i] == L1->element[j])
                break;
        }
        if (j == L1->n)
        {
            L1->element[L1->n] = L2->element[i];
            L1->n++;
        }
    }
}
void SeqAppend(SeqList *A, SeqList *B)
{
    SeqAppendAB(A, B);
}
/* 3.两个集合的并 集合采用链式存储 */
// 法1
void LinkAppendAB(SingleList *L1, SingleList *L2)
{
    Node *p = L1->first, *q = L2->first;
    Node *r = (Node *)malloc(sizeof(Node));
    int i, j;
    while (q)
    {
        while (p)
        {
            if (q->element == p->element)
            {
                q = q->link;
                p = L1->first;
            }
            else
                p = p->link;
        }
        r->element = q->element;
        r->link = L1->first;
        L1->first = r;
    }
}
void LinkAppend(SingleList *A, SingleList *B)
{
    if (A && B)
        LinkAppendAB(A, B);
}

// 法2（不需要额外空间）
void LinkAB(SingleList *A, SingleList *B)
{
    Node *p = A->first;
    Node *q = B->first;
    Node *r;
    while (q)
    {
        while (p)
        {
            if (p->element == q->element)
                break;
            if (!p->link)
                r = p;
            p = p->link;
        }
        if (!p)
            r->link = q;
        B->first = q->link;
        q->link = NULL;
        p = A->first;
        q = B->first;
    }
}