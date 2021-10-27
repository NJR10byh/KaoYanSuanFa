#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MaxSize 10
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

/*
初始：top指向0，top指向栈顶元素的下一个元素
*/

//判断栈空
bool EmptyOrFull(Stack S)
{
    if (S.top == MaxSize || S.top == 0)
        return true;
    else
        return false;
}
// 进栈
bool Push(Stack S, int x)
{
    if (S.top == MaxSize)
        return false; //栈满
    else
    {
        S.data[S.top++] = x;
        return true;
    }
}
// 出栈
int Pop(Stack S)
{
    if (S.top == 0)
        return false; //栈空
    else
    {
        int x = 0;
        x = S.data[S.top--];
        return x;
    }
}
//  读栈顶元素
int GetTop(Stack S)
{
    if (S.top == 0)
        return false; //栈空
    else
        return S.data[S.top];
}
//判断队空
bool IfQueueEmpty(Queue Q)
{
    if (Q.front == Q.rear)
        return true;
    else
        return false;
}
//判断队满
bool IfQueueFull(Queue Q)
{
    if ((Q.rear + 1) % MaxSize == Q.front)
        return true;
    else
        return false;
}
// 入队
bool EnQueue(Queue Q, int x)
{
    if (IfQueueFull(Q))
        return false; //栈满
    else
    {
        Q.data[++Q.rear] = x;
        return true;
    }
}
// 出队
int OutQueue(Queue Q)
{
    if (IfQueueEmpty(Q))
        return false; //栈空
    else
    {
        int x = 0;
        x = Q.data[++Q.front];
        return x;
    }
}
//  读队头元素
int GetQueueTop(Queue Q)
{
    if (IfQueueEmpty(Q))
        return -1; //栈空
    else
        return Q.data[Q.front + 1];
}

// 1.检查表达式中括号是否配对
bool IfMatch(char arr[], int n)
{
    int i;
    Stack S;
    for (i = 0; i < n; i++)
    {
        if (arr[i] == '(' || arr[i] == '[' || arr[i] == '{')
            Push(S, arr[i]);
        else if (arr[i] == ')' || arr[i] == ']' || arr[i] == '}')
        {
            if (!EmptyOrFull(S))
            {
                if (!(GetTop(S) == '(' && arr[i] == ')' || GetTop(S) == '[' && arr[i] == ']' || GetTop(S) == '{' && arr[i] == '}'))
                    return false;
            }
            else
                return false;
        }
    }
    if (S.top == 0)
        return true;
    else
        return false;
}

// 2.利用队列逆置栈中元素
// 设定起始状态，栈中有元素并且队列为空，队列中可存放元素个数大于栈中元素个数
void ReverseStack(Stack S, Queue Q)
{
    // 如果栈不空，就将栈顶元素入队
    while (!EmptyOrFull(S))
    {
        EnQueue(Q, Pop(S));
    }
    // 如果队列不空，就将队头元素入栈
    while (!IfQueueEmpty(Q))
    {
        Push(S, OutQueue(Q));
    }
}
// 3.递归
int Pnx(int n, int x)
{
    switch (n)
    {
    case 0:
        return 1;
        break;
    case 1:
        return 2 * x;
        break;
    }
    if (n > 1)
        return 2 * x * Pnx(n - 1, x) - 2 * (n - 1) * Pnx(n - 2, x);
    else
        return -1;
}
// 3.非递归
int Pnx2(int n, int x)
{
    switch (n)
    {
    case 0:
        return 1;
        break;
    case 1:
        return 2 * x;
        break;
    }
    int i = 0, P1 = 2 * x, P2 = 1, P;
    if (n > 1)
    {
        for (i = 2; i < n; i++)
        {
            P = 2 * x * P1 - 2 * (n - 1) * P2;
            P1 = P;
            P2 = P1;
        }
        return P;
    }
    else
        return -1;
}
// 3.非递归（堆栈）
int Pnx3(int n, int x)
{
    switch (n)
    {
    case 0:
        return 1;
        break;
    case 1:
        return 2 * x;
        break;
    }
    int i = 0, P1 = 2 * x, P2 = 1, P;
    Stack S;
    Push(S, P2);
    Push(S, P1);
    if (n > 1)
    {
        for (i = 2; i < n; i++)
        {
            P1 = Pop(S);
            P2 = Pop(S);
            P = 2 * x * P1 - 2 * (n - 1) * P2;
            Push(S, P);
            Push(S, P1);
        }
        return P;
    }
    else
        return -1;
}