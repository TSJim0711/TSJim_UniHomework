#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <queue>
using namespace std;

struct dfsReturnKit
{
    vector<vector<vector<int>>>playboardHistory;
    vector<char>route;
};

vector<vector<int>>playboardTarg = { {1,2,3},{4,0,5},{6,7,8} };

dfsReturnKit dfs(vector<vector<vector<int>>>playboardHistory, vector<char> route, int depth)
{
    dfsReturnKit rtrnKit = { playboardHistory,route };
    dfsReturnKit rtrnRecv = rtrnKit;//赋值没有任何意义,主要避免rtrnRecv.route.back()虚空请求
    //最后一步，找到了？
    if (playboardHistory.back() == playboardTarg)
    {
        rtrnKit.route.push_back('#');//已经完成，添加完成符
        return rtrnKit;
    }
    else
    {
        depth++;
        //避免LOOP
        for (int i = 0; i < playboardHistory.size() - 1/*不对最后一个(目前)判断*/; i++)
            if (playboardHistory.back() == playboardHistory[i]||depth>35)//与历史重复，，代表此路不通///步骤过多（>35）
                return rtrnKit;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (playboardHistory.back()[i][j] == 0)//找到0(空格)的位置
                {
                    if (i > 0)//going up
                    {
                        playboardHistory.push_back(playboardHistory.back());
                        playboardHistory.back()[i][j] = playboardHistory.back()[i - 1][j];//与上面格交换
                        playboardHistory.back()[i - 1][j] = 0;
                        route.push_back('U');//插入路径‘上’
                        rtrnRecv = dfs(playboardHistory, route, depth);//递归
                        if (rtrnRecv.route.back() != '#')//没有找到结果，删除刚才插入的路径
                        {
                            route.pop_back();
                        }
                        playboardHistory.pop_back();
                    }
                    if (j < 2 && !(rtrnRecv.route.back() == '#'))//going right 同时未曾成功找到路线
                    {
                        playboardHistory.push_back(playboardHistory.back());
                        playboardHistory.back()[i][j] = playboardHistory.back()[i][j + 1];//与右面格交换
                        playboardHistory.back()[i][j+1] = 0;
                        route.push_back('R');//插入路径‘右’
                        rtrnRecv = dfs(playboardHistory, route, depth);//递归
                        if (rtrnRecv.route.back() != '#')//没有找到结果，删除刚才插入的路径
                        {
                            route.pop_back();
                        }
                        playboardHistory.pop_back();
                    }
                    if (i < 2 && !(rtrnRecv.route.back() == '#'))//down
                    {
                        playboardHistory.push_back(playboardHistory.back());
                        playboardHistory.back()[i][j] = playboardHistory.back()[i + 1][j];//交换
                        playboardHistory.back()[i + 1][j] = 0;
                        route.push_back('D');//插入路径
                        rtrnRecv = dfs(playboardHistory, route, depth);//递归
                        if (rtrnRecv.route.back() != '#')//没有找到结果，删除刚才插入的路径
                        {
                            route.pop_back();
                        }
                        playboardHistory.pop_back();
                    }
                    if (j > 0 && !(rtrnRecv.route.back() == '#'))//left
                    {
                        playboardHistory.push_back(playboardHistory.back());
                        playboardHistory.back()[i][j] = playboardHistory.back()[i][j - 1];//交换
                        playboardHistory.back()[i][j-1] = 0;
                        route.push_back('L');//插入路径
                        rtrnRecv = dfs(playboardHistory, route, depth);//递归
                        if (rtrnRecv.route.back() != '#')//没有找到结果，删除刚才插入的路径
                        {
                            route.pop_back();
                        }
                        playboardHistory.pop_back();
                    }
                    if (route.back() == '#'|| rtrnRecv.route.back()=='#')//成功找到路线
                        route = rtrnRecv.route;//Merge进返回线路数据
                }

            }
        }
        rtrnKit.route = route;
        return rtrnKit;
    }
}

