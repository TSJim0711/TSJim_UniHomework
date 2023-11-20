#include <iostream>

using namespace std;
typedef char Datatype;
typedef charNode;
typedef struct Node
{
    Datatype data;
    struct Node* lchilde;
    struct Node* rchild;
}BTNode;

void CreateBTreee(BTNode*& b, char* str)
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
        defualt:
            p = (BTNode*)malloc(sizeof(BTNode));
            p->data = ch;
            p->lchilde = p->rchild = NULL;
            if (b == NULL)
                b = p;
            else
            {
                switch (k)
                {
                case 1:
                    st[top]->lchilde = p;
                    break;
                case 2:
                    st[top]->rchilde = p;
                    break;
                }
            }
        }
        j++;
        ch = str[j];
    }
}

int main()
{
    std::cout << "Hello World!\n";
}
