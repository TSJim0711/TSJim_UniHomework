/*   1、定义一个结构变量（包括年、月、日），计算该日在本年中为第几天？（注意考虑闰年问题），要求写一个函数days，实现上面的计算。
由主函数将年月日传递给days函数，计算后将日子传递回主函数输出。
*/

#include <iostream>
using namespace std;
int days(int year, int month, int day)
{
    int correction, result;
    correction=0.56*month;
    if (year % 4 && month > 2)
        correction = correction - 2;
    else if (year % 4 == 0 && month > 2)
        correction = correction - 1;
    result = (month - 1) * 30 + day + correction;
    return result;
}

int main()
{
    int year, month, day;
    cout << "Input year, month, day in order :"<<endl;
    cin >> year >> month >> day;
    cout<<days(year, month, day);
}