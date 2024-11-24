import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split

data=pd.read_csv("source.data")
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
for i in range (XTest.shape[0]):  #把阈值提升到0.85， 可以让Precision提升到84%左右....
    if yPred[i] >= 0.5 and yTest[i] == 1:
        TP += 1
    elif yPred[i] >= 0.5 and yTest[i] == 0:
        FP += 1
    elif yPred[i] < 0.5 and yTest[i] == 0:
        TN += 1
    elif yPred[i] < 0.5 and yTest[i] == 1:
        FN += 1
        
print("Descent:")
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

###朴素贝叶斯###
X=np.array(trainSet.iloc[:,:-1])
y=np.array(trainSet.iloc[:,-1])
XTest=np.array(testSet.iloc[:,:-1])
yTest=np.array(testSet.iloc[:,-1])

# 朴素贝叶斯模型
classes = np.unique(y)  #获取所有类别，当中，y只有1（是Iris-virginica）/0（不是Iris-virginica）
n_classes = len(classes)  # 类别数量，当中，y只有两个：1或0
n_samples= n_features = X.shape[1]  # 几个参数？4个

# 初始化存储先验概率、均值和方差的数组
prior = np.zeros(n_classes, dtype=np.float64)  # 每个类别先验
mean = np.zeros((n_classes, n_features), dtype=np.float64)  # 特征在类别的平均
var = np.zeros((n_classes, n_features), dtype=np.float64)  # 特征在类别的方差

for idx, c in enumerate(classes): #idx->0开始，c=classes[idx],统计y所有属于0 or 1的
    X_c = X[y == c]#选中所有结果是0（第二次是1）的X里面的4个参数
    prior[idx] = X_c.shape[0] / n_samples#先验
    mean[idx, :] = np.mean(X_c, axis=0)#平均值，每一个参数在0（不是Iris-virginica）的平均值，下一回for就是1
    var[idx, :] = np.var(X_c, axis=0)#方差 同上^^^^

yPred=[]#预测结果
for x in XTest:#取测试数据参数
    yCuzX =[]#y因X概率 后验
    for idx, c in enumerate(classes):#idx->0开始，c=classes[idx],统计y所有属于0 or 1的
        #估计后验
        log_prior = np.log(prior[idx])#先验概率的对数 log(P(Y=c))
        numerator = np.exp(-((x - mean[idx]) ** 2) / (2 * var[idx]))  # 高斯分布分子
        denominator = np.sqrt(2 * np.pi * var[idx])  # 高斯分布分母  \(? . ? )/
        log_conditional = np.sum(np.log(numerator / denominator))# 计算条件概率的对数 log(P(x|Y=c))，对每个特征求和
        yCuzX.append(log_prior + log_conditional)# 后验概率的对数 log(P(Y=c|X)) = log(P(Y=c)) + log(P(X|Y=c))
        
    yPred.append(classes[np.argmax(yCuzX)])#取最大后验概率作判断
yPred = np.array(yPred)  #NumPy数组好像兼容更好？

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

print("\nNaive Bayes:")
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