#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
/* 顺序表 */
typedef struct seqList
{
    int n;         // 顺序表长度
    int maxLength; // 顺序表最大允许长度
    int *element;  // 指向顺序表数组首地址
} SeqList;
/* 链表 */
typedef struct node
{
    int element;       // 结点数据域
    struct Node *link; // 结点指针域
} Node;
typedef struct singleList
{
    Node *first; // 头指针
    int n;       // 单链表中元素个数
} SingleList;

/* 堆栈 */
typedef struct stack
{
    int top;      // 当前栈顶位置下标
    int maxSize;  // 最大栈顶位置下标
    int *element; // 指向堆栈数组首地址的指针
} Stack;
/* 队列 */
typedef struct quene
{
    int front;    // 队头元素前一个位置下标
    int rear;     // 队尾元素位置下标
    int maxSize;  // 最大栈顶位置下标
    int *element; // 指向队列数组首地址的指针
} Quene;

/* 二叉树 */
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

/* 图--邻接矩阵 */
typedef struct mGraph
{
    int **a; // 邻接矩阵（二维数组）
    int n;   // 图的当前顶点数
    int e;   // 图的当前边数
} MGraph;
/* 图--邻接表 */
typedef struct enode
{
    int adjVex;            //顶点
    int w;                 //边的权值
    struct eNode *nextArc; // 指向下一个顶点的指针
} ENode;
typedef struct lGraph
{
    int n;     // 图的当前顶点数
    int e;     // 图的当前边数
    ENode **a; // 指向一维数组的指针（直接指向边结点，不指向头结点）
} LGraph;

/* 1、递归：二叉树中以元素值为x的结点为根的子树高度 */
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
    BTNode *p = IsExist(tree->root, x);
    return Height(p);
}

/* 2、判断无向图G是（true）否（false）为一棵树 */

/* 3、判断二叉树（结点值各不相同）是否为二叉排序树 */
bool IsSortTree(BTNode *t)
{
    if (!t)
        return true;
    if ((t->lchild && t->element < t->lchild->element) || (t->rchild && t->element > t->rchild->element))
        return false;
    return IsSortTree(t->lchild) && IsSortTree(t->rchild);
}
bool SortTree(BinaryTree *tree)
{
    if (!tree->root)
        return true;
    return IsSortTree(tree->root);
}

/* 4、给定有向图G中任意两个顶点i和j，采用邻接表存储结构，判断是否存在从i到j的路径 */

/* 5、输出二叉排序树中max和min */
void SortTreeMaxMin(BinaryTree *tree, int *max, int *min)
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

/* 6、图的邻接矩阵改为邻接表存储 */
void Gai(MGraph *M, LGraph *L)
{
    for (int i = 0; i < M->n; i++)
        for (int j = 0; j < M->n; j++)
            if (M->a[i][j] == 1)
            {
                ENode *p = (ENode *)malloc(sizeof(ENode));
                p->adjVex = j;
                p->nextArc = NULL;
                L->a[i]->nextArc = p;
            }
}

int main()
{
    // 1
    BinaryTree *tree_1;
    int x = 10;
    int height = GetHeight(tree_1, x);

    // 2

    // 3
    BinaryTree *tree_3;
    bool issorttree = SortTree(tree_3);

    // 5
    BinaryTree *tree_5;
    int max = 0;
    int min = 0;
    SortTreeMaxMin(tree_5, &max, &min);

    // 6
    MGraph *M;
    LGraph *L;
    Gai(M, L);

    return 0;
}