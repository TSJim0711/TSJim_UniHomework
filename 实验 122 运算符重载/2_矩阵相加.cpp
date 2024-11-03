/*编写程序，有两个均为3行3列的矩阵ml和m2，求两个矩阵之和。
重载运算符“＋”、“>>”和“<<”，使之能用于矩阵相加、输入和输出。*/
#include <iostream>
using namespace std;


	class matrix
	{
	public:
		//定义矩阵
		int mtxA[3][3], mtxB[3][3];	
		friend istream& operator>>(istream &in, matrix&);
		friend matrix operator+(matrix, matrix);
		friend ostream& operator<<(ostream &out, matrix&);
	};
	istream& operator>>(istream& in, matrix&mtx)
	{
		for (int i = 0; i <= 2; i++)
		{//用户构建矩阵A
			for (int j = 0; j <= 2; j++)
			{
				cout << "Matrix A ["<<i<<"]["<<j<<"]: ";
				in>>mtx.mtxA[i][j];
			}
		}//矩阵B
		for (int i = 0; i <= 2; i++)
		{
			for (int j = 0; j <= 2; j++)
			{
				cout << "Matrix B [" << i << "][" << j << "]: ";
				in >> mtx.mtxB[i][j];
			}
		}
		return in;
	}

	matrix operator+(matrix mtxL, matrix mtxR)
	{
		for (int i = 0; i <= 2; i++)
		{
			for (int j = 0; j <= 2; j++)
			{
				mtxL.mtxA[i][j] = mtxL.mtxA[i][j] + mtxR.mtxB[i][j];
			}
		}
		return mtxL;
	}

	ostream& operator<<(ostream& out, matrix&mtx)
	{
		cout<<"Sum of two matrix is: "<<endl;
		for (int i = 0; i <= 2; i++)
		{
			for(int j = 0; j <= 2; j++)
				cout << mtx.mtxA[i][j] << "\t";
			cout <<endl;
		}
		return out;
	}

int main()
{
	matrix mtx;
	cin >> mtx;
	mtx= mtx + mtx;
	cout << mtx;
}
