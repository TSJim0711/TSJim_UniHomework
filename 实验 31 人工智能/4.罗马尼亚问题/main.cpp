#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct dist
{
	string ASide;
	string BSide;
	int dist;
};

int straitDistToDes(string loc, vector<dist>straitDistToDesList)
{
	for (int straitDistToDesListIndex=0; straitDistToDesListIndex < straitDistToDesList.size(); straitDistToDesListIndex++)
		if (straitDistToDesList[straitDistToDesListIndex].ASide == loc)
			return straitDistToDesList[straitDistToDesListIndex].dist;
	return INT_MAX;
}

vector<string> astar(string from, string dest, vector<dist> distlist, vector<dist>distToDest)
{
	struct toBeVisit
	{
		vector<string>passed;
		int distTraveled = 0;
		int straitDistToDest;
		bool operator<(const toBeVisit& other) const {
			return (distTraveled + straitDistToDest) > (other.distTraveled + other.straitDistToDest); // 按照从小到大排序
		};
	};
	struct visited
	{
		string loc;
		int distTraveled;
	};

	priority_queue<toBeVisit>toBeVsitQueue;//历史棋盘，但是 目标差距+步数 从小到大排序
	toBeVisit curVisiting;
	vector<visited>visitHist;
	vector<string>tempPassed;

	toBeVsitQueue.push({ { from }, 0, INT_MAX });//把起始地址加入队列
	while (!toBeVsitQueue.empty()) 
	{
		curVisiting = toBeVsitQueue.top();//对当前找到的最优路径，取下一步
		toBeVsitQueue.pop();//遗忘当前最优路径
		visitHist.push_back({ curVisiting.passed.back(), curVisiting.distTraveled });//记入历史造访

		if (curVisiting.passed.back() == dest)//成功到达目的地
			return curVisiting.passed;

		for (int distListIndex = 0; distListIndex < distlist.size(); distListIndex++)
		{
			if (distlist[distListIndex].ASide == curVisiting.passed.back())
			{
				for (int visitHistIndex=0; (visitHistIndex < visitHist.size())&&!(distlist[distListIndex].BSide == visitHist[visitHistIndex].loc && visitHist[visitHistIndex].distTraveled < curVisiting.distTraveled + distlist[distListIndex].dist); visitHistIndex++)//不能在造访记录中发现有更短方法
				{
					if (visitHistIndex == visitHist.size() - 1)//未曾以更近距离造访下一个地点
					{
						tempPassed = curVisiting.passed;
						tempPassed.push_back(distlist[distListIndex].BSide);
						toBeVsitQueue.push({ tempPassed,curVisiting.distTraveled + distlist[distListIndex].dist,straitDistToDes(distlist[distListIndex].BSide,distToDest) });//把下一个地点推入造访队列
						tempPassed.clear();
					}

				}
			}
			if (distlist[distListIndex].BSide == curVisiting.passed.back())//distlist架构决定同一个地点可以在左右出现
			{
				for (int visitHistIndex=0; (visitHistIndex < visitHist.size()) && !(distlist[distListIndex].ASide == visitHist[visitHistIndex].loc && visitHist[visitHistIndex].distTraveled < curVisiting.distTraveled + distlist[distListIndex].dist); visitHistIndex++)//不能在造访记录中发现有更短方法
				{
					if (visitHistIndex == visitHist.size() - 1)//未曾以更近距离造访下一个地点
					{
						tempPassed = curVisiting.passed;
						tempPassed.push_back(distlist[distListIndex].ASide);
						toBeVsitQueue.push({ tempPassed,curVisiting.distTraveled + distlist[distListIndex].dist,straitDistToDes(distlist[distListIndex].ASide,distToDest) });//把下一个地点推入造访队列
						tempPassed.clear();
					}
				}
			}
		}
	}
}

int main()
{
	string from = "Zerind";
	string to = "Bucharest";
	vector<dist> distList;
	vector<dist> distToBucharestList;
	string start = "Zerind";
	string end = "Bucharest";

	distList.push_back({ "Oradea","Zerind",71 });
	distList.push_back({ "Oradea","Siblu",151 });
	distList.push_back({ "Zerind","Arad",75 });
	distList.push_back({ "Arad","Siblu",140 });
	distList.push_back({ "Arad","Timisora",118 });
	distList.push_back({ "Timisora","Lugoj",111 });
	distList.push_back({ "Lugoj","Mehadia",71 });
	distList.push_back({ "Mehadia","Dobreta",75 });
	distList.push_back({ "Dobreta","Cralova",120 });
	distList.push_back({ "Siblu","Rimnicu Vilcea",80 });
	distList.push_back({ "Rimnicu Vilcea","Cralova",148 });
	distList.push_back({ "Rimnicu Vilcea","Pltesti",97 });
	distList.push_back({ "Pltesti","Cralova",138 });
	distList.push_back({ "Pltesti","Bucharest",101 });
	distList.push_back({ "Siblu","Fagaras",99 });
	distList.push_back({ "Fagaras","Bucharest",211 });
	distList.push_back({ "Bucharest","Glurglu",90 });
	distList.push_back({ "Bucharest","Urziceni",85 });
	//后面站点无关


	distToBucharestList.push_back({ "Arad",{},366 });
	distToBucharestList.push_back({ "Bucharest",{},0 });
	distToBucharestList.push_back({ "Cralova",{},160 });
	distToBucharestList.push_back({ "Dobreta",{},242 });
	distToBucharestList.push_back({ "Eforie",{},161 });
	distToBucharestList.push_back({ "Fagaras",{},176 });
	distToBucharestList.push_back({ "Glurglu",{},77 });
	distToBucharestList.push_back({ "Hirsova",{},151 });
	distToBucharestList.push_back({ "Iasi",{},226 });
	distToBucharestList.push_back({ "Lugoj",{},244 });
	distToBucharestList.push_back({ "Mehadia",{},241 });
	distToBucharestList.push_back({ "Neamt",{},234 });
	distToBucharestList.push_back({ "Oradea",{},380 });
	distToBucharestList.push_back({ "Pltesti",{},10 });
	distToBucharestList.push_back({ "Rimnicu Vilcea",{},193 });
	distToBucharestList.push_back({ "Siblu",{},253 });
	distToBucharestList.push_back({ "Timisora",{},329 });
	distToBucharestList.push_back({ "Urzicent",{},80 });
	distToBucharestList.push_back({ "Vaslui",{},199 });
	distToBucharestList.push_back({ "Zerind",{},374 });

	vector<string> route = astar(from, to, distList, distToBucharestList);
	for (int i = 0; i < route.size(); i++)
		cout << route[i] << (i < route.size() - 1 ? "->" : "");
}
