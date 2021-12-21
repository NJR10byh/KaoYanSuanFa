#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 交换元素
void Swap(int *a, int *b)
{
    int temp = 0;
    temp = *a;
    *a = *b;
    *b = temp;
}

// 直接插入排序
void ChaSort(int arr[], int length)
{
    if (length < 2)
        return;
    int i = 1, j = 0;
    for (i = 0; i < length; i++)
    {
        j = i - 1;
        while (j >= 0)
        {
            if (arr[j + 1] < arr[j])
                Swap(&arr[j + 1], &arr[j]);
            j--;
        }
    }
    return;
}

// 简单选择排序
void ChooseSort(int arr[], int length)
{
    if (length < 2)
        return;
    int i = 0, j = 0, minIndex = -1;
    for (i = 0; i < length; i++)
    {
        minIndex = i;
        for (j = i; j < length; j++)
            if (arr[j] < arr[minIndex])
                minIndex = j;
        Swap(&arr[i], &arr[minIndex]);
    }
    return;
}

// 冒泡排序
void MaoPaoSort(int arr[], int length)
{
    if (length < 2)
        return;
    int i = 0, j = length - 1;
    for (i = 0; i < length; i++)
        while (j > i)
        {
            if (arr[j] < arr[j - 1])
                Swap(&arr[j], &arr[j - 1]);
            j--;
        }
    return;
}

// 快速排序（递归）-王道
int Partition1(int arr[], int low, int high)
{
    int key = arr[low];
    while (low < high)
    {
        while (low < high && arr[high] > key)
            high--;
        Swap(&arr[high], &arr[low]);
        while (low < high && arr[low] < key)
            low++;
        Swap(&arr[low], &arr[high]);
    }
    arr[low] = key;
    return low;
}
void QuickSort1(int arr[], int low, int high)
{
    if (high - low < 2)
        return;
    int mid = Partition1(arr, low, high);
    QuickSort1(arr, low, mid - 1);
    QuickSort1(arr, mid + 1, high);
    return;
}

// 快速排序（递归）-教材
int Partition2(int arr[], int low, int high)
{
    int key = arr[low];
    int i = low + 1;
    int j = high;
    while (i < j)
    {
        while (arr[i] < key)
            i++;
        while (arr[j] > key)
            j--;
        Swap(&arr[i], &arr[j]);
    }
    Swap(&arr[low], &arr[j]);
    return j;
}
void QuickSort2(int arr[], int low, int high)
{
    if (high - low < 2)
        return;
    int mid = Partition2(arr, low, high);
    QuickSort2(arr, low, mid - 1);
    QuickSort2(arr, mid + 1, high);
    return;
}

// 折半插入排序
void HalfSort(int arr[], int length)
{
    if (length < 2)
        return;
    int i, j, low, high, mid, temp;
    for (i = 1; i < length; i++)
    {
        low = 0;
        high = i - 1;
        while (low <= high)
        {
            mid = (low + high) / 2;
            if (arr[i] < mid)
                high = mid - 1;
            else
                low = mid + 1;
        }
        temp = arr[i];
        for (j = i - 1; j >= low; j--)
            arr[j + 1] = arr[j];
        arr[low] = temp;
    }
}