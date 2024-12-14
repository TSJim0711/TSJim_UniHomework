import array
from math import dist, nan
import plotly.graph_objects as go
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

data=pd.read_csv("seeds_dataset.txt", delimiter='\t', header=None, on_bad_lines='skip', skipinitialspace=True )
dataArray=data.to_numpy()
answerArray=dataArray[:,-1]#验证集
dataArray=dataArray[:,:-1]#训练集

centroids=dataArray[np.random.choice(dataArray.shape[0], 3, replace=False)] #随机3个 7参数的质心,免得取值太离谱无人问津，因为我曾经用centroids = np.random.uniform(3.5, 5, (3, 7))
nodeOfCentroids = [[],[],[]]#3d数组，装载质心旗下数据点的数据
centroidsAnsw = np.zeros((3, 7), dtype=int)#随机3个 装载计算的出的正确质心位置
nodeOfCentroidsAnsw = [[],[],[]]#3d数组,装载计算的出的正确质心位置
temp=[]

#迭代次数和收敛条件
maxIterations = 10
for iteration in range(maxIterations):
    #每个数据点找到最近的质心
    for nodeIndex in range(np.size(dataArray,axis=0)):#每个数据点(data有多少列行)的距离
        centroidsADist=np.sum(abs(dataArray[nodeIndex] - centroids[0]))
        centroidsBDist=np.sum(abs(dataArray[nodeIndex] - centroids[1]))
        centroidsCDist=np.sum(abs(dataArray[nodeIndex] - centroids[2]))
        #判断数据点最近的质心，推入那个质心的计算栈
        if centroidsADist<centroidsBDist and centroidsADist<centroidsCDist:
            nodeOfCentroids[0].append(dataArray[nodeIndex])
        elif centroidsBDist<centroidsCDist:
            nodeOfCentroids[1].append(dataArray[nodeIndex])
        else:
            nodeOfCentroids[2].append(dataArray[nodeIndex])
    centroidsHist=centroids.copy();
    #根据质心旗下数据链平均值，移动质心    temp=np.mean(nodeOfCentroids[0],axis=0)
    if nodeOfCentroids[0]!=[]:
        centroids[0]=np.mean(nodeOfCentroids[0],axis=0)
    if nodeOfCentroids[1]!=[]: 
        centroids[1]=np.mean(nodeOfCentroids[1],axis=0)
    if nodeOfCentroids[2]!=[]:
        centroids[2]=np.mean(nodeOfCentroids[2],axis=0)
    if (centroids==centroidsHist).all():#如果此次质心没有移动，就到此为止
        break
    nodeOfCentroids = [[],[],[]]#质心的计算栈清零

#验证
for nodeIndex in range(np.size(dataArray,axis=0)):#每个数据点(data有多少列行)的距离
    #与实际质点的距离
    for nodeIndex in range(np.size(dataArray,axis=0)):
        if answerArray[nodeIndex]==1:
            nodeOfCentroids[0].append(dataArray[nodeIndex])
        elif answerArray[nodeIndex]==2:
            nodeOfCentroids[1].append(dataArray[nodeIndex])
        elif answerArray[nodeIndex]==3:
            nodeOfCentroids[2].append(dataArray[nodeIndex])
centroidsAnsw[0]=np.array(np.mean(nodeOfCentroids[0],axis=0))
centroidsAnsw[1]=np.array(np.mean(nodeOfCentroids[1],axis=0))
centroidsAnsw[2]=np.array(np.mean(nodeOfCentroids[2],axis=0))

labels=[]
x = dataArray[:, 0]
y = dataArray[:, 1]
z = dataArray[:, 2]
for nodeIndex in range(np.size(dataArray,axis=0)):#每个数据点(data有多少列行)的距离
    centroidsADist=np.sum(abs(dataArray[nodeIndex] - centroids[0]))
    centroidsBDist=np.sum(abs(dataArray[nodeIndex] - centroids[1]))
    centroidsCDist=np.sum(abs(dataArray[nodeIndex] - centroids[2]))
    if centroidsADist<centroidsBDist and centroidsADist<centroidsCDist:
        labels.append(1)
    elif centroidsBDist<centroidsCDist:
        labels.append(2)
    else:
        labels.append(3)

# Create a scatter plot     
fig = go.Figure()
unicode = b'\\u805a\\u7c7b '

