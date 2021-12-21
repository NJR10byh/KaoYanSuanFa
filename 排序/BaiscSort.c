#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
}