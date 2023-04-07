/*1、以下是Point类的定义以及重载运算符“<<”和“>>”的算法的基本实现。请增加重载运算符“+”等的实现，必要时可能需要相应修改重载运算符“<<”和“>>”的实现。请对增加的实现功能和修改之处做适当说明。#include  <iostream>
using namespace std;
class Point
{  int x , y ;
public:
	Point(){};
    friend istream & operator >> (istream &in, Point &p) ;    //重载运算符">>"
    friend ostream & operator << (ostream &out, Point &p) ;  //重载运算符"<<"
} ;
istream & operator >> ( istream & in , Point & p )
{
        cout<<"请输入x, y的值："<<endl ;
        cout<<"x＝";
        in>>p.x;
        cout <<"y＝";
        in>>p.y;
        return in;
}
ostream & operator << ( ostream & out , Point & p )
{
          out <<"输出x, y的值"<< endl ;
          out<<"x＝"<<p.x<<"   y=" << p.y<<endl;
          return out;
}

int main()
{  
	Point P;
	cin>>P;
	cout<<P ;
}
*/

#include  <iostream>
using namespace std;
class Point
{
    int x, y;
public:
    Point() {};
    friend istream& operator >> (istream& in, Point& p);    //重载运算符">>"
    friend ostream& operator << (ostream& out, Point& p);  //重载运算符"<<"
    friend Point operator+(const Point& lhs, const Point& rhs);
    friend Point operator*(const Point& lhs, const Point& rhs);
};
istream& operator >> (istream& in, Point& p)
{
    cout << "请输入x, y的值：" << endl;
    cout << "x＝";
    in >> p.x;
    cout << "y＝";
    in >> p.y;
    return in;
}
ostream& operator << (ostream& out, Point& p)
{
    out << "输出x, y的值" << endl;
    out << "x＝" << p.x << "   y=" << p.y << endl;
    return out;
}

Point operator+(const Point& apt, const Point& bpt)
{
	Point temp;
	temp.x = apt.x + bpt.x;
	temp.y = apt.y + bpt.y;
	return temp;
}

Point operator*(const Point& apt, const Point& bpt)
{
	Point temp;
	temp.x = apt.x * bpt.x;
	temp.y = apt.y * bpt.y;
	return temp;
}



int main()
{
    Point P;
    cin >> P;
    P=P+P;
    cout << P;
    P = P * P;
    cout << P;
}
