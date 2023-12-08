//以0结点为起点实现以下图的深度优先和广度优先遍历算法
//https://i.imgur.com/yLYlBwr.png
//or
//https://picst.sunbangyan.cn/2023/12/08/85d12090f67bb291159191e49de77e58.jpeg

#include <iostream>

using namespace std;

typedef struct ANode
{
    int adjvex;
    struct ANode* nextarc;
    int weight;
}ArcNode;

typedef struct Vnode
{
    int data;
    ArcNode* firstarc;
}VNode;

typedef struct AdjGraph
{
    VNode adjlist[20];//邻接表，最大20
    int n, e;////图中顶点数n和边数e
}AdjGraph;

typedef struct searchStack
{
    int data;
    searchStack* postNode;//为了方便先进后出结构
}searchStack;

AdjGraph* createAdjGraph(int* graphRq)
{
    AdjGraph* mainTrunk = (AdjGraph*)malloc(sizeof(AdjGraph));
    VNode* pointerA = NULL, * pointerB = NULL;
    VNode* VNodeTemp;
    ANode* ANodeTemp, * ANodePointer;
    mainTrunk->e = mainTrunk->n = 0;
    bool doubleInitialize = false;
    int emptySample = mainTrunk->adjlist[1].data;
    int loopFlag = -1;//loop flag 相当于do-while loop 的计数器
    for (int i = 0; i <= sizeof(graphRq); i++)
    {
        do
        {
            loopFlag++;
            if (mainTrunk->adjlist[loopFlag].data == graphRq[i * 3])
                pointerA = &mainTrunk->adjlist[loopFlag];
            if (mainTrunk->adjlist[loopFlag].data == graphRq[i * 3 + 1])
                pointerB = &mainTrunk->adjlist[loopFlag];
        } while (mainTrunk->adjlist[loopFlag].data != emptySample && (pointerA == NULL || pointerB == NULL));//寻找节点对应的VNode，没有就跳出。这里的data很吊诡，不是NULL,0,我不知道如何判断，只能透过emptySample
        //        if(pointerB == NULL && pointerB == pointerA)
        //            pointerB = &mainTrunk->adjlist[loopFlag+1];
        ANodeTemp = (ANode*)malloc(sizeof(ANode));
        ANodeTemp->adjvex = graphRq[i * 3 + 1];//先准备好要插入的新的node的内容
        ANodeTemp->nextarc = NULL;
        ANodeTemp->weight = graphRq[i * 3 + 2];
        if (pointerA == NULL)//代表do-while loop中没有找到对应的开始顶点
        {
            pointerA = &mainTrunk->adjlist[loopFlag];//赋予新行作为开始顶点
            pointerA->data = graphRq[i * 3];
            pointerA->firstarc = ANodeTemp;//插入新的node的内容
            mainTrunk->n++;//图中顶点数n++和边数e++
            mainTrunk->e++;
            doubleInitialize = true;//设潜在的双重初始化为真
        }
        else//代表do-while loop中找到对应的开始顶点
        {
            ANodePointer = pointerA->firstarc;
            while (ANodePointer->nextarc != NULL)//找到对应顶点的nextarc链的尾
                ANodePointer = ANodePointer->nextarc;
            ANodePointer->nextarc = ANodeTemp;//插入的新的node的内容
            mainTrunk->e++;//图中边数e++
        }
        //----A及B结构相同，注释略----//
        ANodeTemp = (ANode*)malloc(sizeof(ANode));
        ANodeTemp->adjvex = graphRq[i * 3];
        ANodeTemp->nextarc = NULL;
        ANodeTemp->weight = graphRq[i * 3 + 2];
        if (pointerB == NULL)
        {
            pointerB = &mainTrunk->adjlist[loopFlag + (doubleInitialize ? 1 : 0)];//如果潜在的双重初始化为真，则代表需要以loopFlag+1行作为开始顶点
            pointerB->data = graphRq[i * 3 + 1];
            pointerB->firstarc = ANodeTemp;
            mainTrunk->n++;//图中顶点数n++和边数e++
            mainTrunk->e++;
        }
        else
        {
            ANodePointer = pointerB->firstarc;
            while (ANodePointer->nextarc != NULL)
                ANodePointer = ANodePointer->nextarc;
            ANodePointer->nextarc = ANodeTemp;
            mainTrunk->e++;
        }
        pointerA = pointerB = NULL;
        doubleInitialize = false;
        loopFlag = -1;
    }
    return mainTrunk;
}

void depthSearchAdjGraph(AdjGraph* grf)
{
    VNode *currentNode = &grf->adjlist[0];
    ANode *nextNode;
    searchStack *searchStkRoot = NULL, * searchStkNode;
    int spottedCount = 0, i;//记录已发现多少节点，存粹空间换时间
    bool* visited = new bool[grf->n];//设立发现节点表，所有色味false，即未发现
    memset(visited, 0, sizeof(bool) * grf->n);
    while(spottedCount < grf->n )
    {
        cout << currentNode->data;
        visited[currentNode->data] = true;//汇报当前节点已发现
        spottedCount++;
        nextNode = currentNode->firstarc;
        if (spottedCount < grf->n)//代表已历遍图，可以结束。
            return;
        rollBack:
        while ((nextNode != NULL && visited[nextNode->adjvex]))
        {
            if (nextNode->nextarc != NULL)
                nextNode = nextNode->nextarc;
        }
        if(nextNode != NULL)
        {
            searchStkNode = (searchStack*)malloc(sizeof(searchStack));
            searchStkNode->data = currentNode->data;//可以通行，就留下目前的节点信息
            searchStkNode->postNode = searchStkRoot;
            searchStkRoot = searchStkNode;
            for (i = 0; grf->adjlist[i].data != nextNode->adjvex;i++)
                cout;
            currentNode = &grf->adjlist[i];
        }
        else //代表无路可走，需要回退。
        {
            searchStkNode = searchStkRoot;
            searchStkRoot = searchStkRoot->postNode;
            free(searchStkNode);
            nextNode = grf->adjlist[searchStkRoot->data].firstarc;//回退一个节点
            goto rollBack;//回退一个节点进行判断
        }
        cout << ", ";
    }
}

void destroyAdjGraph(AdjGraph* grf)
{
    ANode* pointer2Del, * pointer2Handle = NULL;
    for (int i = 0; i < grf->n; i++)
    {
        do
        {
            pointer2Del = grf->adjlist[i].firstarc;
            while (pointer2Del->nextarc != NULL)
            {
                if (pointer2Del->nextarc->nextarc == NULL)//在删除节点的前一个节点放个旗
                    pointer2Handle = pointer2Del;
                pointer2Del = pointer2Del->nextarc;//指向删除节点
            }
            free(pointer2Del);//删除节点
            if (pointer2Handle != NULL)
                pointer2Handle->nextarc = NULL;//把删除节点的前一个节点的nextarc = NULL,方便下一次while loop中判断
            else
                grf->adjlist[i].firstarc = NULL;//如果pointer2Handle == NULL,此时adjlist[i]已清空,所以赋adjlist[i]值NULL,方便 do-while loop 判断
            pointer2Handle = NULL;
        } while (grf->adjlist[i].firstarc != NULL);
    }
    free(grf);
}

int main()
{
    int graphRequest[9][3] = { 0,1,28,6,4,24,1,2,16,2,3,12,3,4,22,4,5,25,5,0,10,1,6,14,6,3,18 }; //{线路节点，线路节点，线路权重}
    AdjGraph* grf;
    grf = createAdjGraph(*graphRequest);
    depthSearchAdjGraph(grf);
    destroyAdjGraph(grf);
}
