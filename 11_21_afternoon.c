#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct bTNode{
    int element;
    struct bTNode *lchild;
    struct bTNode *rchild;
}BTNode;
typedef struct binaryTree{
    BTNode *root;
} BinaryTree;

// 判断二叉树镜像对称
bool DuiChen(BTNode *t1,BTNode *t2){
    if(!t1&&!t2) return true; // 左右都不存在，对称
    if(!t1||!t2) return false; // 左右只存在一个，显然不对称
    return (t1->element==t2->element) && DuiChen(t1->lchild,t2->rchild) && DuiChen(t1->rchild)&&DuiChen(t2->lchild);
}
bool IfDuiChen(BinaryTree *tree){
    if(!tree->root) return true;
    bool Ifduichen=DuiChen(tree->root,tree->root);
}

// 判读图从i到j路径需增加一个判断条件
if(i<0||i>=L->n||j<0||j>=L->n||i==j) return false; // 判断i，j的合法性