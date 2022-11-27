// ConsoleApplication3.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>>stu(6, vector<int>(1, 0));

int debugDisplay()
{
	for (int m = 0; m <stu.size(); m++)
	{
		for (int n = 0; n < stu[m].size(); n++)
			cout << stu[m][n] << " ";
		cout << endl;
	}
	cout << "\n---------------------\n";
	return(1);
}

int display(int target)
{
	cout << "\nStudentID:" << stu[0][target];
	cout << "\nName:" << stu[1][target];
	cout << "\nSubject 1 mark:" << stu[2][target];
	cout << "\nSubject 2 mark:" << stu[3][target];
	cout << "\nSubject 3 mark:" << stu[4][target];
	cout << "\nAverage:" << stu[5][target];
	cout << "\n--------------------";
	return(69);
}

int main()
{
	int rank[4], i, j, k;                                                                     //输入
	cout << "\n---------------------\n";
	for (i=0; i == i; i++)
	{
		cout << "StudentID:"; cin >> stu[0][i];
		cout << "Name:"; cin >> stu[1][i];
		cout << "Subject 1 mark:"; cin >> stu[2][i];
		cout << "Subject 2 mark:"; cin >> stu[3][i];
		cout << "Subject 3 mark:"; cin >> stu[4][i];
		stu[5][i] = (stu[1][i] + stu[2][i] + stu[3][i]) / 3;
		cout <<"--------------------\n" << i + 1 << "student intel had been input." << "\nIf you want to finish the input process, input '1', else input anything:";
		cin >> j;
		cout << "--------------------";
		if (j == 1)
			break;
		for (j = 0; j < 6; j++)
		{
			stu[j].resize(stu[j].size() + 1);
		}
		debugDisplay();
	}

	rank[1] = 0;
	rank[2] = 0;
	rank[3] = 0;
	for (j = 0; j <= i; j++)                                                              //输出全部，找首3
	{
		display(j);	
		if (stu[5][j] > stu[5][rank[1]])
		{
			rank[3] = rank[2];
			rank[2] = rank[1];
			rank[1] = j;
		}
		else if (stu[5][j] > stu[5][rank[2]])
		{
			rank[3] = rank[2];
			rank[2] = j;
		}
		else if (stu[5][j] > stu[5][rank[3]])
		{
			rank[3] = j;
		}
		cout << rank[1] << " " << rank[2] << " " << rank[3];
	}
	cout << "\n--------------------\nAll student you input are printed, and students with top 3 average mark  were shown below.\n--------------------";

	for (j = 1 ; j <= 3; j++)
	{
		cout<<"Name:" << stu[1][rank[j]];
		cout << "Average mark:" << stu[5][rank[j]];
	}
	/*for (j = 0; j <= 2; j++)
	{
		for (k = 0; k <= i; k++)
		{
			if (stu[5][j] < stu[5][k])
			{
				rank[1][1]
			}
		}
	}
	*/

}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
