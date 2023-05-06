#include <iostream>
#include <vector>

using namespace std;
class people
{
public:
	void newPple();
	void edit(int,bool);

private:
	vector <vector<int>>peopleInfo;
	vector <string>peopleName;
};


void people::newPple()
{
	int role;
	peopleInfo.resize(peopleInfo.size() + 1);
	peopleInfo[peopleInfo.size() - 1].resize(3);
	peopleName.resize(peopleName.size() + 1);
	cout << "ID: " << peopleName.size() << " assigned.";
	cout << "Compelete ALL input below.";
	edit(peopleName.size() - 1, 1);
	cout << "Student:[1]\nTeacher:[2]\nGraduate:[3]\nTeaching Assistant:[4]\nTitle:[ ]\b\b";
	cin >> role;
	switch (role)
	{
	case 1:

	default:
		break;
	}
}


void people::edit(int target, bool newPple)
{
	string tempName;
	char tempGender;
	int tempIDCardNo;
	cout << "Name: "; cin >> tempName;
	cout << "ID Card No.:  "; cin >> tempIDCardNo;
	GenderInput:
	cout << "Gender [ M / F ]: [ ]\b\b"; cin >> tempGender;
	switch (newPple)
	{
	case 0:
		if (tempGender == 'M')
			peopleInfo[target][1] = 1;
		else if(tempGender == 'F')
			peopleInfo[target][1] = 0;
		else if (tempGender != NULL)
			goto GenderInput;
		if (!tempName.empty())
			peopleName[target] = tempName;
		if (tempIDCardNo != NULL)
			peopleInfo[target][2] = tempIDCardNo;
	case 1:
		if (tempGender != NULL && tempIDCardNo != NULL && !tempName.empty())
			;
	}



}
class student : virtual public people
{
public:
	//添加程序
private:
};
class teacher : virtual public people
{
public:
	//添加程序
private:
};
class graduate : public student
{
public:
	//添加程序
private:
};
class TA : public graduate, public teacher
{
public:
	//添加程序
private:
};
void main()
{
	//添加程序
}
