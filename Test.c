#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// 顺序表
typedef struct seqList
{
    int n;       // 顺序表元素个数
    int maxSize; // 顺序表最大长度
    int *arr;    // 指向顺序表数组首地址
} SeqList;
// 链表
typedef struct node
{
    int element;
    struct node *link;
} Node;
typedef struct singleLink
{
    int n; // 链表元素个数
    Node *first;
} SingleLink;

// 二叉树
typedef struct bTNode
{
    int element;           // 结点权值
    struct bTNode *lchild; // 左孩子
    struct bTNode *rchild; // 右孩子
} BTNode;
typedef struct binaryTree
{
    BTNode *root;
} BinaryTree;

// 图-邻接表
typedef struct eNode
{
    int AdjVex;            // 当前顶点
    int w;                 // 当前顶点权值
    struct eNode *nextArc; // 指向下一个结点的指针
} ENode;
typedef struct lGraph
{
    int n;       // 顶点个数
    int e;       // 边个数
    ENode **arr; // 存储边结点的二维数组
} LGraph;
// 图-邻接矩阵
typedef struct mGraph
{
    int n;     // 顶点个数
    int e;     // 边个数
    int **arr; // 存储邻接矩阵的二维数组
} MGraph;

// 基础函数
// 1、求树高
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
// 2、判断指定结点是否在二叉树上
void isExist(BTNode *t, int x, BTNode **p)
{
    if (!t)
        return;
    if (t->element == x)
    {
        *p = t;
        return;
    }
    isExist(t->lchild, x, p);
    isExist(t->rchild, x, p);
}
// 3、DFS-邻接表
void DFS(LGraph *L, int visited[], int i)
{
    if (visited[i])
        return;
    visited[i] = 1;
    ENode *p = L->arr[i];
    while (p)
    {
        DFS(L, visited, p->AdjVex);
        p = p->nextArc;
    }
}

/* 1、递归：二叉树中以元素值为x的结点为根的子树高度 */
int GetChildTreeHeight(BinaryTree *tree, int x)
{
    if (!tree->root)
        return 0;
    BTNode *p = NULL;
    isExist(tree->root, x, &p);
    if (p)
        return Height(p);
    return 0;
}

/* 2、判断无向图G是（true）否（false）为一棵树 */
// Step1: 计算边数是否为n-1
// Step2: 从任意一顶点进行一遍DFS，一定能访问到全部顶点
int OutDegree(LGraph *L)
{
    int outdegree = 0;
    ENode *p;
    for (int i = 0; i < L->n; i++)
    {
        p = L->arr[i];
        while (p)
        {
            outdegree++;
            p = p->nextArc;
        }
    }
    return outdegree;
}
bool isTree(LGraph *L)
{
    if (L->n < 2)
        return false;
    int outDegree = OutDegree(L);
    if ((outDegree / 2) != (L->n - 1))
        return false;
    int *visited = (int *)malloc(sizeof(int) * L->n);
    int count = 0;
    int i = 0, j = 0;
    count = 0;
    for (j = 0; j < L->n; j++)
        visited[j] = 0;
    DFS(L, visited, i);
    for (j = 0; j < L->n; j++)
        count += visited[j];
    if (count != L->n)
        return false;
    return true;
}

/* 3、判断二叉树（结点值各不相同）是否为二叉排序树 */
bool LeftLower(BTNode *t, int x)
{
    if (!t)
        return true;
    return t->element < x && LeftLower(t->lchild, x) && LeftLower(t->rchild, x);
}
bool RightLarger(BTNode *t, int x)
{
    if (!t)
        return true;
    return t->element > x && RightLarger(t->lchild, x) && RightLarger(t->rchild, x);
}
bool ChargeSortTree(BTNode *t)
{
    if (!t)
        return true;
    return LeftLower(t->lchild, t->element) &&
           RightLarger(t->rchild, t->element) &&
           ChargeSortTree(t->lchild) &&
           ChargeSortTree(t->rchild);
}
bool isSortTree(BinaryTree *tree)
{
    if (!tree->root)
        return false;
    return ChargeSortTree(tree->root);
}

/* 4、给定有向图G中任意两个顶点i和j，采用邻接表存储结构，判断是否存在从i到j的路径 */
bool isLine(LGraph *L, int i, int j)
{
    if (L->n < 2 || i < 0 || i > L->n - 1 || j < 0 || j > L->n - 1 || i == j)
        return false;
    int *visited = (int *)malloc(sizeof(int) * L->n);
    for (int t = 0; t < L->n; t++)
        visited[t] = 0;
    DFS(L, visited, i);
    if (visited[j])
        return true;
    return false;
}
/* 5、输出二叉排序树中max和min */
void PrintMaxMin(BinaryTree *tree, int *max, int *min)
{
    if (!tree->root)
        return;
    BTNode *p = tree->root;
    while (p->lchild)
        p = p->lchild;
    (*min) = p->element;
    p = tree->root;
    while (p->rchild)
        p = p->rchild;
    (*max) = p->element;
    return;
}