string bfs(vector<vector<int>> vecPlayBoard)
{
    string playBoard;
    for (int x = 0; x < vecPlayBoard.size(); x++)
        for (int y = 0; y < vecPlayBoard[0].size(); y++)
            playBoard.push_back(48+vecPlayBoard[x][y]);

    string playBoardTargStr;
    for (int x = 0; x < vecPlayBoard.size(); x++)
        for (int y = 0; y < vecPlayBoard[0].size(); y++)
            playBoardTargStr.push_back(48+playboardTarg[x][y]);

    struct treeNode
    {
        string curPlayBoard;
        int zeroLoc[2];
        string route;
    };

    vector <treeNode> curBoardList = { {playBoard,{},""}};
    vector <treeNode> nextBoardList;
    string playBrdtemp;
    vector<string>playBoardHist;
    for (int i = 0; i < playBoard.size(); i++) {//寻找 0
        if (playBoard[i]=='0')//找到0(空格)的位置,记录
        {
            curBoardList.back().zeroLoc[0] = i / 3;
            curBoardList.back().zeroLoc[1] = i % 3;
        }
    }
    for (int depth = 0; depth < 35; depth++)
    {
        for (int x = 0; x < curBoardList.size(); x++)//根据上回的行动栈逐一处理
        {
            for (int histIndex = 0; histIndex < playBoardHist.size(); histIndex++)
                if (curBoardList[x].curPlayBoard == playBoardHist[histIndex])//是否与历史结果重复
                {
                    goto skipCurBoard1;//想退出双重循环只能用goto了,无视当前棋盘
                }
            playBoardHist.push_back(curBoardList[x].curPlayBoard);//新棋盘状态，推入历史

            if (curBoardList[x].curPlayBoard == playBoardTargStr)
            {
                curBoardList[x].route.push_back('#');//添加结束标
                return curBoardList[x].route;//如果是结果，返回路径。
            }
            if (curBoardList[x].zeroLoc[0] > 0)//going up
            {
                nextBoardList.push_back({ curBoardList[x].curPlayBoard , {curBoardList[x].zeroLoc[0] - 1,curBoardList[x].zeroLoc[1]}, curBoardList[x].route + 'U' });//把下一步棋盘和该路径推入临时行动栈
                nextBoardList.back().curPlayBoard[(curBoardList[x].zeroLoc[0]) * 3 + curBoardList[x].zeroLoc[1]] = nextBoardList.back().curPlayBoard[(curBoardList[x].zeroLoc[0] - 1) * 3 + curBoardList[x].zeroLoc[1]];//与上面格交换
                nextBoardList.back().curPlayBoard[(curBoardList[x].zeroLoc[0] - 1) * 3 + curBoardList[x].zeroLoc[1]] = 48;
            }
            if (curBoardList[x].zeroLoc[1] < 2)
            {
                nextBoardList.push_back({ curBoardList[x].curPlayBoard,{curBoardList[x].zeroLoc[0],curBoardList[x].zeroLoc[1] + 1}, curBoardList[x].route + 'R' });
                nextBoardList.back().curPlayBoard[(curBoardList[x].zeroLoc[0]) * 3 +curBoardList[x].zeroLoc[1]] = nextBoardList.back().curPlayBoard[(curBoardList[x].zeroLoc[0]) * 3 +curBoardList[x].zeroLoc[1] + 1];
                nextBoardList.back().curPlayBoard[(curBoardList[x].zeroLoc[0]) * 3 +curBoardList[x].zeroLoc[1] + 1] = 48;
            }
            if (curBoardList[x].zeroLoc[0] < 2)
            {
                nextBoardList.push_back({ curBoardList[x].curPlayBoard,{curBoardList[x].zeroLoc[0] + 1,curBoardList[x].zeroLoc[1]}, curBoardList[x].route + 'D' });
                nextBoardList.back().curPlayBoard[(curBoardList[x].zeroLoc[0]) * 3 +curBoardList[x].zeroLoc[1]] = nextBoardList.back().curPlayBoard[(curBoardList[x].zeroLoc[0]+1) * 3 +curBoardList[x].zeroLoc[1]];
                nextBoardList.back().curPlayBoard[(curBoardList[x].zeroLoc[0]+1) * 3 +curBoardList[x].zeroLoc[1]] = 48;
            }if (curBoardList[x].zeroLoc[1] > 0)
            {
                nextBoardList.push_back({ curBoardList[x].curPlayBoard,{curBoardList[x].zeroLoc[0],curBoardList[x].zeroLoc[1] - 1}, curBoardList[x].route + 'L' });
                nextBoardList.back().curPlayBoard[(curBoardList[x].zeroLoc[0]) * 3 +curBoardList[x].zeroLoc[1]] = nextBoardList.back().curPlayBoard[(curBoardList[x].zeroLoc[0]) * 3 +curBoardList[x].zeroLoc[1] - 1];
                nextBoardList.back().curPlayBoard[(curBoardList[x].zeroLoc[0]) * 3 +curBoardList[x].zeroLoc[1] - 1] = 48;
            }
        skipCurBoard1:
            x = x;
        }
        curBoardList = nextBoardList;//把所有可能的步骤推入行动栈
        nextBoardList.clear();
    }
    return("Too deep, too many steps");
}

