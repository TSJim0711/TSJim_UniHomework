import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split

data=pd.read_csv("bezdekIris.data")
is_targ_map={"Iris-setosa":0,"Iris-virginica":1,"Iris-versicolor":0}#convert data to Is Iris-virginica? true/false
data.iloc[:,-1]=data.iloc[:,-1].map(is_targ_map)#ocean_proximity hot-one encode
data=data.dropna() #drop column with empty cell

trainSet, testSet=train_test_split(data, test_size=0.3, random_state=42)#split test set
X=np.matrix(trainSet.iloc[:,:-1])
y=np.transpose(np.matrix(trainSet.iloc[:,-1]))
XTest=np.matrix(testSet.iloc[:,:-1])
yTest=np.transpose(np.matrix(testSet.iloc[:,-1]))

#特征缩放
sigma = np.std(X, axis=0)#X的每列标准差
mu=np.mean(X,axis=0)#X的每列平均
X=(X-mu)/sigma
XTest=(XTest-mu)/sigma

#梯度下降参数
theta=np.zeros((4, 1))
iteration=2000#迭代2000x
learnRate=0.01#迭代速度

def sigmoid(z):#帮助结果映射到[0,1]间
    z = z.astype(np.float32)#全部转换成float 避免TypeError: loop of ufunc does not support argument 0 of type float which has no callable radians
    return 1 / (1 + np.exp(-z))

for i in range(iteration):#梯度下降
    h_x = sigmoid(X @ theta)
    gradient = (X.T @ (h_x - y)) / y.shape[0]
    theta = theta - learnRate * gradient
    
TP = 0  # 准确是
FP = 0  # 准确不是
TN = 0  # 误判是
FN = 0  # 误判不是
#对test set 计算
yPred=[]
yPred=sigmoid(XTest@theta)
for i in range (XTest.shape[0]):
    if yPred[i] >= 0.5 and yTest[i] == 1:
        TP += 1
    elif yPred[i] >= 0.5 and yTest[i] == 0:
        FP += 1
    elif yPred[i] < 0.5 and yTest[i] == 0:
        TN += 1
    elif yPred[i] < 0.5 and yTest[i] == 1:
        FN += 1
    else:
        print(yTest[i])
        

print("Accuracy")
print((TP+TN)/(TP+FP+TN+FN))
print("Precision")#预测是Iris-virginica，实际就是Iris-virginica比例
precs=(TP)/(TP+FP)
print(precs)
print("Recall")#所有实际就是Iris-virginica，被正确预测为Iris-virginica的比例
recall=(TP)/(TP+FN)
print(recall)
print("F1-score")
print(2*(precs*recall)/(precs+recall))