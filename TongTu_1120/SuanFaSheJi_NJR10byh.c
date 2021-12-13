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
    struct node *link; // 结点指针域
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
void IsExist(BTNode *t, int x, BTNode **p)
{
    if (!t)
        return;
    if (t->element == x)
    {
        *p = t;
        return;
    }
    IsExist(t->lchild, x, p);
    IsExist(t->rchild, x, p);
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
    BTNode *p = NULL;
    IsExist(tree->root, x, &p);
    if (!p)
        return 0;
    return Height(p);
}

/* 2、判断无向图G是（true）否（false）为一棵树 */
// Step1: 计算边数是否为n-1
// Step2: 从任意一顶点进行一遍DFS，一定能访问到全部顶点
void DFS_2(LGraph *L, int visited[], int i)
{
    if (visited[i] == 1)
        return;
    visited[i] = 1;
    ENode *p = L->a[i];
    while (p)
    {
        DFS_2(L, visited, p->adjVex);
        p = p->nextArc;
    }
}
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
    // 计算边数（确保此图连通）：
    // 法1（用总度数/2判断）:
    int degree = OutDegree(L);
    if (degree / 2 != L->n - 1)
        return false;
    // 法2（用原有数据结构中给的边数判断）:
    // 对于无向图的邻接表来说，每条边被存储了两次，所以计算边数时要除以2
    /* if (L->e / 2 != L->n - 1)
        return false; */
    int *visited = (int *)malloc(sizeof(int) * L->n);
    for (int i = 0; i < L->n; i++)
        visited[i] = 0;
    DFS_2(L, visited, 0); // 从任意一顶点进行一遍DFS，一定能访问到全部顶点
    int count = 0;
    for (int i = 0; i < L->n; i++)
        count += visited[i];
    if (count == L->n)
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
void DFS_4(LGraph *L, int visited[], int i)
{
    if (visited[i] == 1)
        return;
    visited[i] = 1;
    ENode *p = L->a[i];
    while (p)
    {
        DFS_4(L, visited, p->adjVex);
        p = p->nextArc;
    }
}
bool FindPath(LGraph *L, int i, int j)
{
    if (L->n < 2 || i < 0 || i > L->n - 1 || j < 0 || j > L->n - 1 || i == j)
        return false; // 判断i，j的合法性
    int *visited = (int *)malloc(sizeof(int) * L->n);
    for (int i = 0; i < L->n; i++)
        visited[i] = 0;
    DFS_4(L, visited, i);
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
    L->e = M->e;
    L->n = M->n;
    for (int i = 0; i < M->n; i++)
        for (int j = 0; j < M->n; j++)
            if (M->a[i][j] == 1)
            {
                ENode *p = (ENode *)malloc(sizeof(ENode));
                p->adjVex = j;
                // 头插
                p->nextArc = L->a[i];
                L->a[i] = p;
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

/* 8、二叉树带权路径长度（叶子结点到根结点的带权路径） */
void GetWPL(BTNode *t, int *wpl, int level)
{
    if (!t)
        return;
    if (!t->lchild && !t->rchild)
        (*wpl) += level * t->element;
    GetWPL(t->lchild, wpl, level + 1);
    GetWPL(t->rchild, wpl, level + 1);
}
int WPL(BinaryTree *tree)
{
    if (!tree->root)
        return 0;
    int wpl = 0;
    GetWPL(tree->root, &wpl, 0); // 带权路径长度 和 树高不一样！！！
    return wpl;
}

/* 9、求用邻接表存储的无向图中 “ 结点总数恰好为k ” 的连通分量的个数 */
void DFS_9(LGraph *L, int visited[], int i, int *count)
{
    if (visited[i] == 1)
        return;
    visited[i] = 1;
    (*count)++;
    ENode *p = L->a[i];
    while (p)
    {
        DFS_9(L, visited, p->adjVex, count);
        p = p->nextArc;
    }
}
int SubK(LGraph *L, int k)
{
    int i, j, count = 0, Subk = 0;
    int *visited = (int *)malloc(sizeof(int) * L->n);
    for (i = 0; i < L->n; i++)
        visited[i] = 0;
    for (i = 0; i < L->n; i++)
        if (visited[i] == 0)
        {
            count = 0;
            DFS_9(L, visited, i, &count);
            if (count == k)
                Subk++;
        }
    return Subk;
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
                    arr[j] = -1; // 将所有重复的元素标记为-1
                    newlength--; // 新数组长度-1
                }
    int *newarr = (int *)malloc(sizeof(int) * newlength); // 利用新数组存放不重复元素
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
void ReverseString(char s[], int length)
{
    int i = 0, j = length - 1;
    char temp;
    while (i < j)
    {
        temp = char[i];
        char[i] = char[j];
        char[j] = temp;
        i++;
        j--;
    }
    return;
}

/* 14、用“拉链法”构造散列表，并解决冲突。实现散列表搜索和插入 */

/* 15、递归求顺序表中最大元素 */
void GetMax(SeqList S, int left, int right, int *max)
{
    if (left > right)
        return;
    if (S.element[left] > (*max))
        (*max) = S.element[left];
    return GetMax(S, left + 1, right, max);
}
int SeqMax(SeqList S)
{
    if (S.n == 0)
        return 0;
    else if (S.n == 1)
        return S.element[0];
    int max = -1;
    return max;
}

/* 16、判断二叉树是否为完全二叉树 */
// 根据完全二叉树结点下标的性质将每个结点映射进数组，来判断数组中有无空缺即可
void GetMap(BTNode *t, BTNode *map[], int i)
{
    if (!t)
        return;
    map[i] = t;
    GetMap(t->lchild, map, 2 * i + 1);
    GetMap(t->rchild, map, 2 * i + 2);
}
void GetTotal(BTNode *t, int *total)
{
    if (!t)
        return;
    total++;
    GetTotal(t->lchild, total);
    GetTotal(t->rchild, total);
}
bool IfCompleteTree(BinaryTree *tree)
{
    if (!tree->root)
        return true;
    int total = 0;
    GetTotal(tree->root, &total); // 计算此树总结点数
    BTNode **map = (BTNode **)malloc(sizeof(BTNode *) * total);
    GetMap(tree->root, map, 0);
    for (int i = 0; i < total; i++)
        if (!map[i])
            return false;
    return true;
}

/* 17、给定一个单链表，判断链表是否存在环路 */ // 1>2>3>5>5>
bool IfLoop(SingleList *S)
{
    Node *p = S->first;
    int count = 0;
    while (p)
    {
        count++;
        if (count > S->n) // 如果有环，则count值必将大于S->n
            return false;
        p = p->link;
    }
    return true; //如果没有环，就可以出循环
}

/* 18、求二叉排序树中从根节点开始的路径，这些路径需满足：构成路径的节点之和等于x */
void Find_18(BTNode *t, int x, Stack S)
{
    if (!t)
        return;
    Push(S, t->element); // 将t结点的值入栈
    x -= t->element;
    if (x == 0)
    {
        PrintStack(S); // 从栈底到栈顶依次打印栈中元素
        return;
    }
    else if (x < 0)
        Pop(S);
    else
    {
        Find_18(t->lchild, x, S);
        Find_18(t->rchild, x, S);
        Pop(S); // 此结点下所有结点均不满足条件，出栈
    }
}
void FindPath_18(BinaryTree *tree, int x)
{
    if (!tree->root)
        return;
    Stack S;
    Find_18(tree->root, x, S);
}

/* 19、给定有向图，求能遍历到所有顶点的顶点集合 */
void DFS_19(LGraph *L, int visited[], int i)
{
    if (visited[i] == 1)
        return;
    visited[i] = 1;
    ENode *p = L->a[i];
    while (p)
    {
        DFS_19(L, visited, p->adjVex);
        p = p->nextArc;
    }
}
void GetJiHe(LGraph *L)
{
    int i, j, count;
    int *visited = (int *)malloc(sizeof(int) * L->n);
    for (i = 0; i < L->n; i++)
    {
        for (j = 0; j < L->n; j++)
            visited[j] = 0;
        DFS_19(L, visited, i);
        for (j = 0; j < L->n; j++)
            count += visited[j];
        if (count == L->n)
            EnQueue(Q, i);
    }
    return;
}

/* 20、判断二叉树是否镜像对称 */
bool IfMirror(BTNode *t1, BTNode *t2)
{
    if (!t1 && !t2) // 左右两边结点都不存在，对称
        return true;
    if (!t1 || !t2) // 左右两边结点只有一个不存在，不对称
        return false;
    return t1->element == t2->element && IfMirror(t1->lchild, t2->rchild) && IfMirror(t1->rchild, t2->lchild);
}
bool IfMirrorTree(BinaryTree *tree)
{
    if (!tree->root)
        return true;
    return IfMirror(tree->root, tree->root);
}