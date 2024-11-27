#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct dfsReturnKit
{
    vector<vector<vector<int>>>playboardHistory;
    vector<char>route;
};

struct treeNode
{
    string curPlayBoard;
    int zeroLoc[2];
    string route;
};

vector<vector<int>>playboardTarg = { {1,2,3},{4,0,5},{6,7,8} };

dfsReturnKit dfs(vector<vector<vector<int>>>playboardHistory, vector<char> route, int depth)
{
    dfsReturnKit rtrnKit = { playboardHistory,route };
    dfsReturnKit rtrnRecv = rtrnKit;//赋值没有任何意义,主要避免rtrnRecv.route.back()虚空请求
    //最后一步，找到了？
    if (playboardHistory.back() == playboardTarg)
    {
        cout << "找到! ";
        rtrnKit.route.push_back('#');//已经完成，添加完成符
        return rtrnKit;
    }
    else
    {
        depth++;
        //避免LOOP
        for (int i = 0; i < playboardHistory.size() - 1/*不对最后一个(目前)判断*/; i++)
            if (playboardHistory.back() == playboardHistory[i]||depth>20)//与历史重复，，代表此路不通
            {
                if(depth>20)
                    cout << "过深! ";
                else
                    cout << "LOOP! ";
                return rtrnKit;
            }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (playboardHistory.back()[i][j] == 0)//找到0(空格)的位置
                {
                    if (i > 0)//going up
                    {
                        cout << "加入上 ";
                        playboardHistory.push_back(playboardHistory.back());
                        playboardHistory.back()[i][j] = playboardHistory.back()[i - 1][j];//与上面格交换
                        playboardHistory.back()[i - 1][j] = 0;
                        route.push_back('U');//插入路径‘上’
                        rtrnRecv = dfs(playboardHistory, route, depth);//递归
                        if (rtrnRecv.route.back() != '#')//没有找到结果，删除刚才插入的路径
                        {
                            cout << "删除上 ";

                            route.pop_back();
                        }
                        playboardHistory.pop_back();
                    }
                    if (j < 2 && !(rtrnRecv.route.back() == '#'))//going right 同时未曾成功找到路线
                    {
                        cout << "加入R ";
                        playboardHistory.push_back(playboardHistory.back());
                        playboardHistory.back()[i][j] = playboardHistory.back()[i][j + 1];//与右面格交换
                        playboardHistory.back()[i][j+1] = 0;
                        route.push_back('R');//插入路径‘右’
                        rtrnRecv = dfs(playboardHistory, route, depth);//递归
                        if (rtrnRecv.route.back() != '#')//没有找到结果，删除刚才插入的路径
                        {
                            cout << "删除R ";

                            route.pop_back();
                        }
                        playboardHistory.pop_back();
                    }
                    if (i < 2 && !(rtrnRecv.route.back() == '#'))//down
                    {
                        cout << "加入下 ";
                        playboardHistory.push_back(playboardHistory.back());
                        playboardHistory.back()[i][j] = playboardHistory.back()[i + 1][j];//交换
                        playboardHistory.back()[i + 1][j] = 0;
                        route.push_back('D');//插入路径
                        rtrnRecv = dfs(playboardHistory, route, depth);//递归
                        if (rtrnRecv.route.back() != '#')//没有找到结果，删除刚才插入的路径
                        {
                            cout << "删除下 ";

                            route.pop_back();
                        }
                        playboardHistory.pop_back();
                    }
                    if (j > 0 && !(rtrnRecv.route.back() == '#'))//left
                    {
                        cout << "加入L ";
                        playboardHistory.push_back(playboardHistory.back());
                        playboardHistory.back()[i][j] = playboardHistory.back()[i][j - 1];//交换
                        playboardHistory.back()[i][j-1] = 0;
                        route.push_back('L');//插入路径
                        rtrnRecv = dfs(playboardHistory, route, depth);//递归
                        if (rtrnRecv.route.back() != '#')//没有找到结果，删除刚才插入的路径
                        {
                            cout << "删除L ";

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

    vector <treeNode> procList = { {playBoard,{},""}};
    vector <treeNode> procListTemp;
    string playBrdtemp;
    vector<string>playBoardHist;
    for (int i = 0; i < playBoard.size(); i++) {//寻找 0
        if (playBoard[i]=='0')//找到0(空格)的位置,记录
        {
            procList.back().zeroLoc[0] = i / 3;
            procList.back().zeroLoc[1] = i % 3;
        }
    }
    for (int depth = 0; depth < 50; depth++)
    {
        cout << "深度：" << depth << endl;
        for (int x = 0; x < procList.size(); x++)//根据上回的行动栈逐一处理
        {
            for (int histIndex = 0; histIndex < playBoardHist.size(); histIndex++)
                if (procList[x].curPlayBoard == playBoardHist[histIndex])//是否与历史结果重复
                {
                    goto skipCurBoard;//想退出双重循环只能用goto了,无视当前棋盘
                }
            playBoardHist.push_back(procList[x].curPlayBoard);//新棋盘状态，推入历史

            if (procList[x].curPlayBoard == playBoardTargStr)
                return procList[x].route;//如果是结果，返回路径。
            if (procList[x].zeroLoc[0] > 0)//going up
            {
                procListTemp.push_back({ procList[x].curPlayBoard , {procList[x].zeroLoc[0] - 1,procList[x].zeroLoc[1]}, procList[x].route + 'U' });//把下一步棋盘和该路径推入临时行动栈
                procListTemp.back().curPlayBoard[(procList[x].zeroLoc[0]) * 3 + procList[x].zeroLoc[1]] = procListTemp.back().curPlayBoard[(procList[x].zeroLoc[0] - 1) * 3 + procList[x].zeroLoc[1]];//与上面格交换
                procListTemp.back().curPlayBoard[(procList[x].zeroLoc[0] - 1) * 3 + procList[x].zeroLoc[1]] = 48;
            }
            if (procList[x].zeroLoc[1] < 2)
            {
                procListTemp.push_back({ procList[x].curPlayBoard,{procList[x].zeroLoc[0],procList[x].zeroLoc[1] + 1}, procList[x].route + 'R' });
                procListTemp.back().curPlayBoard[(procList[x].zeroLoc[0]) * 3 +procList[x].zeroLoc[1]] = procListTemp.back().curPlayBoard[(procList[x].zeroLoc[0]) * 3 +procList[x].zeroLoc[1] + 1];
                procListTemp.back().curPlayBoard[(procList[x].zeroLoc[0]) * 3 +procList[x].zeroLoc[1] + 1] = 48;
            }
            if (procList[x].zeroLoc[0] < 2)
            {
                procListTemp.push_back({ procList[x].curPlayBoard,{procList[x].zeroLoc[0] + 1,procList[x].zeroLoc[1]}, procList[x].route + 'D' });
                procListTemp.back().curPlayBoard[(procList[x].zeroLoc[0]) * 3 +procList[x].zeroLoc[1]] = procListTemp.back().curPlayBoard[(procList[x].zeroLoc[0]+1) * 3 +procList[x].zeroLoc[1]];
                procListTemp.back().curPlayBoard[(procList[x].zeroLoc[0]+1) * 3 +procList[x].zeroLoc[1]] = 48;
            }if (procList[x].zeroLoc[1] > 0)
            {
                procListTemp.push_back({ procList[x].curPlayBoard,{procList[x].zeroLoc[0],procList[x].zeroLoc[1] - 1}, procList[x].route + 'L' });
                procListTemp.back().curPlayBoard[(procList[x].zeroLoc[0]) * 3 +procList[x].zeroLoc[1]] = procListTemp.back().curPlayBoard[(procList[x].zeroLoc[0]) * 3 +procList[x].zeroLoc[1] - 1];
                procListTemp.back().curPlayBoard[(procList[x].zeroLoc[0]) * 3 +procList[x].zeroLoc[1] - 1] = 48;
            }
        skipCurBoard:
            x = x;
        }
        procList = procListTemp;//把所有可能的步骤推入行动栈
        procListTemp.clear();
    }
}

    int main()
    {
        //定义
        vector<vector<int>>playboard;
        playboard.push_back({ 2,8,3 });
        playboard.push_back({ 1,6,4 });
        playboard.push_back({ 7,0,5 });
        cout << "START ";
        //dfs search
        string route;
        vector<char> route1;
        //dfsReturnKit dfsRtrn=dfs({playboard}, route1,0);
        route = bfs(playboard);
        for (int i = 0; i < route.size(); i++)
        {
            cout << (route[i] == 'U' ? "上," : (route[i] == 'R' ? "右," : (route[i] == 'D' ? "下," : (route[i] == 'L' ? "左," : (route[i] == '#' ? "成功!" : to_string(route[i]))))));
        }
    }