int different(string curPlayBoard, int targNumLoc[9][2])
{
    int diff = 0;
    for (int i = 1; i <= 8; i++) //寻找数字位置
    {
        diff += abs(targNumLoc[curPlayBoard[i] - '0'][0] - i / 3);
        diff += abs(targNumLoc[curPlayBoard[i] - '0'][1] - i % 3);
    }
    return diff;
}

string aStar(vector<vector<int>> vecPlayBoard)
{
    string playBoard;
    for (int x = 0; x < vecPlayBoard.size(); x++)
        for (int y = 0; y < vecPlayBoard[0].size(); y++)
            playBoard.push_back(48 + vecPlayBoard[x][y]);

    string playBoardTargStr;
    for (int x = 0; x < vecPlayBoard.size(); x++)
        for (int y = 0; y < vecPlayBoard[0].size(); y++)
            playBoardTargStr.push_back(48 + playboardTarg[x][y]);

    struct treeNode
    {
        string curPlayBoard;
        int zeroLoc[2];
        int diff;
        string route;
        bool operator<(const treeNode& other) const {
            return (diff + route.size()) > (other.diff + other.route.size()); // 按照 与目标差距+步数 从小到大排序
        };
    };

    treeNode curBoard = {playBoard,{},0,""} ;
    vector <treeNode> nextBoardList;
    vector <string>playBoardHist = {playBoard};
    priority_queue<treeNode>playBoardQueue;//历史棋盘，但是 目标差距+步数 从小到大排序
    for (int i = 0; i 
        < playBoard.size(); i++) {//寻找 起始0
        if (playBoard[i] == '0')//找到0(空格)的位置,记录
        {
            curBoard.zeroLoc[0] = i / 3;
            curBoard.zeroLoc[1] = i % 3;
        }
    }
    int targNumLoc[9][2];
    for (int i = 0; i <= 8; i++) {//寻找 目标的数字位置
            targNumLoc[playBoardTargStr[i]-'0'][0] = i / 3;
            targNumLoc[playBoardTargStr[i]-'0'][1] = i % 3;
    }
    curBoard.diff = different(curBoard.curPlayBoard, targNumLoc);//定义初始棋盘与目标棋盘距离
    playBoardQueue.push(curBoard);//初始棋盘推入优先棋盘

    while( !playBoardQueue.empty())
    {
        curBoard = playBoardQueue.top();//拿到棋盘，最小：目标差距+步数
        playBoardQueue.pop();//推出拿到的棋盘
        if (curBoard.curPlayBoard == playBoardTargStr)//成功找到
        {
            curBoard.route.push_back('#');//添加结束标
            return curBoard.route;
        }

        if (curBoard.zeroLoc[0] > 0)//going up
        {
            nextBoardList.push_back({ curBoard.curPlayBoard , {curBoard.zeroLoc[0] - 1,curBoard.zeroLoc[1]}, NULL, curBoard.route + 'U'});//把下一步棋盘和该路径推入临时行动栈
            nextBoardList.back().curPlayBoard[(curBoard.zeroLoc[0]) * 3 + curBoard.zeroLoc[1]] = nextBoardList.back().curPlayBoard[(curBoard.zeroLoc[0] - 1) * 3 + curBoard.zeroLoc[1]];//与上面格交换
            nextBoardList.back().curPlayBoard[(curBoard.zeroLoc[0] - 1) * 3 + curBoard.zeroLoc[1]] = 48;
            nextBoardList.back().diff = different(nextBoardList.back().curPlayBoard, targNumLoc);
        }
        if (curBoard.zeroLoc[1] < 2)
        {
            nextBoardList.push_back({ curBoard.curPlayBoard,{curBoard.zeroLoc[0],curBoard.zeroLoc[1] + 1}, NULL, curBoard.route + 'R' });
            nextBoardList.back().curPlayBoard[(curBoard.zeroLoc[0]) * 3 + curBoard.zeroLoc[1]] = nextBoardList.back().curPlayBoard[(curBoard.zeroLoc[0]) * 3 + curBoard.zeroLoc[1] + 1];
            nextBoardList.back().curPlayBoard[(curBoard.zeroLoc[0]) * 3 + curBoard.zeroLoc[1] + 1] = 48;
            nextBoardList.back().diff = different(nextBoardList.back().curPlayBoard, targNumLoc);
        }
        if (curBoard.zeroLoc[0] < 2)
        {
            nextBoardList.push_back({ curBoard.curPlayBoard,{curBoard.zeroLoc[0] + 1,curBoard.zeroLoc[1]}, NULL, curBoard.route + 'D' });
            nextBoardList.back().curPlayBoard[(curBoard.zeroLoc[0]) * 3 + curBoard.zeroLoc[1]] = nextBoardList.back().curPlayBoard[(curBoard.zeroLoc[0] + 1) * 3 + curBoard.zeroLoc[1]];
            nextBoardList.back().curPlayBoard[(curBoard.zeroLoc[0] + 1) * 3 + curBoard.zeroLoc[1]] = 48;
            nextBoardList.back().diff = different(nextBoardList.back().curPlayBoard, targNumLoc);
        }if (curBoard.zeroLoc[1] > 0)
        {
            nextBoardList.push_back({ curBoard.curPlayBoard,{curBoard.zeroLoc[0],curBoard.zeroLoc[1] - 1}, NULL, curBoard.route + 'L' });
            nextBoardList.back().curPlayBoard[(curBoard.zeroLoc[0]) * 3 + curBoard.zeroLoc[1]] = nextBoardList.back().curPlayBoard[(curBoard.zeroLoc[0]) * 3 + curBoard.zeroLoc[1] - 1];
            nextBoardList.back().curPlayBoard[(curBoard.zeroLoc[0]) * 3 + curBoard.zeroLoc[1] - 1] = 48;
            nextBoardList.back().diff = different(nextBoardList.back().curPlayBoard, targNumLoc);
        }
        //curBoard.==NULL;//对上一个步骤的棋盘标注弃置
        for(int nextBoardIndex = 0; nextBoardIndex < nextBoardList.size(); nextBoardIndex++) //对每个nextBoard判断是否重复，计算与结果的差距
        {
            for (int histIndex = 0; histIndex < playBoardHist.size(); histIndex++)
                if (nextBoardList[nextBoardIndex].curPlayBoard == playBoardHist[histIndex])//是否与历史结果重复
                    goto skipCurBoard;//想退出双重循环只能用goto了,无视当前棋盘

            playBoardHist.push_back(nextBoardList[nextBoardIndex].curPlayBoard);//当前棋盘记录进历史
            nextBoardList[nextBoardIndex].diff = different(nextBoardList[nextBoardIndex].curPlayBoard, targNumLoc);
            playBoardQueue.push(nextBoardList[nextBoardIndex]);
        skipCurBoard:
            nextBoardIndex = nextBoardIndex;
        }
        nextBoardList.clear();
    }
    return ("Queue empty.Board can not be done.");
}

