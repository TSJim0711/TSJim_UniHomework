/*2、不用字符串处理函数将两个字符串连接，即将字符串b连接到字符串a的后面，变成字符串c。*/
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
