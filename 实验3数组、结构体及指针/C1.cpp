/*1、 要求使用指针处理下面的问题，输入四个整数，按由小到大的顺序输出；然后将程序改为：输入四个字符串，按由小到大顺序输出。（使用指针或指针数组）*/

#include <iostream>
using namespace std;

int main()
{
    int No1, No2, No3, No4, * arr[4]{ &No1,&No2,&No3,&No4 }, rank[5] = { 0,-1,-1,-1,-1 }, i, j;
    for (int i = 1; i <= 4; i++)
        cin >> *arr[i - 1];
    for (i = 1; i <= 3; i++)
    {
        for (j = 0; j <= 4; j++)
        {
            if (rank[j] == -1)
            {
                rank[j] = i;
                j = 5;
            }
            else if (rank[j] != -1 && *arr[i] > *arr[rank[j]])
            {
                for (int k = 3; k >= j; k--)
                    rank[k + 1] = rank[k];
                rank[j] = i;
                j = 5;
            }
        }
    }
    for (int i = 0; i <= 3; i++)
    {
        cout << *arr[rank[i]] << endl;
    }
}
