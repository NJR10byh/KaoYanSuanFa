//
//  SuanFaSheJi_NJR10byh.c
//
//  Created by NJR10byh Tutu on 2021/11/19.
//

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
    ENode **a; // 指向一维数组的指针（直接指向边结点，不指向头结点）
    int n;     // 图的当前顶点数
    int e;     // 图的当前边数
} LGraph;

/* 1、递归：二叉树中以元素值为x的结点为根的子树高度 */
// 先找到元素值为x的结点，然后传入此结点调用求树高
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
// 边数（度数 / 2）为（顶点数 - 1）
int OutDegree(LGraph *L)
{
    int count = 0;
    for (int i = 0; i < L->n; i++)
    {
        ENode *p = L->a[i];
        while (p)
        {
            count++;
            p = p->nextArc;
        }
    }
    return count;
}
bool IfTree(LGraph *L)
{
    int degree = OutDegree(L);
    if (degree / 2 == L->n - 1)
        return true;
    return false;
}

/* 3、判断二叉树（结点值各不相同）是否为二叉排序树 */
// 每个结点值大于其左子树所有结点值，小于其右子树所有结点值
bool IfLower(BTNode *t, int x)
{
    if (!t)
        return true;
    return t->element < x && IfLower(t->lchild, x) && IfLower(t->rchild, x);
    // 三个条件：此结点权值小于x、此结点左子树所有结点权值小于x，此结点右子树所有结点权值小于x
}
bool IfLarger(BTNode *t, int x)
{
    if (!t)
        return true;
    return t->element > x && IfLarger(t->lchild, x) && IfLarger(t->rchild, x);
    // 三个条件：此结点权值大于x，此结点左子树所有权值大于x，此结点右子树所有权值大于x
}
bool IsSortTree(BTNode *t)
{
    if (!t)
        return true;
    return IfLower(t->lchild, t->element) &&
           IfLarger(t->rchild, t->element) &&
           IsSortTree(t->lchild) &&
           IsSortTree(t->rchild);
    // 四个条件：此结点权值大于此结点左子树所有结点权值、小于此结点右子树所有结点权值、此结点左子树是二叉排序树、右子树是二叉排序树
}
bool IsBinarySortTree(BinaryTree *tree)
{
    return IsSortTree(tree->root);
}

/* 4、给定有向图G中任意两个顶点i和j，采用邻接表存储结构，判断是否存在从i到j的路径 */
// 从i开始，调用一次DFS，如果j被标记，则说明存在i到j的路径
void DFS(LGraph *L, int visited[], int i)
{
    if (visited[i] == 1)
        return;
    visited[i] = 1;
    ENode *p = L->a[i];
    while (p)
    {
        DFS(L, visited, p->adjVex);
        p = p->nextArc;
    }
}
bool FindPath(LGraph *L, int i, int j)
{
    if (L->n < 2)
        return false;
    int *visited = (int *)malloc(sizeof(int) * L->n);
    for (int i = 0; i < L->n; i++)
        visited[i] = 0;
    DFS(L, visited, i);
    if (visited[j] == 1)
        return true;
    return false;
}

/* 5、输出二叉排序树中max和min */
// min：二叉树最左结点值，max：二叉树最右结点值
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
// 按行遍历邻接矩阵，每一行中为1的结点说明存在边，将其转化为邻接表中的边结点
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

/* 7、求指定结点p在给定二叉排序树中的层次 */
// 不管是什么二叉树，求某结点高度都一样
void GetLevel(BTNode *t, BTNode *p, int current, int *level)
{
    if (!t)
        return;
    if (t->element == p->element)
    {
        (*level) = current;
        return;
    }
    GetLevel(t->lchild, p, current + 1, level);
    GetLevel(t->rchild, p, current + 1, level);
}
int Level(BinaryTree *tree, BTNode *p)
{
    if (!tree->root)
        return 0;
    int level = 0;
    GetLevel(tree->root, p, 1, &level);
    return level;
}

/* 8、二叉树带权路径长度 */
void GetWPL(BTNode *t, int *wpl, int level)
{
    if (!t)
        return;
    (*wpl) += level * t->element;
    GetWPL(t->lchild, wpl, level + 1);
    GetWPL(t->rchild, wpl, level + 1);
}
int WPL(BinaryTree *tree)
{
    if (!tree->root)
        return 0;
    int wpl = 0;
    GetWPL(tree->root, &wpl, 1);
    return wpl;
}

/* 10、长度为n的序列，删除序列中重复元素。每个重复出现的元素保留最后出现的元素 */
void DeleteDuplicated(int arr[], int length)
{
    int i = 0, j = 0;
    int newlength = length;
    for (i = length - 1; i >= 0; i--)
        if (arr[i] != -1)
            for (j = i - 1; j >= 0; j--)
                if (arr[j] == arr[i])
                {
                    arr[j] = -1;
                    newlength--;
                }
    int *newarr = (int *)malloc(sizeof(int) * newlength);
    for (i = 0; i < newlength; i++)
        newarr[i] = 0;
    j = 0;
    for (i = 0; i < length; i++)
        if (arr[i] != -1)
            newarr[j++] = arr[i];
}

/* 11、求二叉树高度 */
int TreeHeight(BTNode *t)
{
    if (!t)
        return 0;
    int l = TreeHeight(t->lchild);
    int r = TreeHeight(t->rchild);
    if (l > r)
        return l + 1;
    else
        return r + 1;
}
int BinaryTreeHeight(BinaryTree *tree)
{
    if (!tree->root)
        return 0;
    return TreeHeight(tree->root);
}

/* 12、有向图采用邻接表存储，求有向图每个顶点的出入度 */
void GetDegree(LGraph *L)
{
    int i = 0;
    ENode *p;
    int *indegree = (int *)malloc(sizeof(int) * L->n);
    int *outdegree = (int *)malloc(sizeof(int) * L->n);
    for (i = 0; i < L->n; i++)
    {
        indegree[i] = 0;  // 初始化indegree数组
        outdegree[i] = 0; // 初始化outdegree数组
    }
    for (i = 0; i < L->n; i++)
    {
        p = L->a[i];
        while (p)
        {
            outdegree[i]++;
            indegree[p->adjVex]++;
            p = p->nextArc;
        }
    }
}

/* 13、逆置字符串，要求空间复杂度 O(1) */

int main()
{
    // 1
    BinaryTree *tree_1;
    int x = 10;
    int height = GetHeight(tree_1, x);

    // 2
    LGraph *L_2;
    bool ifTree = IfTree(L_2);

    // 3
    BinaryTree *tree_3;
    bool issorttree = IsBinarySortTree(tree_3);

    // 4
    int i = 0;
    int j = 3;
    LGraph *L_4;
    bool ifPath = FindPath(L_4, i, j);

    // 5
    BinaryTree *tree_5;
    int max = 0;
    int min = 0;
    SortTreeMaxMin(tree_5, &max, &min);

    // 6
    MGraph *M_6;
    LGraph *L_6;
    Gai(M_6, L_6);

    return 0;
}