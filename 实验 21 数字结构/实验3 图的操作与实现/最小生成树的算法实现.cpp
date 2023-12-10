//利用克鲁斯卡尔(Kruskal)算法求上图的最小生成树，算法实现代码必须有注释。//

#include <iostream>
#include <vector>
using namespace std;

void fun(int www)
{
	/*int* AdjGrf[7];
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
	AdjGrf[6] = AdjGrfNode6;*/
}

bool cycleFormed(int *grf[7], int last, int from, int target)
{
	bool cycle = false;
	if (from == target)
		cycle = true;
	for (int col = 0; grf[from][col] != 0; col++)
		if (cycle != true && grf[from][col] > 0 && col!=last)
			cycle = cycleFormed(grf, from, col, target);
	for (int row = from + 1; row < sizeof(grf[0]) - 1; row++)
		if (cycle != true && grf[row][from] > 0 && row != last)
			cycle = cycleFormed(grf, from, row, target);
	return cycle;
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

	bool underRoutePending = false;
	int currentLowest = 0;
	int nodeOnLowRoute[2];
	int RouteCount, x,y, current_y;
	for (int x = 0; x < sizeof(AdjGrf[0]); x++)
		for (int y = x + 1; y < sizeof(AdjGrf[0]); y++)
			AdjGrf[x][y] = -1;
	for(RouteCount =0 ; currentLowest < INT_MAX;RouteCount++)
	{
		currentLowest = INT_MAX;
		for (x = 0; x < sizeof(AdjGrf[0]) -1; x++)//历遍数组，寻找当前最小weight
			for (y = 0; y < x; y++)
			{
				if (AdjGrf[x][y] <= currentLowest && AdjGrf[x][y] >= 0 && AdjGrf[y][x] == -1)//如果当前node是找到的中最小及未曾确定是最小的
				{
					currentLowest = AdjGrf[x][y];
					nodeOnLowRoute[0] = x;
					nodeOnLowRoute[1] = y;
				}
			}
		if(currentLowest < INT_MAX)
			AdjGrf[nodeOnLowRoute[1]][nodeOnLowRoute[0]] = RouteCount +1;
	} while (currentLowest < INT_MAX);
	RouteCount--;//应对for判断为假时，依然RouteCount++
	for ( y = 0 ; y < sizeof(AdjGrf[0]) -1 ; y++)
		for ( x = 0; AdjGrf[x][y]!=0; x++)
			AdjGrf[y][x] = -1;
	for (int i = 1; i <= RouteCount; i++)
	{
		for (int x = 0; x < sizeof(AdjGrf[0]); x++)
			for (int y = x + 1; y < sizeof(AdjGrf[0]); y++)
				if (AdjGrf[min(x, y)][max(x, y)] == i)
					if(!cycleFormed(AdjGrf, NULL, x,y))
					{
						AdjGrf[max(x, y)][min(x, y)] = i;
						cout <<"链接\t" << x << ", " << y << endl;
						x = y = sizeof(AdjGrf[0]);//使脱离两层for loop
					}
					else
					{
						cout << "断连 X\t" << x << ", " << y << endl;
						x = y = sizeof(AdjGrf[0]);//使脱离两层for loop
					}
	}
	cin >> RouteCount;
}
