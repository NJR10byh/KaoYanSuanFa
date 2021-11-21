#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct btNode
{
    int element;
    struct btNode *lchild;
    struct btNode *rchild;
} BTNode;
typedef struct binaryTree
{
    BTNode *root;
} BinaryTree;

// 二叉树非递归的插入
bool Insert1(BinaryTree *tree, int x)
{
    BTNode *p = tree->root, *q = NULL;
    while (p)
    {
        q = p;
        if (x < p->element)
            p = p->lchild; // x小于结点值，去左子树
        else if (x > p->element)
            p = p->rchild; // x大于结点值，去右子树
        else
            return false; // x值重复
    }
    p = (BTNode *)malloc(sizeof(BTNode));
    p->element = x;
    p->lchild = p->rchild = NULL;
    if (!tree->root)
        tree->root = p;
    else
    {
        if (x < q->element)
            q->lchild = p;
        else if (x > q->element)
            q->rchild = p;
    }
    return true;
}
// 二叉树递归的插入
bool Insert2(BTNode *t, int x)
{
    if (x < t->element)
    {
        if (!t->lchild)
        {
            t->lchild = (BTNode *)malloc(sizeof(BTNode));
            t->lchild->element = x;
            t->lchild->lchild = t->lchild->rchild = NULL;
            return true;
        }
        else
            return Insert2(t->lchild, x);
    }
    else if (x > t->element)
    {
        if (!t->rchild)
        {
            t->rchild = (BTNode *)malloc(sizeof(BTNode));
            t->rchild->element = x;
            t->rchild->lchild = t->rchild->rchild = NULL;
            return true;
        }
        else
            return Insert2(t->rchild, x);
    }
    else
        return false;
}
bool Insert(BinaryTree *tree, int x)
{
    if (!tree->root)
    {
        tree->root = (BTNode *)malloc(sizeof(BTNode));
        tree->root->element = x;
        tree->root->lchild = tree->root->rchild = NULL;
        return true;
    }
    else
        return Insert2(tree->root, x);
}

// 1.求二叉树第K层有多少个度为1的结点
void CountK1(BTNode *t, int k, int level, int *count)
{
    if (!t)
        return;
    if (level <= k)
    {
        if (level == k)
        {
            if ((t->lchild && !t->rchild) || (!t->lchild && t->rchild))
                (*count)++;
            return;
        }
        else
        {
            CountK1(t->lchild, k, level + 1, count);
            CountK1(t->rchild, k, level + 1, count);
        }
    }
}
int NumK1(BinaryTree *tree, int k)
{
    int count = 0;
    CountK1(tree->root, k, 1, &count);
    return count;
}

// 2.求二叉树大于x结点的数量
void LargerX(BTNode *t, int x, int *count)
{
    if (!t)
        return;
    if (x < t->element)
        (*count)++;
    LargerX(t->lchild, x, count);
    LargerX(t->rchild, x, count);
}
int NumLargerX(BinaryTree *tree, int x)
{
    int count = 0;
    LargerX(tree->root, x, &count);
    return count;
}
// 2-拓展 求二叉树大于x结点的最小值
void SearchMinLargerX(BTNode *t, int x, int *min)
{
    if (!t)
        return;
    if (x < t->element)
    {
        if (t->element < (*min))
            (*min) = t->element;
    }
    SearchMinLargerX(t->lchild, x, min);
    SearchMinLargerX(t->rchild, x, min);
}
int MinLargerX(BinaryTree *tree, int x)
{
    int min = 0;
    LargerX(tree->root, x, &min);
    return min;
}

// 3.二叉树相似性判断
bool IsSimilar(BTNode *t1, BTNode *t2)
{
    if (!t1 && !t2)
        return true;
    else if ((!t1 && t2) || (t1 && !t2))
        return false;
    return IsSimilar(t1->lchild, t2->lchild) && IsSimilar(t1->rchild, t2->rchild);
}
bool SimilarTree(BinaryTree *tree1, BinaryTree *tree2)
{
    return IsSimilar(tree1->root, tree2->root);
}
// 3-拓展1 二叉树等价性判断
bool IsEqual(BTNode *t1, BTNode *t2)
{
    if (!t1 && !t2)
        return true;
    else if ((!t1 && t2) || (t1 && !t2))
        return false;
    return t1->element == t2->element && IsEqual(t1->lchild, t2->lchild) && IsEqual(t1->rchild, t2->rchild);
}
bool EqualTree(BinaryTree *tree1, BinaryTree *tree2)
{
    return IsEqual(tree1->root, tree2->root);
}
// 3-拓展2 求二叉树相似度
// 相似度=具有相同位置结点数量*2/两棵树中结点总数量
void Num_EqualNode(BTNode *t1, BTNode *t2, int *num)
{
    if ((!t1 && !t2) || (!t1 && t2) || (t1 && !t2))
        return;
    (*num)++;
    Num_EqualNode(t1->lchild, t2->lchild, num);
    Num_EqualNode(t1->rchild, t2->rchild, num);
}
void Size(BTNode *t, int *total)
{
    if (!t)
        return;
    (*total)++;
    Size(t->lchild, total);
    Size(t->rchild, total);
}
double Similarity(BinaryTree *tree1, BinaryTree *tree2)
{
    int num = 0, total = 0;
    Num_EqualNode(tree1->root, tree2->root, &num);
    Size(tree1->root, &total);
    Size(tree2->root, &total);
    return (double)num * 2 / total;
}

// 4.求二叉树内路径（针对扩充二叉树而言）长度（所有结点到根结点的距离之和）和外路径长度（所有叶子结点的下一级结点到根结点的距离之和）
void PathLength(BTNode *t, int *inlength, int *outlength, int level)
{
    if (!t)
        return;
    if (t->lchild || t->rchild)
        (*inlength) += level;
    else
        (*outlength) += level;
    PathLength(t->lchild, inlength, outlength, level + 1);
    PathLength(t->rchild, inlength, outlength, level + 1);
}
void Length(BinaryTree *tree)
{
    int inlength = 0, outlength = 0;
    PathLength(tree->root, &inlength, &outlength, 0);
    printf("内路径长度：%d，外路径长度：%d", inlength, outlength);
}
// 4-拓展 求二叉树WPL（所有叶子结点带权路径长度）
void GetWPL(BTNode *t, int *wpl, int level)
{
    if (!t)
        return;
    if (!t->lchild && !t->rchild)
        (*wpl) += t->element * level;
    GetWPL(t->lchild, wpl, level + 1);
    GetWPL(t->rchild, wpl, level + 1);
}
void WPL(BinaryTree *tree)
{
    int wpl = 0;
    GetWPL(tree->root, &wpl, 0);
    printf("WPL: %d", wpl);
}

// 5.求二叉树宽度（二叉树中结点最多那一层的结点个数）
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
void Weight(BTNode *t, int level, int count[])
{
    if (!t)
        return;
    count[level]++;
    Weight(t->lchild, level + 1, count);
    Weight(t->rchild, level + 1, count);
}
int getWeight(BinaryTree *tree)
{
    if (!tree->root)
        return 0;
    int height = Height(tree->root);
    int *count = (int *)malloc(sizeof(int) * height);
    for (int i = 0; i < height; i++) //初始化count数组
        count[i] = 0;
    Weight(tree->root, 1, count);
    int max = -1;
    for (int i = 0; i < height; i++)
    {
        if (max < count[i])
            max = count[i];
    }
    return max;
}