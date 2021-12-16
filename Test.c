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
typedef struct singleList
{
    int n; // 链表元素个数
    Node *first;
} SingleList;

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

/* 6、图邻接矩阵改邻接表 */
void MGraphToLGraph(MGraph *M,LGraph *L)
{
    int i=0,j=0;
    L->n=M->n;
    L->e=M->e;
    ENode *p,*q;
    for(i=0;i<M->n;i++)
    {
        q=L->arr[i];
        for(j=0;j<M->n;j++)
        {
            if(M->arr[i][j]==1)
            {
                p=(ENode *)malloc(sizeof(ENode));
                p->adjVex=j;
                p->nextArc=NULL;
                q->nextArc=p;
                q=q->nextArc;
            }
        }
    }   
}

/* 7、求指定节点在二叉排序中的层次 */
void SearchBTNode(BTNode *t,BTNode *p,int level,int *count)
{
    if(!t)
        return;
    if(t->element==p->element)
    {
        (*count)=level;
        return;
    }
    SearchBTNode(t->lchild,p,level+1,count);
    SearchBTNode(t->rchild,p,level+1,count);
}
int GetLevel(BinaryTree *tree,BTNode *p)
{
    if(!tree->root)
        return 0;
    int count=0;
    SearchBTNode(tree->root,p,1,&count);
    return count;
}

/* 8、二叉树带权路径长度 */
void GetPath(BTNode *t,int level,int *count)
{
    if(!t)
        return;
    if(!t->lchild&&!t->rchild)
        count+=level * t->element;// 带权路径长度：节点路径长度 * 结点权值
    GetPath(t->lchild,level+1,count);
    GetPath(t->rchild,level+1,count);
}
int GetPathLength(BinaryTree *tree)
{
    if(!tree->root)
        return 0;
    int count=0;    
    GetPath(tree->root,0,&count);
    return count;
}

/* 9、求用邻接表存储的无向图中，结点数量恰好为k的连通分量的个数 */
void DFS_8(LGraph *L,int visited[],int i,int *count)
{
    if(visited[i])
        return;
    (*count)++;
    visited[i]=1;
    ENode *p=L->arr[i];
    while(p)
    {
        DFS_8(L,visited,p->adjVex,count);
        p=p->nextArc;
    }
}
int GetKNum(LGraph *L,int k)
{
    int i=0,j=0;
    int *visited=(int *)malloc(sizeof(int)*L->n);
    int count=0,knum=0;
    for(i=0;i<l->n;i++)
        visited[i]=0;
    for(i=0;i<L->n;i++)
    {
        if(!visited[i])
        {
            DFS_8(L,visited,i,&count);
            if(count==k)
                knum++;
        }
    }
    return knum;   
}

/* 12、有向图用邻接表存储，求每个顶点出入度 */
void GetDegree(LGraph *L)
{
    int i;
    int *inDegree=(int *)malloc(sizeof(int)*L->n);
    int *outDegree=(int *)malloc(sizeof(int)*L->n);
    ENode *p;
    for(i=0;i<L->n;i++)
    {
        inDegree[i]=0;
        outDegree[i]=0;
    }
    for(i=0;i<L->n;i++)
    {
        p=L->arr[i];
        while(p)
        {
            inDegree[p->adjVex]++;
            outDegree[i]++;
            p=p->nextArc;
        }
    }
}

/* 13、逆转字符串，空间复杂度为O(1) */
void Reverse(char s[], int length)
{
    int i,j;
    char temp;
    i=0;
    j=length-1;
    while(i<j)
    {
        temp=s[i];
        s[i]=s[j];
        s[j]=temp;
        i++;
        j--;
    }
}

/* 15、递归求顺序表中最大值 */
void max(SeqList S,int low,int high,int *max)
{
    if(low>high)
        return;
    if(S.arr[low]>(*max))
        (*max)=S.arr[low];
    return max(S,low+1,high,max);
}
int GetMax(SeqList S)
{
    if(S.n==0)
        return 0;
    else if(S.n==1)
        return S.arr[0];
    int max=-1;
    Max(S,0,S.n-1,&max);
    return max;
}

/* 16、判断一棵二叉树是否为完全二叉树 */
void GetTotal(BTNode *t,int *total)
{
    if(!t)
        return;
    (*total)++;
    GetTotal(t->lchild,total);
    GetTotal(t->rchild,total);
}
void GetMap(BTNode *t,BTNode *map[],int i)
{
    if(!t)
        return;
    map[i]=t;
    GetMap(t->lchild,map,2*i+1);
    GetMap(t->rchild,map,2*i+2);
}
bool IfCompleteTree(BinaryTree *tree)
{
    if(!tree->root)
        return true;
    int total=0;
    GetTotal(tree->root,&total);
    BTNode **map=(BTNode **)malloc(sizeof(BTNode *)*total);
    GetMap(tree->root,map,0);
    for(int i=0;i<total;i++)
        if(map[i]==NULL)
            return false;
    return true;
}

/* 17、给定一个单链表，判断是否存在环路 */
bool IfLoop(SingleList *S)
{
    if(S->n<=1)
        return false;
    int count=0;
    Node *p=S->first;
    while(p)
    {
        if(count>S->n)
            return false;
        count++;
        p=p->link;
    }
    return true;
}

/* 18、求二叉排序树中从根节点开始的路径，这些路径需满足：构成路径的节点之和等于x */
void Getxpath(BTNode *t,int x,Stack S)
{
    if(!t)
        return;
    Push(S,t->element);
    x-=t->element;
    if(x==0)
        PrintStack(S);// 从栈底到栈顶依次打印元素
    else if(x<0)
        Pop(S);
    else
    {
        Getxpath(t->lchild,x,S);
        Getxpath(t->rchild,x,S);
        Pop(S);
    }
    return;
}
void GetxPath(BinaryTree *tree,int x)
{
    if(!tree->root)
        return;
    Stack S;
    Getxpath(tree->root,x,S);
}

/* 19、给定有向图，求能遍历到所有顶点的顶点集合 */
void DFS_19(LGraph *L,int visited[],int i)
{
    if(visited[i])
        return;
    visited[i]=1;
    ENode *p=L->arr[i];
    while(p)
    {
        DFS_19(L,visited,p->adjVex);
        p=p->nextArc;
    }
} 
void Que_19(LGraph *L)
{
    int i=0,j=0,count=0;
    int *visited=(int*)malloc(sizeof(int)*L->n);
    Stack S;
    for(i=0;i<L->n;i++)
    {
        for(j=0;j<L->n;j++)
            visited[j]=0;
        count=0;
        DFS_19(L,visited,i);
        for(j=0;j<L->n;j++)
            count+=visited[j];
        if(count==L->n)
            Push(S,i);
    }
}

/* 20、判断二叉树是否镜像对称 */
bool Mirror(BTNode *t1,BTNode *t2)
{
    if((t1&&!t2)||(!t1&&t2))
        return false;
    else if(!t1&&!t2)
        return true;
    return t1->element==t2->element&&Mirror(t1->lchild,t2->rchild)&&Mirror(t1->rchild,t2->lchild);
}
bool IfMirror(BinaryTree *tree)
{
    if(!tree->root)
        return true;
    return Mirror(tree->lchild,tree->rchild);
}