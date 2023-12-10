//利用克鲁斯卡尔(Kruskal)算法求上图的最小生成树，算法实现代码必须有注释。//

#include <iostream>
using namespace std;

bool cycleFormed(int* grf[7], int last, int from, int target)
{
	bool cycle = false;
	if (from == target)//如果from找到target,意味存在回路，不能链接该线
		cycle = true;
	for (int col = 0; grf[from][col] != 0; col++)//列寻找，直到遇到0
		if (cycle != true && grf[from][col] > 0 && col != last)//如果当前列的当前单元格<0,意味有路，以该路对面节点为起点递归，为防止同一条路的两端来回循坏，禁止倒流
			cycle = cycleFormed(grf, from, col, target);
	for (int row = from + 1; row < sizeof(grf[0]) - 1; row++)//行寻找，从0开始
		if (cycle != true && grf[row][from] > 0 && row != last)//如果当前行的当前单元格<0,意味有路，以该路对面节点为起点递归，为防止在同一条路的两端来回循坏，禁止倒流
			cycle = cycleFormed(grf, from, row, target);
	return cycle;
}


void MSTFtKruskal(int* AdjGrf[7])
{
	int currentLowest = 0;
	int nodeOnLowRoute[2];
	int RouteCount, x, y;//routecount将储存有多少路，x和y是行和列，但有时会对调
	for (int x = 0; x < sizeof(AdjGrf[0]); x++)//铺平数组右上部分
		for (int y = x + 1; y < sizeof(AdjGrf[0]); y++)
			AdjGrf[x][y] = -1;//用-1铺平
	for (RouteCount = 0; currentLowest < INT_MAX; RouteCount++)//(currentLowest < INT_MAX)意味仍有节点未转化
	{
		currentLowest = INT_MAX;
		for (x = 0; x < sizeof(AdjGrf[0]) - 1; x++)//历遍数组，寻找当前最小weight的路
			for (y = 0; y < x; y++)
			{
				if (AdjGrf[x][y] <= currentLowest && AdjGrf[x][y] >= 0 && AdjGrf[y][x] == -1)//如果当前的路的weight是找到的中最小及未曾确定是最小的
				{
					currentLowest = AdjGrf[x][y];//记录信息
					nodeOnLowRoute[0] = x;
					nodeOnLowRoute[1] = y;
				}
			}
		if (currentLowest < INT_MAX)//当前的路的weight确定是找到的中最小
			AdjGrf[nodeOnLowRoute[1]][nodeOnLowRoute[0]] = RouteCount + 1;//在数组右上写，整个图的路的weight最小将是1，次小是2，如此类推
	} while (currentLowest < INT_MAX);//一旦找到当前最小，就重新开始寻找当前次小
	RouteCount--;//应对for判断为假时，依然RouteCount++
	for (y = 0; y < sizeof(AdjGrf[0]) - 1; y++)//铺平数组左下部分
		for (x = 0; AdjGrf[x][y] != 0; x++)
			AdjGrf[y][x] = -1;//用-1铺平
	for (int i = 1; i <= RouteCount; i++)
	{
		for (int x = 0; x < sizeof(AdjGrf[0]); x++)
			for (int y = x + 1; y < sizeof(AdjGrf[0]); y++)
				if (AdjGrf[min(x, y)][max(x, y)] == i)//信息源于数组左上部分，需AdjGrf[小][大]
					if (!cycleFormed(AdjGrf, NULL, x, y))//判断链接x,y节点会否产生回路
					{
						AdjGrf[max(x, y)][min(x, y)] = i;
						cout << "链接\t" << x << ", " << y << endl;
						x = y = sizeof(AdjGrf[0]);//使脱离两层for loop
					}
					else
					{
						cout << "断连 X\t" << x << ", " << y << endl;
						x = y = sizeof(AdjGrf[0]);//使脱离两层for loop
					}
	}
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
	MSTFtKruskal(AdjGrf);
	for (int i = 0; i < 7; i++)
		delete[] AdjGrf[i];
	delete[] AdjGrf;
}
