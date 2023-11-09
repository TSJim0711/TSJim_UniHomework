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
    SNode* top,* current;
    DataType item=10;
    InitStack(top);
    int op, userInput, userInput2;
    //随机数入链表
    srand(time(0));
    for (int i = 1; i <= 10; i++)
        Push(&top, rand() % 900 + 100);
    //Manu
    while (true)
    {
        cout << "Input\tOperation\n[1]\tPrint Stack\n[2]\tStack lookup\n[3]\tInsert data & print\nOperation [ ]\b\b";
        if (!(cin >> op))
            op= -1;
        switch (op)
        {
        case 1://输出链表内容
            current = top;
            while (current != NULL)
            {
                cout << current->data << "\t";
                current = current->next;
            }
            cout << endl;
            break;
        case 2://读入数，在？在，输出位置
            current = top;
            cout << "Input your number (integers only) : ";
            if (!(cin >> userInput))
            {
                cout << "Input rejected. Integers only";
                break;
            }
            for (int i = 1; current != NULL; i++)
            {
                if (current->data == userInput)
                    cout << "Found! In " << i<<endl;
                current = current->next;
            }
            cout << "End of seek. If no \"Found\" context, your input do not exist in stack."<<endl;
            break;
        case 3: //读入数+位置，插入数在位置，输出链表
            cout << "Input location you like to insert (integers only) : ";
            if (!(cin >> userInput))
            {
                cout << "Input rejected. Integers only.";
                break;
            }
            current = top;
            for (int i = 1; i <= userInput - 2 ; i++)
            {
                if (current != NULL)
                {
                   current = current->next;
                }
                else    
                {
                    cout << "Invalid location input, as exceed stack range.";
                    break;
                }
            }
            cout << "Input data you like to insert (integers only) : ";
            if (!(cin >> userInput2))
            {
                cout << "Input rejected. Integers only.";
                break;
            }
            SNode* temp;
            temp = (SNode*)malloc(sizeof(SNode));
            temp->data = userInput2;
            if(userInput==1) //1是特别的！要对top操作！！！！
            {
                temp->next = top->next;
                top = temp;
            }else
            {
                temp->next = current->next;
                current->next = temp;
            }
            //输出链表内容，是照搬的
            current = top;
            while (current != NULL)
            {
                cout << current->data << "\t";
                current = current->next;
            }
            cout << endl;
            break;
        default: 
            cout << "Input rejected, invalid operation code."<<endl;
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
}
