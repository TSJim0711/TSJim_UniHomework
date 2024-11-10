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
YTest=np.transpose(np.matrix(testSet['median_house_value'].values))

#特征缩放
sigma = np.std(X, axis=0)#X的每列标准差
mu=np.mean(X,axis=0)#X的每列平均
X=(X-mu)/sigma
sigma = np.std(XTest, axis=0)#X的每列标准差
mu=np.mean(XTest,axis=0)#X的每列平均
XTest=(XTest-mu)/sigma

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

def R_2(X_test,y_test,theta):

    y_pred=X_test*theta
    mu=np.mean(y_test,axis=0)
    SSE=np.sum(np.power(y_test-y_pred,2))
    SSR=np.sum(np.power(y_pred-mu,2))
    SST=SSR+SSE
    r_2=1-SSE/SST
    return r_2

print("Test Set TDXJ R2:")
print(R_2(XTest,YTest,theta))
print("Train Set TDXJ R2:")
print(R_2(X,Y,theta))
print("Test Set ZGFC R2:")
print(R_2(XTest,YTest,theta1))
print("Train Set ZGFC R2:")
print(R_2(X,Y,theta1))

def costfun(theta, X=X, Y=Y):
    h_x=X@theta
    inner=np.sum(np.power(h_x-Y,2))
    return inner/(2*Y.size)

print("TDXJ cost:")
print(costfun(theta))
print("ZGFC cost:")
print(costfun(theta1))

temp=data.copy()
corr=temp.corr()
score=corr['median_house_value'].sort_values()
print(score)

#打印图表：梯度下降的代价值变化
# Plot the array
plt.plot(J, marker='.')
plt.title('TDXJ iterative values')
# Label
plt.xlabel('Try Count')
plt.ylabel('Cost')

# Display plot
plt.show()
