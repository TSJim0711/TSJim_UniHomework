/*1、 要求使用指针处理下面的问题，输入四个整数，按由小到大的顺序输出；然后将程序改为：输入四个字符串，按由小到大顺序输出。（使用指针或指针数组）*/
#include <iostream>
using namespace std;

int main()
{
	string aString, bString, cString;
	cout << "a:";
	cin >> aString; 
	cout << "b:";
	cin>> bString;
	cString = bString + aString;
	cout <<"c:" << cString;
}