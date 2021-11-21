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
    if(!t1&&!t2) return true;
    if(!t1||!t2) return false;
    return (t1->element==t2->element) && DuiChen(t1->lchild,t2->rchild) && DuiChen(t1->rchild)&&DuiChen(t2->lchild);
}
bool IfDuiChen(BinaryTree *tree){
    if(!tree->root) return true;
    bool Ifduichen=DuiChen(tree->root,tree->root);
}