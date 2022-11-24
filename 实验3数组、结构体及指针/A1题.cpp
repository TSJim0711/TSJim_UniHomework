/*    1、某班期末考试科目为数学（MT）、英语（EN）和物理（PH），有最多不超过30人参加考试。考试后要求：
（1）计算每个学生的总分和平均分；
（2）按总分成绩由高到低排出成绩的名次；
（3）打印出名次表，表格内包括学生编号、各科分数、总分和平均分；
（4）任意输入一个学号，能够查找出该学生在班级中的排名及其考试分数。
*/

#include <iostream>
using namespace std;

int stuID[31], mathScore[31], engScore[31], phyScore[31], averageScore[31], fullScore[31], highestScore;

int showIntel(int j)
{
    cout << "\nStudent ID: " << stuID[j] << "\nMath score: " << mathScore[j] << "\nEnglish Score:" << engScore[j] << "\nPhysic Score:" << phyScore[j] << "\nFull mark:" << fullScore[j] << "\nAverage:" << averageScore[j] << "\n---------------------";
    return(j);
}

int switcher(int from, int to)
{
    stuID[to] = stuID[from];
    mathScore[to] = mathScore[from];
    engScore[to] = engScore[from];
    phyScore[to] = phyScore[from];
    averageScore[to] = averageScore[from];
    fullScore[to] = fullScore[from];
    return(fullScore[to]);
}

int main()
{
    int temp ,counter, i, j, k;
    cout << "Input student's ID, MATHS score, ENG score and physic score respectively:" << endl;
    for (i = 1; i <= 30; i++)
    {
        cin >> stuID[i] >> mathScore[i] >> engScore[i] >> phyScore[i];
        fullScore[i] = engScore[i] + mathScore[i] + phyScore[i];
        averageScore[i] = fullScore[i] / 3;
        cout << i << "/30 student(s) had been input." << endl << "Input “1” to finish the input process,else input anything: ";
        cin >> j;
        if (j == 1) break;
    }

    for (j = 1; j <= i; j++)
    {
        highestScore = fullScore[j];
        for (k = j; k <= i; k++)
        {
            if (fullScore[k] < highestScore)
            {
                switcher(k, 31);
                switcher(j, k);
                highestScore = switcher(31, j);
            }
        }
    }
    for (j = 1; j <= i; j++) 
        showIntel(j);

    for (; i == i;)
    {
        cout << "\nEnter a student ID to search:";
        cin >> temp;
        counter = 0;
        for (k = 1; k <= i; k++)
        {
            if (temp == stuID[k])
            {
                showIntel(k);
                counter++;
            }
        }
        if (counter == 0)
            cout << "\nStudent ID not found, please retry.";
        cout << "\nSearch ended.\n---------------------";
    }
}
