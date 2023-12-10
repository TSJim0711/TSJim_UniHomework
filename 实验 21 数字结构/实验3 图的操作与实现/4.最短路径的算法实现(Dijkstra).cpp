//利用狄克斯特拉（Dijkstra）算法求下图中0结点到其它结点的最短路径，算法实现代码必须有注释。
//https://i.imgur.com/yLYlBwr.png
//or
//https://picst.sunbangyan.cn/2023/12/08/85d12090f67bb291159191e49de77e58.jpeg

#include <iostream>
using namespace std;

void SPAFtDijkstra(int *AdjGrf[], int strat)
{
	int start = 0;
	int dist[sizeof(AdjGrf[0]) - 2] = { 0 };
	int path[sizeof(AdjGrf[0]) - 2];
	memset(path, -1, sizeof(path));
	int leastDist[2] = { start,0 };
	bool pending[sizeof(AdjGrf[0]) - 2];//代表节点是否仍然悬空
	memset(pending, true, sizeof(pending));

	for (int done = 0; done < sizeof(AdjGrf[0]) - 1; done++)//循环图的节点数的次数
	{
		for (int i = 0; i < sizeof(AdjGrf[0]) - 1; i++)//寻找最小距离的线
		{
			if (pending[i] == true && path[i] != -1 && dist[i] < leastDist[1])//最小距离的线，前提是终点节点仍然悬空
			{
				leastDist[0] = i;//存入leastDist，如果还有更小距离，将被复写
				leastDist[1] = dist[i];
			}
		}
		if (leastDist[1] == INT_MAX)//是否找不到更小
			break;
		if (done == 0)//如果是一开始，就重置为起点
		{
			leastDist[0] = start;
			path[0] = start;
		}
		pending[leastDist[0]] = false;//节点不再悬空
		for (int i = 0; i < sizeof(AdjGrf[0]) - 1; i++)
		{
			if (AdjGrf[leastDist[0]][i] > 0)//如果此节点往对面节点有路
				if (path[i] == -1 || (path[i] > 0 && dist[i] > leastDist[1] + AdjGrf[leastDist[0]][i]))//如果对面节点未曾有路，或原有路更远
				{
					dist[i] = leastDist[1] + AdjGrf[leastDist[0]][i];//写为经此路的距离
					path[i] = leastDist[0];//写为经此路
				}
		}
		leastDist[1] = INT_MAX;//重置最小距离为最多，方便对比时 最多>较小>最小
	};
	cout << "Dist:{";//输出
	for (int i = 0; i < sizeof(AdjGrf[0])-2; i++)
		cout << dist[i] << ", ";
	cout << "\b\b}\nPath:{";
	for (int i = 0; i < sizeof(AdjGrf[0])-2; i++)
		cout << path[i] << ", ";
	cout << "\b\b}";
}

int main()
{
	int* AdjGrf[7];
	int AdjGrfNode0[7] = { 00,28,-1,-1,-1,10,-1 };
	int AdjGrfNode1[7] = { 28,00,16,-1,-1,-1,14 };
	int AdjGrfNode2[7] = { -1,16,00,12,-1,-1,-1 };
	int AdjGrfNode3[7] = { -1,-1,12,00,22,-1,18 };
	int AdjGrfNode4[7] = { -1,-1,-1,22,00,25,24 };
	int AdjGrfNode5[7] = { 10,-1,-1,-1,25,00,-1 };
	int AdjGrfNode6[7] = { -1,14,-1,18,24,-1,00 };
	AdjGrf[0] = AdjGrfNode0;
	AdjGrf[1] = AdjGrfNode1;
	AdjGrf[2] = AdjGrfNode2;
	AdjGrf[3] = AdjGrfNode3;
	AdjGrf[4] = AdjGrfNode4;
	AdjGrf[5] = AdjGrfNode5;
	AdjGrf[6] = AdjGrfNode6;
	SPAFtDijkstra(AdjGrf, 0);
}
