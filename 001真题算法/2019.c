#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define maxSize 6

// 树数据结构
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

// 图数据结构
//（邻接表）
typedef struct eNode
{
    int AdjVex;
    struct eNode *nextArc;
} ENode;
typedef struct lGraph
{
    ENode **arr;
    int n;
    int e;
} LGraph;
//（邻接矩阵）
typedef struct mGraph
{
    int **a;
    int n;
    int e;
} MGraph;

// 散列表数据结构
typedef struct sanLie
{
    ENode **a; // 指向一位数组的指针
} SanLie;

// 1、求树中结点的平衡因子
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
int Size(BTNode *t)
{
    if (!t)
        return 0;
    return 1 + Size(t->lchild) + Size(t->rchild);
}
void Balance(BTNode *t, int nodes[], int *level)
{
    if (!t)
        return;
    int l = Height(t->lchild);
    int r = Height(t->rchild);
    nodes[(*level)++] = abs(l - r);
    Balance(t->lchild, nodes, level);
    Balance(t->rchild, nodes, level);
}

// 2、求有向图是否有从vi->vj的路径
void DFS(LGraph *G, int visited[], int i)
{
    if (visited[i] == 1)
        return;
    ENode *p = G->arr[i];
    visited[i] = 1;
    while (p)
    {
        DFS(G, visited, p->AdjVex);
        p = p->nextArc;
    }
}
bool SearchPath(LGraph *G, int visited[], int va, int vb)
{
    if (G->n == 0)
        return false;
    DFS(G, visited, va);
    if (visited[vb] == 1)
        return true;
    return false;
}

// 3、将数组arr中元素使用除留余数法添加到散列表中，用拉链法解决冲突
void ChuLiuYuShu(SanLie *S, int arr[], int key)
{
    for (int i = 0; i < maxSize - 1; i++)
    {
        ENode *p = S->a[arr[i] % key]; //   p指针指向在待插入结点数组的头结点
        // 生成新结点q，用于存储待插入元素
        ENode *q = (ENode *)malloc(sizeof(ENode));
        q->AdjVex = arr[i];
        q->nextArc = NULL;
        // 拉链法解决冲突（头插法）
        if (!p)
            p->nextArc = q;
        else
        {
            q->nextArc = p;
            S->a[arr[i] % key] = q;
        }
    }
}

int main()
{
    // 1
    BinaryTree *tree;
    int total = Size(tree->root);
    int *nodes = (int *)malloc(sizeof(int) * total);
    for (int i = 0; i < total; i++)
        nodes[i] = 0;
    int level = 0;
    Balance(tree->root, nodes, &level);

    // 2
    LGraph *G;
    int a, b;                                         // 图的顶点a、b
    int *visited = (int *)malloc(sizeof(int) * G->n); // 记录每个结点出度
    for (int i = 0; i < G->n; i++)
        visited[i] = 0;
    bool IsHave = SearchPath(G, visited, a, b);
    return 0;

    // 3
    SanLie *S;
    int arr[] = {24, 11, 44, 17, 25, 35};
    int key = maxSize; // 取key为表长
    ChuLiuYuShu(S, arr, key);
}