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