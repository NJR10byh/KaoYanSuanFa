#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

/* 判断树高 */
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
/* 判断树结点个数 */
// 法1:
int Size(BTNode *t)
{
    if (!t)
        return 0;
    return 1 + Size(t->lchild) + Size(t->rchild);
}
// 法2:
void GetSize(BTNode *t, int *count)
{
    if (!t)
        return;
    (*count)++;
    GetSize(t->lchild, count);
    GetSize(t->rchild, count);
}
/* 求结点是否在二叉树上 */
bool IsExist(BTNode *t, int x)
{
    if (!t)
        return false;
    return t->element == x || IsExist(t->lchild, x) || IsExist(t->rchild, x);
}

// 6. 判断二叉树是否为满二叉树
// 原理：num=2^h-1
bool IsCompltetTree(BinaryTree *tree)
{
    if (!tree->root)
        return true;
    int height = Height(tree->root);
    int total = Size(tree->root);
    if (total == (pow(2, height) - 1))
        return true;
    else
        return false;
}

// 6-拓展1：扩充二叉树的判定（所有结点度为零）
void CountDegree(BTNode *t, int *count)
{
    if (!t)
        return;
    if ((t->lchild && !t->rchild) || (!t->lchild && t->rchild))
        (*count)++;
    CountDegree(t->lchild, count);
    CountDegree(t->rchild, count);
}
bool Is2Tree(BinaryTree *tree)
{
    int count = 0;
    CountDegree(tree->root, &count);
    if (count == 0)
        return true;
    else
        return false;
}

// 6-拓展2：二叉搜索树的判定
bool LeftLower(BTNode *t, int x)
{
    if (!t)
        return true;
    return t->element < x && LeftLower(t->lchild, x) && LeftLower(t->rchild, x);
    // 三个条件：x大于此结点、x大于此结点的左子树、x大于此结点的右子树
}
bool RightLarger(BTNode *t, int x)
{
    if (!t)
        return true;
    return t->element > x && RightLarger(t->lchild, x) && RightLarger(t->rchild, x);
    // 三个条件：x小于此结点、x小于此结点的左子树、x小于此结点的右子树
}
bool IsBinarySearchTree(BTNode *t)
{
    if (!t)
        return true;
    return LeftLower(t->lchild, t->element) &&
           RightLarger(t->rchild, t->element) &&
           IsBinarySearchTree(t->lchild) &&
           IsBinarySearchTree(t->rchild);
    // 四个条件：此结点大于其左子树上的全部结点、小于其右子树上的全部结点、左子树为BST、右子树为BST
}
bool BinarySearchTree(BinaryTree *tree)
{
    return IsBinarySearchTree(tree->root);
}

// 6-拓展3：AVL树（平衡二叉搜索树）的判定
bool IsBalance(BTNode *t) //判断二叉树平衡（左子树和右子树高度差小于1）
{
    if (!t)
        return true;
    int l = Height(t->lchild);
    int r = Height(t->rchild);
    return abs(l - r) <= 1 && IsBalance(t->lchild) && IsBalance(t->rchild);
    // 三个条件：左右子树高度差小于1、左子树平衡，右子树平衡
}
bool IsAVL(BinaryTree *tree)
{
    return IsBinarySearchTree(tree->root) && IsBalance(tree->root);
}

// 7. 判断二叉树各结点存储数据的平均值
/* 计算结点总和 */
void Sum1(BTNode *t, int *count)
{
    if (!t)
        return;
    else
        *count += t->element;
    Sum1(t->lchild, count);
    Sum1(t->rchild, count);
}
double Avg1(BinaryTree *tree)
{
    int count = 0, size = 0;
    if (!tree->root)
        return false;
    Sum1(tree->root, &count);
    size = Size(tree->root);
    return (double)count / size;
}
/* 计算结点总和(优化) */
// 在计算结点个数时求和
void Sum2(BTNode *t, int *count, int *size)
{
    if (!t)
        return;
    *count += t->element;
    *size += 1;
    Sum2(t->lchild, count, size);
    Sum2(t->rchild, count, size);
}
double Avg2(BinaryTree *tree)
{
    int count = 0, size = 0;
    if (!tree->root)
        return false;
    Sum2(tree->root, &count, &size);
    return (double)count / size;
}

// 8.集合元素用二叉树存，求集合A和B的交集，空间复杂度为: O(1)
/* 计算交集 */
void OutputIntersection(BTNode *tA, BTNode *tB)
{
    if (!tA)
        return;
    if (IsExist(tB, tA->element))
        printf("%d", tA->element);
    OutputIntersection(tA->lchild, tB);
    OutputIntersection(tA->rchild, tB);
}
void Intersection(BinaryTree *tree1, BinaryTree *tree2)
{
    OutputIntersection(tree1->root, tree2->root);
}

// 9.求孩子兄弟表示法中x的父节点
typedef struct tNode
{
    int element;
    struct tNode *leftChild;
    struct tNode *rightSibling;
} TNode;

// 层次遍历
void FindParent(TNode *t, int x, TNode **parent)
{
    if (!t)
        return;
    TNode *p = t->leftChild;
    while (p)
    {
        if (p->element == x)
        {
            *parent = t;
            return;
        }
        p = p->rightSibling;
    }
    FindParent(t->leftChild, x, parent);
    FindParent(t->rightSibling, x, parent);
}
TNode *FindF(TNode *root, int x)
{
    TNode *p;
    FindParent(root, x, &p);
    return p;
}

// 10.求二叉搜索树搜索成功的ASL
void SumAndCount(BTNode *t, int *sum, int *count)
{
    if (!t)
        return;
    *sum += t->element;
    *count += 1;
    SumAndCount(t->lchild, sum, count);
    SumAndCount(t->rchild, sum, count);
}
double Avg(BinaryTree *tree)
{
    if (!tree->root)
        return 0;
    int sum = 0, count = 0;
    SumAndCount(tree->root, &sum, &count);
    return (double)sum / count;
}