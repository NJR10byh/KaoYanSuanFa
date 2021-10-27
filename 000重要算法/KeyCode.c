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

// 交换元素
void Swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
// 初始化链表
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
// 直接插入排序
void ZhiSort(int arr[], int length)
{
    for (int i = 1; i < length; i++)
    {
        int j = i - 1;
        while (j > 0)
        {
            if (arr[j + 1] < arr[j])
            {
                Swap(&arr[j + 1], &arr[j]);
            }
            j--;
        }
    }
}

// 简单选择排序
void ChooseSort(int arr[], int length)
{
    for (int i = 0; i < length; i++)
    {
        int minIndex = i;
        for (int j = i; j < length; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        Swap(&arr[i], &arr[minIndex]);
    }
}
// 冒泡排序
void BubbleSort(int arr[], int length)
{
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length - 1; j++)
        {
            if (arr[i] > arr[i + 1])
            {
                Swap(&arr[i], &arr[i + 1]);
            }
        }
    }
}
// 快速排序（递归）
void QuickSort(int arr[], int low, int high)
{
    int key = Partition(arr, low, high); // 对数组进行划分
    QuickSort(arr, low, key - 1);        // 对划分后的左半部分进行快排
    QuickSort(arr, key + 1, high);       // 对划分后的右半部分进行快排
}
int Partition(int arr[], int low, int high)
{
    int element = arr[low]; // 将每一个划分区域的第一个元素（low）作为element
    while (low < high)
    {
        while (low < high && arr[high] > element) // 从后往前进行遍历，找到第一个小于element的值，和low进行交换
            --high;
        Swap(&arr[high], &arr[low]);
        while (low < high && arr[low] < element) // 从前向后遍历，找到第一个大于element的值，和high进行交换
            ++low;
        Swap(&arr[low], &arr[high]);
    }
    arr[low] = element; // low>=high，跳出while循环，将element放在low的位置
    return low;         // 返回low作为划分区域的位置
}

int main()
{
    int arr[9] = {4, 6, 2, 8, 1, 9, 0, 7, 3};
    // SingleList L;
    // InitLink(&L, arr, 9); // 初始化链表
    // InsertSeq(arr, 9);    // 直接插入排序（顺序表）
    // InsertLink(&L);       // 直接插入排序（链表）
    // BubbleSeq(arr, 9); // 冒泡排序（顺序表）
    // BubbleLink(&L);       // 冒泡排序（链表）
    // SimpleChooseSort_Seq(arr, 9); // 简单选择排序（顺序表）
    // SimpleChooseSort_Seq(&L);     // 简单选择排序（链表）
    return 0;
}