import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split

data = pd.read_csv("housing.csv")
ocean_proximity_map={"INLAND":0,"<1H OCEAN":1,"NEAR OCEAN ":2,"NEAR BAY":3,"ISLAND":4}
data['ocean_proximity']=data['ocean_proximity'].map(ocean_proximity_map)#ocean_proximity hot-one encode
data=data.dropna() #drop column with empty cell

dataEncoded=pd.get_dummies(data)
trainSet, testSet=train_test_split(dataEncoded, test_size=0.3, random_state=42)

X = trainSet.drop(columns=['median_house_value']).values
Y = trainSet['median_house_value'].values
XTest = testSet.drop(columns=['median_house_value']).values
YTest = testSet['median_house_value'].values

X=np.matrix(trainSet.drop(columns=['median_house_value']).values) #convert to matrix
Y=np.transpose(np.matrix(trainSet['median_house_value'].values))#rotate Y from 1*n to n*1
XTest=np.matrix(testSet.drop(columns=['median_house_value']).values)
YTest=np.matrix(testSet['median_house_value'].values)

print("X:",X.shape)
print("Y:",Y.shape)

#特征缩放
sigma=np.std(X,axis=0)#X的每列标准差
mu=np.mean(X.mean,axis=0)#X的每列平均
X=(x-mu)/sigma
