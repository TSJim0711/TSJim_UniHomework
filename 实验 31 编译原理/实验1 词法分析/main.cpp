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
{ "}",31 },
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

    if (inptWrd.front() == '\"')//是string，由引号开始
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

bool validSyntax(vector<wordCells>inptArray)
{
    bool validSyntaxFlag=true;
    vector<int> bracketNest;
    for (int cursor = 0; cursor < inptArray.size(); cursor++)
    {
        if (inptArray[cursor].token == 26 || inptArray[cursor].token == 28 || inptArray[cursor].token == 30)//括号([{对称
            bracketNest.push_back(inptArray[cursor].token);//左括号入栈
        if (inptArray[cursor].token == 27 || inptArray[cursor].token == 29 || inptArray[cursor].token == 31)//右括号和最新左括号正确对应，出栈
            if (bracketNest.back() == inptArray[cursor].token - 1)
                bracketNest.pop_back();
            else
            {
                cout << "错误！右括号和最近左括号并不正确对应";
                validSyntaxFlag = false;
            }
        if (inptArray[cursor].token == 10)//检测非法字符，基于除string外都容不下非法字符，其必定落入参数名
        {
            for(int idCursor=0;idCursor<inptArray[cursor].word.size();idCursor++)
                if (!(inptArray[cursor].word[idCursor] >= 48 || inptArray[cursor].word[idCursor] <= 57 ||//存在非数字
                    inptArray[cursor].word[idCursor] >= 65 || inptArray[cursor].word[idCursor] <= 90 ||//或非大写字母
                    inptArray[cursor].word[idCursor] >= 97 || inptArray[cursor].word[idCursor] <= 122))//或非小写字母
                {
                    cout << "错误！存在非法字符";
                    validSyntaxFlag = false;
                }
                else if(idCursor == 0 && (inptArray[cursor].word[idCursor] >= 30 || inptArray[cursor].word[idCursor] <= 39))
                {
                    cout << "错误！参数名不能以数字为先";
                    validSyntaxFlag = false;
                }
        }
    }

   
    return validSyntaxFlag;
}

int main()
{
    string sd;
    ifstream sourceCodeFile;
    sourceCodeFile.open("sourceCode.txt");
    if (!sourceCodeFile.is_open())
    {
        cout << "错误！无法打开源代码文件";
        return 0;
    }
    string inpt, curReading;
    vector<wordCells>optArray, tempArray;
    int cursor = 0 ,statusFlag = 0;
    while (getline(sourceCodeFile, inpt))//逐行读入文件
    {
        cursor = 0;//换行重置光标
        while (cursor <= inpt.size())
        {
            curReading.push_back(inpt[cursor]);//逐字读入
            if ((inpt[cursor] == ' ' || cursor == inpt.size()) && !statusFlag)//如果是空格或读完，送去编码，注释后无视
            {
                if(inpt[cursor] == ' ' )
                    curReading.pop_back();//推出空格
                tempArray = wordCodePend(curReading);
                if (tempArray.back().token < 0)//进入注释状态
                {
                    statusFlag == tempArray.back().token;//-1 or -2
                    tempArray.erase(tempArray.end() - 1);
                }
                if (tempArray.back().token == 50)//进入读String状态
                {
                    statusFlag == 1;
                }
                optArray.insert(optArray.end(), tempArray.begin(), tempArray.end());
                curReading.clear();
            }
            else if (statusFlag == -2 && inpt[cursor] == '/')//是/*  */注释    **注释内没有string, string内能有注释**
            {
                if (inpt[cursor - 1] == '*')
                {
                    cout << "错误！注释存在嵌套";
                    return 0;
                }
                else if (inpt[cursor + 1] == '*')//退出注释状态
                    statusFlag = false;
            }
            else if(statusFlag == 1)//如果在读string状态
            {
                optArray[optArray.size() - 1].word.push_back(inpt[cursor]);//任何文本推入string
                if (inpt[cursor] == '\"')//再读到引号，退出string状态
                    statusFlag == false;
            }
            cursor++;
        }
    if (cursor==inpt.size()+1)//加1为对冲上两行的 cursor++
        if(statusFlag == -1)//换行时取消注释状态,/* */除外
            statusFlag == false;
        else if(statusFlag == 1)
        { 
            cout << "错误！引号直到换行仍然不对称";
            return 0;
        }
    }
    for (int i = 0; i < optArray.size(); i++)
        cout << "{" << optArray[i].token << "," << optArray[i].word << "}";
}

