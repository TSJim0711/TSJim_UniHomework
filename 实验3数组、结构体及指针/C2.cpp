/*2、 通过指针和动态存储处理下面的问题：利用随机函数模拟产生300个1~12月出生的人数，统计本次运行得到的数据中，各个月的出生率是多少。*/
#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

int main()
{
    int dataPool[300];
    srand(time(0));
    vector<vector<int>>monthDivide(12, vector<int>(1));
    for (int i = 0; i <= 299; i++)
    {
        dataPool[i] = rand() % 12 + 1;
        monthDivide[dataPool[i]-1].resize(monthDivide[dataPool[i]-1].size() + 1);
    }
    for (int i = 1; i <= 12; i++)
    {
        cout << i << "月出生率比例：" << monthDivide[dataPool[i]-1].size() / 3 <<"%" << endl;
    }
}
