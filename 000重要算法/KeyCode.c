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

void Swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
void InitLink(SingleList *L, int arr[], int length)
{
    Node *p, *q;
    L->first = NULL;
    L->n = 0;
    p = L->first;
    for (int i = 0; i < length - 1; i++)
    {
        q = (Node *)malloc(sizeof(Node));
        q->element = arr[i];
        q->link = p->link;
        p->link = q;
        L->n++;
        p = q;
    }
}

/* 排序 */
// 直接插入排序（顺序表）
void InsertSeq(int arr[], int length)
{
    int i, j = 0;
    for (i = 1; i < length; i++)
    {
        j = i;
        while (j > 0)
        {
            if (arr[j] < arr[j - 1])
            {
                Swap(&arr[j], &arr[j - 1]);
            }
            j--;
        }
    }
    for (i = 0; i < length; i++)
    {
        printf("%d->", arr[i]);
    }
}
// 直接插入排序（链表）
void InsertLink(SingleList *L)
{
    Node *p, *q, *r;
    p = L->first->link;
    q = (Node *)malloc(sizeof(Node));
    q->element = p->element;
    q->link = NULL;
    r = p = p->link;
    while (r)
    {
        p = r;
        r = p->link;
        if (p->element < q->element)
        {
            p->link = q;
            q = p;
        }
        else if (p->element >= q->element)
        {
            p->link = q->link;
            q->link = p;
        }
    }
}

// 冒泡排序（顺序表）
void BubbleSeq(int arr[], int length)
{
    int i, j = 0;
    for (i = 0; i < length; i++)
    {
        for (j = 0; j < length - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                Swap(&arr[j], &arr[j + 1]);
            }
        }
    }
    for (i = 0; i < length; i++)
    {
        printf("%d->", arr[i]);
    }
}
// 冒泡排序（链表）
void BubbleLink(SingleList *L)
{
    Node *p, *q, *r; // q指向当前元素，p指向当前元素的前驱，r指向当前元素的后继
    for (int i = 0; i < L->n; i++)
    {
        p = L->first;
        q = p->link;
        r = q->link;
        while (r)
        {
            if (q->element > r->element)
            {
                q->link = r->link;
                r->link = q;
                p->link = r;
            }
            p = p->link;
            q = q->link;
            r = r->link;
        }
    }
}
int main()
{
    int arr[9] = {4, 6, 2, 8, 1, 9, 0, 7, 3};
    // SingleList L;
    // InitLink(&L, arr, 9); // 初始化链表
    // InsertSeq(arr, 9);    // 直接插入排序（顺序表）
    // InsertLink(&L);       // 直接插入排序（链表）
    BubbleSeq(arr, 9); // 冒泡排序（顺序表）
    // BubbleLink(&L);       // 冒泡排序（链表）
    return 0;
}
