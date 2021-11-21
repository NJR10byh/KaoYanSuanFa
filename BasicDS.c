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

/*------------------------------------------------------------------*/

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

/*--------------------------------------------------------------------*/

/* 稀疏矩阵 */
typedef struct term
{
    int row, col; // 非零元素在稀疏矩阵中的行、列下标
    int value;    // 非零元素值
} Term;
typedef struct sparsematrix
{
    int m, n, t;  // 矩阵行数（m）、列数（n）、非零元素实际个数（t）
    Term table[]; // 存储非零元素的三元组表
} SparseMatrix;

/*--------------------------------------------------------------------*/

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

/*---------------------------------------------------------------------*/

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

/* 散列表（拉链法） */
typedef struct hashNode{
    int data;
    struct hashNode *nextArc;
}HashNode;
typedef struct hashTable{
    int maxSize;// 散列表最大长度
    HashNode **table;// 指向边结点的指针（直接指向边结点，不指向头结点）
}HashTable;