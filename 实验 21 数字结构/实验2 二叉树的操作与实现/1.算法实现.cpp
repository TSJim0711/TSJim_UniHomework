/*1.	二叉树的基本操作算法实现
（1）利用二叉树字符串“A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))”创建二叉树的二叉链式存储结构；
（2）输出该二叉树；
（3）输出‘H’节点的左、右孩子结点值；
（4）输出该二叉树的结点个数、叶子结点个数、二叉树的度和高度；
*/

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
        default: //是字母时
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

//输出该二叉树
void PrintBTree(BTNode* b, bool underRecursion)
{
    if (b != NULL)
    {
        cout << b->data;
        if (b->lchild != NULL || b->rchild != NULL)
        {
            cout << "(";
            PrintBTree(b->lchild, 1);
            cout << ",";
            if (b->rchild != NULL)
            {
                PrintBTree(b->rchild, 1);
                cout << ")";
            }
            if (!underRecursion)
                cout << endl;
        }
    }
}

//输出节点的左、右孩子结点值；
void seekLR(BTNode* b, char target)
{
    if (b != NULL)
    {
        if (b->data == target)
        {
            cout << "Left Child = " << ((b->lchild != NULL) ? b->lchild->data : '0');
            cout << " Right Child = " << ((b->rchild != NULL) ? b->rchild->data : '0')<<endl;
            return;
        }
        if (b->lchild != NULL)
            seekLR(b->lchild, target);
        if (b->rchild != NULL)
            seekLR(b->rchild, target);
    }
}

void addIntArray(int* being, int* by)
{
    for (int i = 0; i < 5; i++)
        cout;
  for (int i = 0; i < 3; i++)
  {
      being[i] = being[i] + by[i];
  }
  if (being[4] < by[4])
      being[4] = by[4];
}

int a;
//输出该二叉树的结点个数、叶子结点个数、二叉树的度和高度；0:结点个数,1:叶子,2:度,4:高度
int* wrapUp(BTNode* b, bool underRecursion) 
{
    int counter[5] = { 0,0,0,0,1 };
    if (b->lchild != NULL || b->rchild != NULL)
    {
        if (b->lchild != NULL)
        {

            addIntArray(counter, wrapUp(b->lchild, 1));
            counter[2]++;
        }
        if (b->rchild != NULL)
        {
            addIntArray(counter, wrapUp(b->rchild, 1));
            counter[2]++;
        }
        counter[4]++;
    }
    else
        counter[1]++;
    counter[0]++;
    if (!underRecursion)
        cout << "结点个数:" << counter[0] << " 叶子结点个数:" << counter[1] << " 二叉树的度:" << counter[2] << " 高度:" << counter[4];
    return counter;
}

int main()
{
    BTNode* bTree;
    char treeRequest[] = "A(B(D,E(H(J,K(L,M)))),C(F,G(,I)))";
    CreateBTree(bTree, treeRequest);
    PrintBTree(bTree, 0);
    seekLR(bTree, 'H');
    wrapUp(bTree, 0);
}
