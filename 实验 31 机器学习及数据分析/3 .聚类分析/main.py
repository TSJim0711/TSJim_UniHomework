from math import dist
import numpy as np
import pandas as pd
from itertools import permutations #这是验证时候用到的小工具,产生1，2，3排列
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.animation import FuncAnimation
import matplotlib.colors as mcolors

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
dist=[]#装载all排列方式的距离
for arr in permutations(range(3)):
   dist.append(np.linalg.norm(centroids[0]-centroidsAnsw[arr[0]])+np.linalg.norm(centroids[1]-centroidsAnsw[arr[1]])+np.linalg.norm(centroids[2]-centroidsAnsw[arr[2]]))#norm()计算距离root(A^2+B^2)
#print("训练质心与正确质心的总距离：")
print("Distance between calculated centroi & given centroi:")   
print(min(dist))

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
# Create a 3D scatter plot       
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Plot the points
scatter = ax.scatter(x, y, z, c=labels, cmap='viridis', s=50)  # Increase size of points

# Label each point with its corresponding w value
for i in range(len(x)):
    ax.text(x[i], y[i], z[i], f'{int(labels[i])}', size=8, color='white', zorder=8, ha='center', va='center')

# Show the plot
plt.show()