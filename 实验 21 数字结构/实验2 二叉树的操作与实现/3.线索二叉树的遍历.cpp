//线索二叉树的遍历
//中序线索化二叉树并找出根结点的前驱和后继。

#include <iostream>

using namespace std;
typedef char ElemType;
typedef struct node
{
    ElemType data;
    int ltag, rtag;
    struct node* lchild;
    struct node* rchild;
}TBTNode;
TBTNode* theRoot;
TBTNode* pre;
TBTNode* CreateThread(TBTNode* b)//创建线索二叉树根节点
{
    TBTNode* root;
    root = (TBTNode*)malloc(sizeof(TBTNode));
    root->ltag = 0;
    root->rtag = 1;
    root->lchild = b;
    if (b == NULL)
        root->lchild = root;
    else
    {
        root->lchild = b;
        pre = root;
    }
    theRoot = root;
    return root;
}

void CreateBTree(TBTNode*& b, char* str)
{
    TBTNode* st[100], * p = NULL;
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
            p = (TBTNode*)malloc(sizeof(TBTNode));
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

void Thread(TBTNode*& p, bool underRecursion)
{
    if (p != NULL)
    {
        Thread(p->lchild,1);
        if (p->lchild == NULL)
        {
            p->lchild = pre;
            p->ltag = 1;
        }
        else
            p->ltag = 0;
        if (pre->rchild == NULL)
        {
            pre->rchild = p;
            pre->rtag = 1;
        }
        else
            pre->rtag = 0;
        pre = p;
        Thread(p->rchild,1);
    }
    if(!underRecursion)
    {//应对最后
        pre = p;
        while (pre->rtag ==0)
            pre = pre->rchild;
        pre->rchild = theRoot;
        pre->rtag = 1;

    }
}

void ThInOrder(TBTNode * &source, char target)
{
    TBTNode* p = source->lchild;
    while (p != source)
    {
        while (p->ltag == 0)//=0
            p = p->lchild;
        while (p->rtag == 1 && p->rchild != source)
        {
            if (p->data == target)
                break;
            p = p->rchild;
        }
        if (p->data == target || p->rchild->data == target)
        {
            if (p->rchild->data == target)
                p = p->rchild;
            TBTNode* tempP;
            string toString;
            if (p->ltag != 1)
            {
                tempP = p->lchild;
                while (tempP->rtag == 0)
                    tempP = tempP->rchild;
                cout << "Pre-Node: " << tempP->data<<",  ";
            }else
                cout << "Pre-Node: " << ((p->lchild == source)?"Root" : toString=p->lchild->data)<<", ";
            if (p->rtag != 1 && p->rtag != NULL)
            {
                tempP = p->rchild;
                while (tempP->ltag == 0)
                    tempP = tempP->lchild;
                cout << "Pre-Node: " << tempP->data;
            }
            else
                cout << "Post-Node: " << ((p->rchild == source) ? "Root" : toString = p->rchild->data);
            return;
        }
        p = p->rchild;
    }
}

void destoryTBTree(TBTNode* node)
{
    if (node->lchild == NULL &&  node->ltag == 0)
        destoryTBTree(node->lchild);
    if (node->rchild == NULL && node->rtag == 0)
        destoryTBTree(node->rchild);
    free(node);
}

int main()
{
    TBTNode *p;
    char treeRequest[] = "A(B(D(,G)),C(E,F))";
    CreateBTree(p, treeRequest);
    p=CreateThread(p);
    Thread(p->lchild,0);
    char target;
    cout << "Enter a node to seek: ";
    cin >> target;
    ThInOrder(theRoot, target);
    destoryTBTree(theRoot);
}

