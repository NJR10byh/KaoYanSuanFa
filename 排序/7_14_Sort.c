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

// 1.双向冒泡，避免已到位元素重复比较
// 重点是swapLoc的使用
void DoubleSort(int A[], int n)
{
    int i, left = 0, right = n - 1, swapLoc = -1;
    while (left < right)
    {
        // 从左到右冒泡
        swapLoc = -1;
        for (i = left; i < right; i++)
        {
            if (A[i] > A[i + 1])
            {
                Swap(&A[i], &A[i + 1]);
                swapLoc = i;
            }
        }
        if (swapLoc == -1)
            return;
        else
            right = swapLoc;

        // 从右到左冒泡
        swapLoc = -1;
        for (i = right; i > left; i--)
        {
            if (A[i] < A[i - 1])
            {
                Swap(&A[i], &A[i - 1]);
                swapLoc = i;
            }
        }
        if (swapLoc == -1)
            return;
    }
}

// 3.找第k小元素( 从小到大排序第K个 )
int KTH(int A[], int left, int right, int k)
{
    if (left > right)
        return -1;
    int i = left, j = right;
    do
    {
        do
        {
            i++;
        } while (A[i] < A[left]);
        do
        {
            j--;
        } while (A[j] < A[left]);
        if (i < j)
            Swap(&A[i], &A[j]);
    } while (i < j);
    Swap(&A[left], &A[j]);
    if (j == k)
        return A[j];
    else if (j > k)
        return KTH(A, left, j - 1, k);
    else
        return KTH(A, j + 1, right, k);
}
int FindK(int A[], int n, int k)
{
    return KTH(A, 0, n - 1, k);
}

// 4.奇数挪到偶数前面
void JiOu(int A[], int n)
{
    int i, j;
    while (i < j)
    {
        while (A[i] % 2 == 1) // 奇数
            i++;
        while (A[i] % 2 == 0) // 偶数
            j--;
        if (i < j)
            Swap(&A[i], &A[j]);
    }
}