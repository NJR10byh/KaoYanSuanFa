#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MaxSize 10
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
    struct eNode *nextAre; // 指向下一个边结点
} ENode;
typedef struct lGraph
{
    ENode **a; // 一维指针数组表示的头结点表
    int n;     // 顶点数
    int e;     // 边数
} LGraph;

typedef struct stack
{
    int data[MaxSize]; // 栈中元素
    int top;           // 栈顶指针
} Stack;
typedef struct queue
{
    int data[MaxSize]; // 队列中元素
    int front;         // 队头
    int rear;          // 队尾
} Queue;

/* 1.深度优先遍历 */
void DFS(LGraph *G, int visited[], int i)
{
    if (visited[i])
        return;
    printf("%d", i);
    visited[i] = 1;
    ENode *p = G->a[i];
    while (p)
    {
        DFS(G, visited, p->AdjVex);
        p = p->nextAre;
    }
}
// 遍历
void Traverse(LGraph *G)
{
    int i;
    int *visited = (int *)malloc(sizeof(int) * G->n);
    for (i = 0; i < G->n; i++)
        visited[i] = 0;
    for (i = 0; i < G->n; i++)
        if (!visited[i])
            DFS(G, visited, i);
}

/* 2.求有向无环图的根（对每一个结点进行一遍DFS，如果有一个结点能访问到全部的结点，这个点就是根结点） */
int GetRoot(LGraph *G)
{
    int i, j, count;
    int *visited = (int *)malloc(sizeof(int) * G->n);
    for (i = 0; i < G->n; i++)
    {
        count = 0;
        for (j = 0; j < G->n; j++)
            visited[j] = 0;
        DFS(G, visited, i);
        for (j = 0; j < G->n; j++)
            count += visited[j];
        if (count == G->n) // 如果一次能访问到全部的结点，则visited全为1，加起来和为G->n
            return i;      // 根存在，返回根结点编号
    }
    return -1; // 根不存在，返回-1
}

/* 3.DFS非递归算法 */
void NDFS(LGraph *G)
{
    int i, j;
    ENode *p;
    Stack S, Temp;
    int *visited = (int *)malloc(sizeof(G->n));
    for (i = 0; i < G->n; i++)
        visited[i] = 0;
    for (i = 0; i < G->n; i++)
    {
        if (!visited[i])
        {
            Push(S, i);
            while (!IsEmpty(S))
            {
                j = Top(S);
                Pop(S);
                printf("%d", j);
                visited[j] = 1;
                p = G->a[j];
                while (p)
                {
                    if (!visited[p->AdjVex])
                        Push(Temp, p->AdjVex);
                    p = p->nextAre;
                }
                while (!IsEmpty(Temp))
                {
                    j = Top(Temp);
                    Pop(Temp);
                    Push(S, j);
                }
            }
        }
    }
}

// 4.判断G1是否为G2的子图
/* 邻接表 */
bool IsSubList(ENode *L1, ENode *L2)
{
    ENode *p = L1, *q = L2;
    while (p)
    {
        q = L2;
        while (q)
        {
            if (p->AdjVex == q->AdjVex)
                break;
            q = q->nextAre;
        }
        if (!q)
            return false;
        p = p->nextAre;
    }
    return true;
}
bool IsSubGraph1(LGraph *G1, LGraph *G2)
{
    bool flag = false;
    int i, j;
    if (G1->n > G2->n)
        return false; //判断G1的顶点集合是否是G2的顶点集合的子集
    //判断G1的边集合是否是G2的边集合的子集
    for (i = 0; i < G1->n; i++)
    {
        if (!IsSubList(G1->a[i], G2->a[i]))
            return false;
    }
    return true;
}
/* 邻接矩阵 */
bool IsSubGraph2(LGraph *G1, LGraph *G2)
{
    bool flag = false;
    int i, j;
    if (G1->n > G2->n || G1->e > G2->e)
        return false; //判断G1的顶点集合是否是G2的顶点集合的子集
    //判断G1的边集合是否是G2的边集合的子集
    for (i = 0; i < G1->n; i++)
        for (j = 0; j < G1->n; j++)
            if ((G1->a[i][j] == 1) && (G2->a[i][j] == 0))
                return false;
    return true;
}

// 5.求图的最大入度顶点
int FindMaxInNode(LGraph *G)
{
    int *indegree = (int *)malloc(sizeof(int) * G->n);
    ENode *p;
    int i, max = -1, node = -1;
    for (i = 0; i < G->n; i++)
        indegree[i] = 0; // 初始化indegree数组
    for (i = 0; i < G->n; i++)
    {
        p = G->a[i];
        while (p)
        {
            indegree[p->AdjVex]++;
            p = p->nextAre;
        }
    }
    for (i = 0; i < G->n; i++)
    {
        if (max < indegree[i])
        {
            max = indegree[i];
            node = i;
        }
    }
    return node;
}

// 5-拓展1 求图的入度和出度相等的结点有多少个
int FindEqualNode(LGraph *G)
{
    int *indegree = (int *)malloc(sizeof(int) * G->n);
    int *outdegree = (int *)malloc(sizeof(int) * G->n);
    ENode *p;
    int i, max = -1, node = -1, count = 0;
    for (i = 0; i < G->n; i++)
    {
        indegree[i] = 0;  // 初始化indegree数组
        outdegree[i] = 0; // 初始化outdegree数组
    }
    for (i = 0; i < G->n; i++)
    {
        p = G->a[i];
        while (p)
        {
            indegree[p->AdjVex]++; // 入度加1
            outdegree[i]++;        // 出度加1
            p = p->nextAre;
        }
    }
    for (i = 0; i < G->n; i++)
    {
        if (indegree[i] == outdegree[i])
            count++;
    }
    return count;
}
// 5-拓展2 判断无向图G是否连通
/* 从0号顶点出发进行DFS，判断是否能够访问到每一个顶点 */
int IsConnectionGraph(LGraph *G)
{
    int i, count;
    int *visited = (int *)malloc(sizeof(int) * G->n);
    for (i = 0; i < G->n; i++)
        visited[i] = 0; // 初始化visited数组
    DFS(G, visited, 0);
    for (i = 0; i < G->n; i++)
        count = count + visited[i];
    if (count == G->n)
        return true;
    return false;
}
// 5-拓展3 判断有向图G是否强连通
int IsStrongConnectionGraph(LGraph *G)
{
    int i, j, count;
    int *visited = (int *)malloc(sizeof(int) * G->n);
    for (i = 0; i < G->n; i++)
    {
        for (j = 0; j < G->n; j++)
            visited[i] = 0; // 初始化visited数组
        count = 0;
        DFS(G, visited, 0); // 对每个顶点进行DFS
        for (j = 0; j < G->n; j++)
            count = count + visited[i];
        if (count != G->n) // 所有顶点必须全部满足全访问到
            return false;
    }
    return true;
}