#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
typedef struct btNode
{
    int element;           // 结点值
    struct btNode *lchild; // 左孩子
    struct btNode *rchild; // 右孩子
} BTNode;
typedef struct binaryTree
{
    BTNode *root;
} BinaryTree;

// 邻接矩阵
typedef struct mGraph
{
    int **a; // 指向二维数组的指针
    int n;   // 顶点数
    int e;   // 边数
} MGraph;

// 邻接表
typedef struct eNode
{
    int AdjVex;            //顶点位置
    int n;                 //权值
    struct eNode *nextArc; // 指向下一个边结点
} ENode;
typedef struct lGraph
{
    ENode **a; // 指向一维数组的指针（直接指向边结点，不指向头结点）
    int n;     // 顶点数
    int e;     // 边数
} LGraph;

// 1、递归：二叉树中以元素值为x的结点为根的子树高度
BTNode *IsExist(BTNode *t, int x)
{
    if (!t)
        return NULL;
    if (t->element == x)
        return t;
    IsExist(t->lchild, x);
    IsExist(t->rchild, x);
}
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
int GetHeight(BinaryTree *tree, int x)
{
    if (!tree->root)
        return 0;
    BTNode *p = IsExist(tree->root);
    return Height(p);
}

// 2、给定无向图G中任意两个顶点i和j，采用邻接表存储结构，判断两个顶点间是否存在一条长度为k的简单路径

// 3、图的邻接矩阵改为邻接表存储
void Gai(MGraph *M, LGraph *L)
{
    for (int i = 0; i < M->n; i++)
        for (int j = 0; j < M->n; j++)
            if (M->a[i][j] == 1)
            {
                ENode *p = (ENode *)malloc(sizeof(ENode));
                p->AdjVex = j;
                p->nextArc = NULL;
                L->a[i]->nextArc = p;
            }
}

int main()
{
    // 1
    BinaryTree *tree;
    int x = 10;
    int height = GetHeight(tree, x);

    // 2

    // 3
    MGraph *M;
    LGraph *L;
    Gai(M, L);

    return 0;
}