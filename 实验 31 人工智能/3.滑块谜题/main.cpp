#include <iostream>
#include <vector>
#include <string>
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
        cout << "找到! ";
        rtrnKit.route.push_back('#');//已经完成，添加完成符
        return rtrnKit;
    }
    else
    {
        depth++;
        //避免LOOP
        for (int i = 0; i < playboardHistory.size() - 1/*不对最后一个(目前)判断*/; i++)
            if (playboardHistory.back() == playboardHistory[i]||depth>50)//与历史重复，，代表此路不通
            {
                if(depth>50)
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
int main()
{
    //定义
    vector<vector<int>>playboard;
    playboard.push_back({1,2,3});
    playboard.push_back({4,5,6});
    playboard.push_back({7,0,8});
    cout<<"START ";
    //dfs search
    vector<char> route;
    dfsReturnKit dfsRtrn=dfs({playboard}, route,0);
    for (int i = 0; i < dfsRtrn.route.size(); i++)
    {
        cout << (dfsRtrn.route[i]=='U' ?"上,": (dfsRtrn.route[i] == 'R' ? "右," : (dfsRtrn.route[i] == 'D' ? "下," : (dfsRtrn.route[i] == 'L' ? "左," : (dfsRtrn.route[i] == '#' ? "成功!" : to_string(dfsRtrn.route[i]))))));
    }

}