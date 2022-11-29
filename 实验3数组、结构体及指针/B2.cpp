/*2、编写一个程序，用结构表示一个学生的信息，每个学生的信息包括：学号、姓名、三门成绩。要求从键盘输入学生的数据，并输出成绩表（包括每个学生的学号、姓名、三门成绩及平均分数），并输出平均分在前3名的学生的姓名及平均分。*/

#include <iostream>
#include <vector>
using namespace std;

vector<vector<char>>stuName(1, vector<char>(30,48));
vector<vector<int>>stu(6, vector<int>(1,0));


int debugDisplay()
{
	for (int m = 0; m <stuName.size(); m++)
	{
		for (int n = 0; n < stuName[m].size(); n++)
			cout << stuName[m][n] << " ";
		cout << endl;
	}
	cout << "\n---------------------\n";
	return(1);
}

int display(int target)
{
	cout << "\nStudentID:" << stu[0][target];
	cout << "\nName:";
	for (int i = 0; i <= 28; i++)
	{
		cout<<stuName[target][i];
	}
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
	char temp[30] = { 32 };
	for (i=0; i == i; i++)
	{
		cout << "StudentID:"; cin >> stu[0][i];
		cout << "Name (Max 26 bit):"; cin >> temp;
		for (j = 0; j <= 28; j++)
		{
			stuName[stuName.size()-1][j] = temp[j];
		}
		cout << "Subject 1 mark:"; cin >> stu[2][i];
		cout << "Subject 2 mark:"; cin >> stu[3][i];
		cout << "Subject 3 mark:"; cin >> stu[4][i];
		stu[5][i] = (stu[1][i] + stu[2][i] + stu[3][i]) / 3;
		cout <<"--------------------\n" << i + 1 << " student(s) info had been input." << "\nIf you want to finish the input process, input '1', else input anything:";
		cin >> j;
		cout << "--------------------\n";
		if (j == 1)
			break;
		for (j = 0; j < 6; j++)
		{
			stu[j].resize(stu[j].size() + 1);
		}
		stuName.resize(stu[0].size());
		stuName[stuName.size()-1].resize(30);
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
	}
	cout << "\n--------------------\nAll student you input are printed, and students with top 3 average mark  were shown below.\n--------------------";

	for (j = 1 ; j <= 3; j++)                                         //输出首3
	{
		cout << "\nTOP:"<<j;
		cout << "\nName:";
		for (k = 0; k <= 28; k++)
		{
			cout << stuName[rank[j]][k];
		}
		cout << "\nAverage mark:" << stu[5][rank[j]];
		cout << "\n--------------------";
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
