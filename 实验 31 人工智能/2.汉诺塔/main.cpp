#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

struct hanoTowers
{
    vector<int>tw1;
    vector<int>tw2;
    vector<int>tw3;
};
hanoTowers towers;
int no = 1;
int LoopCount = 0;
void printHanoTowers(const hanoTowers& towers) {
    cout << no << "------------------\n";
    no++;
    cout << "塔 1: ";
    for (int disc : towers.tw1) {
        cout << disc << " ";
    }
    cout << endl;

    cout << "塔 2: ";
    for (int disc : towers.tw2) {
        cout << disc << " ";
    }
    cout << endl;

    cout << "塔 3: ";
    for (int disc : towers.tw3) {
        cout << disc << " ";
    }
    cout << endl<<endl;
}

void move(vector<int>& from, int fromLoc, vector<int> &to, vector<int>&temp)
{
    LoopCount++;
    bool execFlag = false;
    while(!execFlag)//不断尝试直到可以执行
    {
        if (&from[fromLoc] != &from.back())//出发点上方有阻挡
            move(from, fromLoc + 1, temp, to);
        else if (to.size() != 0 && from[fromLoc] > to.back())//目的地有阻挡
        {
            for (int i = to.size() - 1; i >= 0; i--)//找到目的地>自己的碟+1，或地板
                if (from[fromLoc] < to[i] || i == 0)
                {
                    move(to, i + (from[fromLoc] < to[i] ? 1 : 0), temp, from); //找到>自己的碟, + 1
                    break;
                }
        }
        else
        {
            to.push_back(from[fromLoc]);
            from.pop_back();
            execFlag = true;
            printHanoTowers(towers);
        }
    }
}

int main()
{
    int x;
    cin >> x;

    clock_t begin = clock();
    for (int i = x; i > 0; i--)//初始化x个碟
        towers.tw1.push_back(i);
    for(int i=0;i<x/2;i++)
    {
        move(towers.tw1, 0, towers.tw3, towers.tw2);
        move(towers.tw2, 0, towers.tw3, towers.tw1);
    }
    if(x%2!=0)//总数为单数
        move(towers.tw1, 0, towers.tw3, towers.tw2);
    clock_t end = clock();
    cout << "执行时钟周期数：" << (end - begin)<<endl;
    cout << "调用次数：" << LoopCount;
}