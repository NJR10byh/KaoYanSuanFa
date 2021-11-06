#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// 二叉树数据结构
typedef struct bTNode
{
    int element;
    struct BTNode *lchild;
    struct BTNode *rchild;
} BTNode;
typedef struct binaryTree
{
    BTNode *root;
} BinaryTree;

// 图数据结构
typedef struct eNode
{
    int AdjVex;
    int n;
    struct ENode *nextArc;
} ENode;
typedef struct lGraph
{
    ENode **arr;
    int n;
    int e;
} LGraph;

/* 1、一个长度为n的序列，删除序列中重复的元素，对每个重复出现的元素保留最后出现的 */
void Delete(int arr[], int length, int *count)
{
    // 将所有重复数值进行软删除，只保留最后出现的（置-1）
    for (int i = 0; i < length; i++)
        for (int j = i + 1; j < length; j++)
            if (arr[i] == arr[j])
                arr[i] = -1;
    // 将所有值为-1的元素进行删除
    for (int i = 0; i < length; i++)
        if (arr[i] == -1)
        {
            for (int j = i + 1; j < length; j++)
                arr[j - 1] = arr[j];
            (*count)++;
            i--; // 很关键，删除后数组长度减1，当前位置元素改变，故应再次访问当前所在位置元素
        }
    return;
}

/* 2、二叉树采用二叉链表存储结构，求树高 */
int Height(BTNode *t)
{
    if (!t)
        return 0;
    int l = Height(t->lchild);
    int r = Height(t->rchild);
    if (l > r)
        return l + 1;
    else
        return r + 1;
}

/* 3、有向图用邻接表表示，求每个结点出度 */
void OutDegree(LGraph *L, int visited[])
{
    ENode *p;
    for (int i = 0; i < L->n; i++)
    {
        p = L->arr[i];
        while (p)
            visited[i]++;
    }
}
int main()
{
    int arr[10] = {4, 3, 2, 5, 1, 1, 6, 3, 1, 8};
    int count = 0, length = 10; // 记录重复值个数，数组长度
    BinaryTree *tree;
    LGraph *L;
    int *visited = (int *)malloc(sizeof(int) * L->n); // 记录每个结点出度
    for (int i = 0; i < L->n; i++)
        visited[i] = 0;
    Delete(arr, 10, &count);         // 1
    int height = Height(tree->root); // 2
    OutDegree(L, visited);           // 3
    return 0;
}
