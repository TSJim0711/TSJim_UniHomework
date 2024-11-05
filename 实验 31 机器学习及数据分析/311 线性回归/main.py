import pandas as pd
import numpy as np

data = pd.read_csv("housing.csv")

data_encoded=pd.get_dummies(data,columns=['ocean_proximity'])

s=(data.dtypes=='ocean_proximity')
object_cols=list(s[s].index)

X = data_encoded.drop(columns=['median_house_value']).values.astype(np.float64)
Y=data_encoded['median_house_value'].values

W=np.linalg.inv(X.T@X)@X.T@Y

pd.set_option('display.max_rows',5)
pd.set_option('display.max_columns',None)

print("data_Enc:\n",data_encoded)
print("W:",W)
