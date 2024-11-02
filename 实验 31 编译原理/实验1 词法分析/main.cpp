#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct wordCells
{ 
    string word;
    int token;
};

vector<wordCells> wordList = 
{
{ "main",1},
{ "int",2 },
{ "char",3 },
{ "if",4 },
{ "else",5 },
{ "for",6 },
{ "while",7 },
{ "return",8 },
{ "void",9 },
{ "ID",10 },
{ "“",11 },
{ "”",12 },
{ "=",21 },
{ "+",22 },
{ "-",23 },
{ "*",24 },
{ "/",25 },
{ "(",26 },
{ ")",27 },
{ "[",28 },
{ "]",29 },
{ "{",30 },
{ "},",31 },
{ ",",32 },
{ ":",33 },
{ ";",34 },
{ ">",35 },
{ "<",36 },
{ ">=",37 },
{ "<=",38 },
{ "==",39 },
{ "!=",40 },
{ "!",41 },
{ "STRING",50 },
{ "NUM",60 }

};

vector<wordCells> wordCodePend(string inptWrd)
{
    vector<wordCells> tempArray,optArray;//输出时："{" optArray[x].token "," optArray[x].word "}"
    string curReading;
    int token,cursor=0,operatorFlag=0;
    istringstream isString(inptWrd);
    int tempInt; string tempString;

    if (inptWrd.front() == inptWrd.back() == '\"')//是string，当被""包围
        return {{inptWrd,50 }};
    
    if (isString >> tempInt)//是整数
        if (!(isString >> tempString))
            return { {inptWrd,20 } };

    for (int curWordCode = 0; curWordCode < 9; curWordCode++)//是关键字，关键字结束于9行
    {
        if (inptWrd == wordList[curWordCode].word)
            return { {inptWrd,curWordCode } };
    }

    for (cursor = 0; cursor < inptWrd.length(); cursor++)//是运算符+-*/=等
    {
        curReading=(inptWrd[cursor]);
        for (int curWordCode = 10; curWordCode < wordList.size(); curWordCode++)//运算符在10行开始
        {
            if (inptWrd[cursor] == wordList[curWordCode].word.back())
            {
                operatorFlag=1;
                optArray.push_back({ string(1,inptWrd[cursor]),curWordCode });
            }
            if (operatorFlag)
                break;
        }
        if (operatorFlag)
            break;
    }
    if (operatorFlag)//是运算符,但是因为不会用空格间隔,取前后
    {
        if (cursor > 0)//取掉目前一位，前后都递归寻找token
        {
            tempArray = wordCodePend(inptWrd.substr(0, cursor));
            optArray.insert(optArray.begin(), tempArray.begin(), tempArray.end());
        }
        if (cursor < inptWrd.size() - 1)
        {
            tempArray = wordCodePend(inptWrd.substr(cursor + 1, inptWrd.size()));
            optArray.insert(optArray.end(), tempArray.begin(), tempArray.end());
        }
        return optArray;
    }

    return { {inptWrd,10 } }; //乱七八糟的只能是人起的参数名了
}


int main()
{
    string inpt, curReading;
    vector<wordCells>optArray,tempArray;
    int cursor = 0;
    getline(cin, inpt);
    while (cursor <= inpt.size())
    {
        if (inpt[cursor] == ' '||cursor==inpt.size())//如果是空格或读完，送去编码
        {
            tempArray= wordCodePend(curReading);
            optArray.insert(optArray.end(), tempArray.begin(), tempArray.end());
            curReading.clear();
        }
        else
            curReading += inpt[cursor]; 
        cursor++;
    }
    for (int i = 0; i < optArray.size(); i++)
        cout << "{" << optArray[i].token << "," << optArray[i].word << "}";
}