int main()
{
    //定义
    vector<vector<int>>playboard;
    playboard.push_back({ 1,3,6 });
    playboard.push_back({ 7,4,2 });
    playboard.push_back({ 0,5,8 });
    string route;
    vector<char> route1;
    dfsReturnKit dfsRtrn = dfs({ playboard }, {}, 0);
    for (int i = 0; i < dfsRtrn.route.size(); i++)
    {
        cout << (dfsRtrn.route[i] == 'U' ? "上," : (dfsRtrn.route[i] == 'R' ? "右," : (dfsRtrn.route[i] == 'D' ? "下," : (dfsRtrn.route[i] == 'L' ? "左," : (dfsRtrn.route[i] == '#' ? "成功!" : to_string(dfsRtrn.route[i]))))));
    }
    cout << endl;
    route = bfs({ playboard });
    for (int i = 0; i < route.size(); i++)
    {
        string ss(1, route[i]);
        cout << (route[i] == 'U' ? "上," : (route[i] == 'R' ? "右," : (route[i] == 'D' ? "下," : (route[i] == 'L' ? "左," : (route[i] == '#' ? "成功!" : ss)))));
    }
    cout << endl;
    route = aStar(playboard);
    for (int i = 0; i < route.size(); i++)
    {
        string ss(1,route[i]);
        cout << (route[i] == 'U' ? "上," : (route[i] == 'R' ? "右," : (route[i] == 'D' ? "下," : (route[i] == 'L' ? "左," : (route[i] == '#' ? "成功!" : ss)))));
    }
}

