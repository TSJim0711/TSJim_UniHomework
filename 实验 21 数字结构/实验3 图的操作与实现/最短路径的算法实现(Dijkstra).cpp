#include <iostream>
#include <algorithm> 
using namespace std;


void SPAFtDijkstra(int *AdjGrf[], int strat)
{
	int start = 0;
	int dist[sizeof(AdjGrf[0]) - 2] = { 0 };
	int path[sizeof(AdjGrf[0]) - 2];
	memset(path, -1, sizeof(path));
	int leastDist[2] = { start,0 };
	bool pending[sizeof(AdjGrf[0]) - 2];
	memset(pending, true, sizeof(pending));

	for (int done = 0; done < sizeof(AdjGrf[0]) - 1; done++)
	{
		for (int i = 0; i < sizeof(AdjGrf[0]) - 1; i++)//find lowest path
		{
			if (pending[i] == true && path[i] != -1 && dist[i] < leastDist[1])
			{
				leastDist[0] = i;
				leastDist[1] = dist[i];
			}
		}
		if (leastDist[1] == INT_MAX)
			break;
		if (done == 0)
		{
			leastDist[0] = start;
			path[0] = start;
		}
		pending[leastDist[0]] = false;
		for (int i = 0; i < sizeof(AdjGrf[0]) - 1; i++)
		{
			if (AdjGrf[leastDist[0]][i] > 0)
				if (path[i] == -1 || (path[i] > 0 && dist[i] > leastDist[1] + AdjGrf[leastDist[0]][i]))
				{
					dist[i] = leastDist[1] + AdjGrf[leastDist[0]][i];
					path[i] = leastDist[0];
				}
		}
		leastDist[1] = INT_MAX;
	}
	cout << "Dist:{";
	for (int i = 0; i < sizeof(AdjGrf[0])-2; i++)
		cout << dist[i] << " ";
	cout << "}\nPath:{";
	for (int i = 0; i < sizeof(AdjGrf[0])-2; i++)
		cout << path[i] << " ";
	cout << "}";
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