# dot add
fig.add_trace(go.Scatter3d(
    x=x, y=y, z=z,
    mode='markers',
    name=("K-Means "+unicode.decode("unicode_escape")),
    marker=dict(
        size=8,
        color=labels,
        colorscale='Viridis',
        opacity=0.8
    ),
    textposition="top center"
))

#计算每个数据点对每个数据点的距离
distList = np.full((dataArray.shape[0],dataArray.shape[0]),nan)#空数组， 大小： dataArray行*dataArray行
for x in range(0,dataArray.shape[0]):
    for y in range(x+1,dataArray.shape[0]):
        distList[x,y]=sum(abs(dataArray[x]-dataArray[y]))#数据点对每个数据点的距离，*10！

#存储每个点的意思(由那几个点合并而来?) 
represent=[[i] for i in range(dataArray.shape[0])]#初始化为第一列由0开始排列,为每一个数据点添加独立标签
    
mrgAct = np.dtype([
    ('mergeTo','O'),
    ('dist', float)])
mergeHist = np.zeros(0,dtype=mrgAct)#储存合并历史 格式为{{合并自},{合并自},{合并距离}}

minDistToObj=[]#临时存储当下的合并后离其他点的最小距离
#合并数据点
while distList.shape[0]>1:#重复合并直到只有一个数据点
    minDist = np.nanmin(distList)#找到距离最小的一对数据点
    minDistLoc = np.where(distList ==minDist)
    minDistLoc =[int(minDistLoc[0]),int(minDistLoc[1])]
    minDistLoc.sort()
    #建立新数据点，是距离最小的一对数据点合并而来的    
    
   #把合并后两个点中 距离其他同个点最近的距离推入distList
    new = np.full((distList.shape[0],1), nan)
    distList=np.hstack((distList,new))#添加空列
    new = np.full((1, distList.shape[1]), nan)
    distList=np.vstack((distList,new))#添加空行，避免行列不平衡
    for obj in range(0,distList.shape[0]-1):
        distList[obj][-1]=((distList[obj,minDistLoc[0]] if obj<minDistLoc[0] else distList[minDistLoc[0],obj])*(len(represent[minDistLoc[0]]))+(distList[obj,minDistLoc[1]] if obj<minDistLoc[1] else distList[minDistLoc[1],obj])*(len(represent[minDistLoc[1]])))/(len(represent[minDistLoc[0]])+len(represent[minDistLoc[1]]))#取两个点的平均值，根据旗下元数据点分配权重，obj<minDistLoc避免取到nan 

    mergeAct=(represent[minDistLoc[0]]+represent[minDistLoc[1]],distList[minDistLoc[0]][minDistLoc[1]])#好抽象啊！ 为什么numpy.int32 和常规int不相容？？？？
    mergeHist=np.append(mergeHist,np.array([mergeAct],dtype=mrgAct))#记录合并历史
    represent.append(represent[minDistLoc[0]]+represent[minDistLoc[1]])#合并后更新代表的数据点
    represent.pop(minDistLoc[1])#删除原有的数据点
    represent.pop(minDistLoc[0])

    distList=np.delete(distList,minDistLoc[1],axis=0)#移除合并数据点的原行原列,由大到小
    distList=np.delete(distList,minDistLoc[1],axis=1)
    distList=np.delete(distList,minDistLoc[0],axis=0)
    distList=np.delete(distList,minDistLoc[0],axis=1)

   
sectors=0#当前分出多少个类？ 目标3
#解读mergeHist 
splitList = [nan]*dataArray.shape[0]#添加空行,储存分类，与dataArray行对应
for mergeHistIdx in range (mergeHist.shape[0]-1,0,-1):#由上而下读mergeHist
    if(sectors>3):
        break
    sectors=sectors+1#分出新类
    for mergeWithIdx in range (0,len(mergeHist[mergeHistIdx]['mergeTo'])):
        splitList[mergeHist[mergeHistIdx]['mergeTo'][mergeWithIdx]]=mergeHistIdx#为每个数据点标记当前类

x = dataArray[:, 0]
y = dataArray[:, 1]
z = dataArray[:, 2]

fig.add_trace(go.Scatter3d(
    x=x, y=y, z=z,
    mode='markers',
    name=("Hierarchical "+unicode.decode("unicode_escape")),
    marker=dict(
        size=8,
        color=splitList,
        colorscale='Viridis',
        opacity=0.8
    ),
))
# graph layout
fig.update_layout(
    scene=dict(
        camera=dict(
            eye=dict(x=1, y=-1, z=0.1) 
        )
    ),
)
fig.write_html("clustering.html")
#graph display
fig.show()