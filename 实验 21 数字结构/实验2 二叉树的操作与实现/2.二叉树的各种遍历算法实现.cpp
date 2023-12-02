//2.	二叉树的各种遍历算法实现
//实现上述二叉树的先序、中序和后序遍历的递归和非递归算法；

#include <iostream>

const int MaxSize = 100;

using namespace std;
typedef char Datatype;
typedef struct Node
{
    Datatype data;
    struct Node* lchild;
    struct Node* rchild;
}BTNode;

//创建二叉树的二叉链式存储结构
void CreateBTree(BTNode*& b, char* str)
{
    BTNode* st[MaxSize], * p = NULL;
    int top = -1, k, j = 0;
    char ch;
    b = NULL;
    ch = str[j];
    while (ch != '\0')
    {
        switch (ch)
        {
        case '(':
            top++;
            st[top] = p;
            k = 1;
            break;
        case ')':
            top--;
            break;
        case ',':
            k = 2;
            break;
        default:
            p = (BTNode*)malloc(sizeof(BTNode));
            p->data = ch;
            p->lchild = p->rchild = NULL;
            if (b == NULL)
                b = p;
            else
            {
                switch (k)
                {
                case 1:
                    st[top]->lchild = p;
                    break;
                case 2:
                    st[top]->rchild = p;
                    break;
                }
            }
        }
        j++;
        ch = str[j];
    }
}

//前序
void printBTreePre(BTNode* b)
{
    if(b != NULL)
    {
        if (b->lchild != NULL)
            printBTreePre(b->lchild);
        cout << b->data;
        if (b->rchild != NULL)
            printBTreePre(b->rchild);
    }
}

//中序
void printBTreeIn(BTNode* b)
{
    if (b != NULL)
    {
        cout << b->data;
        if (b->lchild != NULL)
            printBTreeIn(b->lchild);
        if (b->rchild != NULL)
            printBTreeIn(b->rchild);
    }
}

//后序
void printBTreePost(BTNode* b)
{
    if (b != NULL)
    {
        if (b->rchild != NULL)
            printBTreePost(b->rchild);
        cout << b->data;
        if (b->lchild != NULL)
            printBTreePost(b->lchild);
    }
}

void destoryBTree(BTNode* node)
{
    if (node->lchild == NULL)
        destoryBTree(node->lchild);
    if (node->rchild == NULL)
        destoryBTree(node->rchild);
    free(node);
}

int main()
{
    BTNode* bTree;
    char treeRequest[] = "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))";
    CreateBTree(bTree, treeRequest);
    cout << "先序：";
    printBTreePre(bTree);
    cout << "\n中序：";
    printBTreeIn(bTree);
    cout << "\n后序：";
    printBTreePost(bTree);
    destoryBTree(bTree);
}
