#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
// 矩阵数据结构
typedef struct juZhen
{
    int **a;
    int n; // 矩阵阶数
} JuZhen;
// 二叉树数据结构
typedef struct bTNode
{
    int element;
    struct bTNode *lchild;
    struct bTNode *rchild;
} BTNode;
typedef struct binaryTree
{
    BTNode *root;
} BinaryTree;

/* 1、求数组A中的最大元素（递归） */
void GetMax(int A[], int left, int right, int *max)
{
    if (left > right)
        return;
    if (A[left] > (*max))
        (*max) = A[left];
    GetMax(A, left + 1, right, max);
}

/* 2、行优先下三角矩阵的查找） */
bool Search(JuZhen J, int x)
{
    for (int j = 0; j < J.n; j++)
        for (int i = 0; i <= j; i++)
            if (J.a[i][j] == x)
                return true;
    return false;
}

/* 3、判断完全二叉树 */
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
int Size(BTNode *t, int height, int level)
{
    if (level < height)
    {
        if (!t)
            return 0;
        return 1 + Size(t->lchild, height, level + 1) + Size(t->rchild, height, level + 1);
    }
    return 0;
}
bool IsComplete(BTNode *t)
{
    if (!t)
        return true;
    if (!t->lchild && t->rchild)
        return false;
    IsComplete(t->lchild);
    IsComplete(t->rchild);
}
bool IsCompleteTree(BTNode *t)
{
    int height = Height(t);        // 计算树高
    int size = Size(t, height, 1); //计算前height-1层结点个数
    if (size != pow(2, height - 1))
        return false;
    return IsComplete(t);
}
int main()
{
    // 1
    int A[10] = {4, 3, 2, 5, 9, 1, 6, 3, 0, 8};
    int max = -1;
    GetMax(A, 0, 9, &max);
    printf("Max = %d\n", max);

    // 2
    JuZhen J;
    int IsHave = Search(J, 5);

    // 3
    BinaryTree *tree;
    bool IsComplete = IsCompleteTree(tree->root);

    return 0;
}