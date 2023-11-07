#include <iostream>
#include <ctime>

using namespace std;
typedef int DataType;
struct SNode
{
    DataType  data;//数据域
    struct SNode* next;//后继节点指针
};

void InitStack(SNode*& top)
{
    top = NULL;
}

bool StackEmpty(SNode* top)
{
    if (top == NULL)
        return true;
    else return false;
}

int Push(SNode** top, DataType item)
{
    SNode* temp;
    temp = (SNode*)malloc(sizeof(SNode));
    if (temp == NULL)
        return 0;
    temp->data = item;
    temp->next = *top;
    *top = temp;
    return 1;
}

int Pop(SNode* top, DataType& item)
{
    if (StackEmpty(top))
        return 0;
    SNode* temp = top;
    item = temp->data;
    top = temp->next;
    free(temp);
    return 1;
}

int GetTop(SNode* top, DataType& item)
{
    if (StackEmpty(top))
        return 0;
    item = top->data;
    return 1;
}

void Destroy(SNode*& top)
{
    SNode* temp;
    while (top != NULL)
    {
        temp = top;
        top = top->next;
        free(temp);
    }
}

int main()
{
    SNode* top;
    DataType item=10;
    InitStack(top);
    Push(&top, item);
    GetTop(top, item);
}
