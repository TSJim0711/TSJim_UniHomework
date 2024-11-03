#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

struct wordCells
{
    string word;
    int token;
};
int globExpect = 0;
/*
0=任何
1=(/）
2=参数
3=运算符
*/

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
{ "\"",11 },
{ "\'",12 },
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
{ "!",37 },
{ ">=",38 },
{ "<=",39 },
{ "==",40},
{ "!=",41 },
{ "><",42 },
{ "//",-1 },
{ "/*",-2 },
{ "ID",10 },
{ "STRING",50 },
{ "INT",60 },
{ "FLOAT",70 },
{ "HEXNUM",80 }
};

vector<wordCells> wordCodePend(string inptWrd)
{
    vector<wordCells> tempArray, optArray;//输出时："{" optArray[x].word "," optArray[x].token "}"
    string curReading;
    int token, cursor = 0, operatorFlag = 0;
    istringstream isFloat(inptWrd);
    istringstream isString(inptWrd);
    int tempInt; string tempString;

    if (inptWrd.front() == inptWrd.back() == '\"')//是string，当被""包围
        return { {inptWrd,50 } };

    for (int curWordCode = 0; curWordCode < 9; curWordCode++)//是关键字，关键字结束于9行
    {
        if (inptWrd == wordList[curWordCode].word)
            return { {inptWrd,curWordCode } };
    }

    for (cursor = 0; cursor < inptWrd.length(); cursor++)//是运算符+-*/=等
    {
        curReading = (inptWrd[cursor]);
        for (int curWordCode = 10; curWordCode < wordList.size(); curWordCode++)//运算符在10行开始
        {
            if (string(1, inptWrd[cursor]) == wordList[curWordCode].word)
            {
                operatorFlag = 1;
                optArray.push_back({ string(1,inptWrd[cursor]),wordList[curWordCode].token });
            }
            if (string(1, inptWrd[cursor]) + string(1, inptWrd[cursor + 1]) == wordList[curWordCode].word)//是复合运算符 >= <= ==等
            {
                operatorFlag = 2;
                optArray[optArray.size() - 1] = { wordList[curWordCode].word,wordList[curWordCode].token };//是复合运算符，则更新结果
            }
        }
        if (operatorFlag)
            break;
    }
    if (operatorFlag)//是运算符,但是因为不会用空格间隔,所以历遍
    {
        if (cursor > 0)//取掉目前一位，前后都递归寻找token
        {
            tempArray = wordCodePend(inptWrd.substr(0, cursor));
            optArray.insert(optArray.begin(), tempArray.begin(), tempArray.end());
        }
        if (cursor < inptWrd.size() - 2 + operatorFlag && (optArray.back().token != -1|| optArray.back().token != -2))//是复合运算符则向后一位,并且不存在注释
        {
            tempArray = wordCodePend(inptWrd.substr(cursor + operatorFlag, inptWrd.size()));
            optArray.insert(optArray.end(), tempArray.begin(), tempArray.end());
        }

        return optArray;
    }

    if (count(inptWrd.begin(), inptWrd.end(), '.') == 1)//是双精度
        return { {inptWrd,70 } };

    if (isString >> tempInt)//是DEX整数
        if (!(isString >> tempString))
            return { {inptWrd,60 } };

    if (inptWrd[0] == '0' && inptWrd[1] == 'x')//是HEX整数,以0x开始
        return { {inptWrd,80 } };

    return { {inptWrd,10 } }; //乱七八糟的只能是人起的参数名了,所以包含带下划线的标识符
}


int main()
{
    string sd;
    ifstream sourceCodeFile;
    sourceCodeFile.open("sourceCode.txt");
    if (!sourceCodeFile.is_open())
    {
        cout << "无法打开源代码文件";
        return 0;
    }
    string inpt, curReading;
    vector<wordCells>optArray, tempArray;
    int cursor = 0 ,CommentFlag = 0;
    while (getline(sourceCodeFile, inpt))//逐行读入文件
    {
        cursor = 0;//换行重置光标
        while (cursor <= inpt.size())
        {
            if ((inpt[cursor] == ' ' || cursor == inpt.size()) && !CommentFlag)//如果是空格或读完，送去编码，注释后无视
            {
                tempArray = wordCodePend(curReading);
                if (tempArray.back().token < 0)//进入注释状态
                {
                    CommentFlag == tempArray.back().token;
                    tempArray.erase(tempArray.end() - 1);
                }
                optArray.insert(optArray.end(), tempArray.begin(), tempArray.end());
                curReading.clear();
            }
            else if(CommentFlag==-2 && inpt[cursor]=='/')//是/*  */注释
            {
                if (inpt[cursor - 1] == '*')
                {
                    cout << "错误！注释存在嵌套";
                    return 0;
                }
                else if (inpt[cursor + 1] == '*')//退出注释状态
                    CommentFlag = 0;
            }
            else
                curReading += inpt[cursor];
            cursor++;
        }
    if (CommentFlag && inpt[cursor] == '\n')//换行时取消注释状态
        CommentFlag == false;
    }
    for (int i = 0; i < optArray.size(); i++)
        cout << "{" << optArray[i].token << "," << optArray[i].word << "}";
}
