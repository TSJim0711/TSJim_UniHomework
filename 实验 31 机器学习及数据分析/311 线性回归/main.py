import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split

data = pd.read_csv("housing.csv")
ocean_proximity_map={"INLAND":0,"<1H OCEAN":1,"NEAR OCEAN ":2,"NEAR BAY":3,"ISLAND":4}
data['ocean_proximity']=data['ocean_proximity'].map(ocean_proximity_map)#ocean_proximity hot-one encode
data=data.dropna() #drop column with empty cell

dataEncoded=pd.get_dummies(data)
trainSet, testSet=train_test_split(dataEncoded, test_size=0.3, random_state=42)



X=np.matrix(trainSet.drop(columns=['median_house_value']).values) #convert to matrix
Y=np.transpose(np.matrix(trainSet['median_house_value'].values))#rotate Y from 1*n to n*1
XTest=np.matrix(testSet.drop(columns=['median_house_value']).values)
YTest=np.matrix(testSet['median_house_value'].values)

print("X:",X)
print("Y:",XTest)

#特征缩放
sigma = np.std(X, axis=0)#X的每列标准差
mu=np.mean(X,axis=0)#X的每列平均
X=(X-mu)/sigma

#引入偏置项
X = np.c_[(np.ones(X.shape[0]), X)]
XTest = np.c_[(np.ones(XTest.shape[0]), XTest)]

#梯度下降参数
theta=np.zeros((10, 1))
theta1=np.zeros((10, 1))
iteration=2000#迭代2000x
J=np.zeros(iteration)#迭代代价
learnRate=0.01

for i in range(iteration):#梯度下降
    h_x=X@theta
    inner=np.sum(np.power(h_x-Y,2))
    J[i]=inner/(2*Y.size)
    theta=theta-(learnRate/Y.size)*(X.T@(X@theta-Y))

theta1=np.linalg.inv(X.T@X)@X.T@Y

#打印图表
# Plot the array
plt.plot(J, marker='.')

# Add labels and title
plt.xlabel('Index')
plt.ylabel('Value')
plt.title('Line Chart of 1x20 Array')

# Display the plot
plt.show()
