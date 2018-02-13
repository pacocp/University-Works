'''
Fracisco Carrillo Pérez
Inteligencia de Negocio 
Práctica 3
'''
import numpy as np
import pandas as pd
from sklearn import preprocessing
from sklearn.preprocessing import StandardScaler
from scipy.stats import skew
import scipy.stats as st
from math import sqrt
import os

from six.moves import cPickle as pickle
import matplotlib
import matplotlib.pyplot as plt
from matplotlib.pylab import rcParams
import seaborn as sns

from sklearn import datasets, linear_model
from sklearn.linear_model import Ridge, RidgeCV, ElasticNet, LassoCV, Lasso
from sklearn.ensemble import ExtraTreesRegressor
from sklearn.ensemble import RandomForestRegressor
from sklearn import cross_validation, metrics
from sklearn.cross_validation import KFold
from sklearn.metrics import mean_squared_error
import xgboost as xgb

#data_root = '../input' # Change me to store data elsewhere

#reading the train and test datasets
train = pd.read_csv("train.csv")
test = pd.read_csv("test.csv")

# keep ID for submission
train_ID = train['Id']
test_ID = test['Id']

#--------------------------------------------------
trainSize = train.shape #size of the train dataset
testSize = test.shape #size of the test dataset
print("train dataset size = %s x %s" % (trainSize))
print("test dataset size = %s x %s" % (testSize))

#outliers treatment
train = train.drop(train[(train['GrLivArea']>4000) & (train['SalePrice']<1000000)].index) 
train = train.drop(train[(train['LotArea']>100000) & (train['SalePrice']<500000)].index) 
train = train.drop(train[(train['LotFrontage']>300) & (train['SalePrice']<300000)].index) 
train = train.drop(train[(train['TotalBsmtSF']>5000) & (train['SalePrice']<200000)].index) # parecen ser el mismo 

y = train.SalePrice
y = np.log1p(y)
train.drop('SalePrice',1,inplace=True)
all_data = pd.concat([train,test]) 

##drop attributes with many missing values
#too many missing values
all_data.drop("Alley", 1,inplace=True)
all_data.drop("Fence", 1,inplace=True)
all_data.drop("MiscFeature", 1,inplace=True)
all_data.drop("PoolQC", 1,inplace=True)
all_data.drop("FireplaceQu", 1,inplace=True)
#non-intuitive features
#all_data.drop("GarageArea", 1,inplace=True)
all_data.drop("MSSubClass", 1,inplace=True)
all_data.drop("GarageYrBlt", 1,inplace=True)
all_data.drop("RoofMatl", 1,inplace=True)
#convert year to age
Yr = max(all_data['YearBuilt'])
all_data['BuildingAge'] = all_data['YearBuilt'].apply(lambda x: Yr-x if not pd.isnull(x) else 'None')
all_data['RemodelAge'] = all_data['YearRemodAdd'].apply(lambda x: Yr-x if not pd.isnull(x) else 'None')
all_data['SellAge'] = all_data['YrSold'].apply(lambda x: Yr-x if not pd.isnull(x) else 'None')
#drop old variables
all_data.drop("YearBuilt", 1,inplace=True);
all_data.drop("RemodelAge", 1,inplace=True);
all_data.drop("YrSold", 1,inplace=True);
# add a new feature 'total sqfootage'
all_data['TotalSF'] = all_data['TotalBsmtSF'] + all_data['1stFlrSF'] + all_data['2ndFlrSF']
all_data.drop(['1stFlrSF', '2ndFlrSF'], axis=1, inplace=True)

#extraxt train and test datasets
train = all_data[:train.shape[0]]
test = all_data[train.shape[0]:]

#divide features into numeric and categorical 
numeric = [c for c in train.columns if train.dtypes[c] != 'object']
numeric.remove('Id')
print("Number of Numeric Attributes = %s" % (len(numeric)))
categorical = [c for c in train.columns if train.dtypes[c] == 'object']
print("Number of Categorical Attributes = %s" % (len(categorical)))

##preprocessing of numeric features
feature = train[numeric].dropna()
skewed_feats = feature.apply(skew) #compute skewness
skewed_feats = skewed_feats[(skewed_feats > 0.5) | (skewed_feats < -0.5)]
skewed_feats = skewed_feats.index

#log transformation to resolve skewness on train and test data
all_data[skewed_feats] = np.log1p(all_data[skewed_feats])

pd.options.mode.chained_assignment = None  # default='warn'
#standard scale (zero mean and unit variance)
all_data[numeric] = all_data[numeric].fillna(all_data[numeric].mean())
x_train = all_data[:train.shape[0]]
x_test = all_data[train.shape[0]:]
columns=x_train.columns
x_train[numeric] = StandardScaler().fit_transform(x_train[numeric])
x_train = pd.DataFrame(x_train, index=x_train.index, columns=x_train.columns)
x_test[numeric] = StandardScaler().fit_transform(x_test[numeric])
x_test = pd.DataFrame(x_test, index=x_test.index, columns=x_test.columns)
all_data = pd.concat([x_train,x_test])

'''
##preprocessing of categorical features
feature = all_data[categorical]
#identify the most frequent level of each categorical feature
frequentLevel = feature.apply(lambda x: x.value_counts().idxmax())
def itemReplace (column,value):
    frequentLevel[column] = value
itemReplace('BsmtFinSF1','None')
itemReplace('BsmtFinSF2','None')
itemReplace('GarageType','None')
itemReplace('GarageFinish','None')
itemReplace('GarageQual','None')
itemReplace('GarageCond','None')
all_data[categorical] = feature.fillna(frequentLevel)
'''
# MSZoning NA in pred. filling with most popular values
all_data['MSZoning'] = all_data['MSZoning'].fillna(all_data['MSZoning'].mode()[0])

# LotFrontage  NA in all. I suppose NA means 0
all_data['LotFrontage'] = all_data['LotFrontage'].fillna(all_data['LotFrontage'].mean())

# MasVnrType NA in all. filling with most popular values
all_data['MasVnrType'] = all_data['MasVnrType'].fillna(all_data['MasVnrType'].mode()[0])

# BsmtQual, BsmtCond, BsmtExposure, BsmtFinType1, BsmtFinType2
# NA in all. NA means No basement
for col in ('BsmtQual', 'BsmtCond', 'BsmtExposure', 'BsmtFinType1', 'BsmtFinType2'):
    all_data[col] = all_data[col].fillna('NoBSMT')

# TotalBsmtSF  NA in pred. I suppose NA means 0
all_data['TotalBsmtSF'] = all_data['TotalBsmtSF'].fillna(0)

# Electrical NA in pred. filling with most popular values
all_data['Electrical'] = all_data['Electrical'].fillna(all_data['Electrical'].mode()[0])

# KitchenQual NA in pred. filling with most popular values
all_data['KitchenQual'] = all_data['KitchenQual'].fillna(all_data['KitchenQual'].mode()[0])

# GarageType, GarageFinish, GarageQual  NA in all. NA means No Garage
for col in ('GarageType', 'GarageFinish', 'GarageQual'):
    all_data[col] = all_data[col].fillna('NoGRG')

# GarageCars  NA in pred. I suppose NA means 0
all_data['GarageCars'] = all_data['GarageCars'].fillna(0.0)

# SaleType NA in pred. filling with most popular values
all_data['SaleType'] = all_data['SaleType'].fillna(all_data['SaleType'].mode()[0])
#transform categorical variables into dummy variables
all_data = pd.get_dummies(all_data)

# create new variable LivArea_Total
all_data['LivArea_Total'] = all_data['GrLivArea'] + all_data['GarageArea'] + all_data['PoolArea']

x_train = all_data[:train.shape[0]]
x_test = all_data[train.shape[0]:]
columns=x_train.columns
print(x_train.shape)
print(x_test.shape)

x_train.drop("Id", 1,inplace=True)
x_test.drop("Id", 1,inplace=True)
names = list(x_train)

x_train = np.array(x_train)
x_test = np.array(x_test)
y_train = np.array(y)
ntrain = x_train.shape[0]
ntest = x_test.shape[0]

from sklearn.linear_model import ElasticNet

'''
LGBM
'''

import lightgbm as lgb
from sklearn.model_selection import KFold, cross_val_score, train_test_split

gbm = lgb.LGBMRegressor(bagging_fraction=0.8, bagging_freq=5, bagging_seed=9,
	boosting_type='gbdt', colsample_bytree=1.0, feature_fraction=0.2319,
	feature_fraction_seed=9, learning_rate=0.01, max_bin=55,
	max_depth=-1, min_child_samples=20, min_child_weight=0.001,
	min_data_in_leaf=2, min_split_gain=0.0, min_sum_hessian_in_leaf=11,
	n_estimators=3862, n_jobs=-1, num_leaves=5, objective='regression',
	random_state=None, reg_alpha=0.0, reg_lambda=0.0, silent=True,
	subsample=1.0, subsample_for_bin=200000, subsample_freq=1,
	verbose=0)

'''
# specify parameters and distributions to sample from
from scipy.stats import randint as sp_randint
from sklearn.model_selection import RandomizedSearchCV
param_dist = {"num_leaves": sp_randint(5,1000),
              "learning_rate": [0.01,0.02,0.03,0.05,0.1,0.15,0.2,0.3,0.4,0.5,0.6,0.7,0.8],
              "min_data_in_leaf": sp_randint(1, 50),
              "n_estimators": sp_randint(10, 8000)}
#run randomized search
n_iter_search = 20
random_search = RandomizedSearchCV(gbm, param_distributions=param_dist,
                                   n_iter=n_iter_search)
random_search.fit(x_train,y_train)
print(random_search.best_estimator_)
'''

# Average R2 score and standart deviation of 5-fold cross-validation
scores = cross_val_score(gbm, x_train, y_train, cv=5)
print("Accuracy GBM: %0.2f (+/- %0.2f)" % (scores.mean(), scores.std() * 2))
# Prints R2 and RMSE scores
def get_score(prediction, lables):    
    from sklearn.metrics import r2_score, mean_squared_error
    print('R2: {}'.format(r2_score(prediction, lables)))
    print('RMSE: {}'.format(np.sqrt(mean_squared_error(prediction, lables))))

gbm = gbm.fit(x_train,y_train)
predictions_gbm = gbm.predict(x_train)
get_score(predictions_gbm,y_train)

elesnet = ElasticNet(alpha=0.0004, l1_ratio=1.2)

'''
# specify parameters and distributions to sample from
from scipy.stats import randint as sp_randint
from numpy.random import random_sample
from sklearn.model_selection import RandomizedSearchCV
param_dist = {"alpha": random_sample(20),
              "l1_ratio": sp_randint(1.0,6.0)}
#run randomized search
n_iter_search = 20
random_search = RandomizedSearchCV(elesnet, param_distributions=param_dist,
                                   n_iter=n_iter_search)
random_search.fit(x_train,y_train)
print(random_search.best_estimator_)
'''
# Average R2 score and standart deviation of 5-fold cross-validation
scores = cross_val_score(elesnet, x_train, y_train, cv=5)
print("Accuracy elesnet: %0.2f (+/- %0.2f)" % (scores.mean(), scores.std() * 2))

elesnet = elesnet.fit(x_train,y_train)
predictions_elesnet = elesnet.predict(x_train)
get_score(predictions_elesnet,y_train)

predictions = predictions_gbm*0.5 + predictions_elesnet*0.5
get_score(predictions,y_train)

'''
#Ridge Regularization model
'''
'''
# fit a ridge regularization model
from sklearn.linear_model import Ridge
ridge_model = Ridge(alpha=7.0)
scores = cross_val_score(ridge_model, x_train, y_train,cv=5)
print("Accuracy Ridge: %0.2f (+/- %0.2f)" % (scores.mean(), scores.std() * 2))

ridge_model = ridge_model.fit(x_train,y_train)
predictions_ridge_model = ridge_model.predict(x_train)
get_score(predictions_ridge_model,y_train)

predictions = predictions_gbm*0.8 + predictions_elesnet*0.2
get_score(predictions,y_train)

from sklearn.base import BaseEstimator, TransformerMixin, RegressorMixin, clone
class AveragingModels(BaseEstimator, RegressorMixin, TransformerMixin):
    def __init__(self, models):
        self.models = models
        
    # we define clones of the original models to fit the data in
    def fit(self, X, y):
        self.models_ = [clone(x) for x in self.models]
        
        # Train cloned base models
        for model in self.models_:
            model.fit(X, y)

        return self
    
    #Now we do the predictions for cloned models and average them
    def predict(self, X):
        predictions = np.column_stack([
            model.predict(X) for model in self.models_
        ])
        return np.mean(predictions, axis=1)

averaged_models = AveragingModels(models = (elesnet,gbm))

# Average R2 score and standart deviation of 5-fold cross-validation
scores = cross_val_score(averaged_models, x_train, y_train, cv=5)
print("Accuracy Averaged: %0.2f (+/- %0.2f)" % (scores.mean(), scores.std() * 2))

averaged_models = AveragingModels(models = (elesnet,gbm))
averaged_models = averaged_models.fit(x_train,y_train)
predictions_averaged = averaged_models.predict(x_train)
predictions = predictions_averaged*0.7 + predictions_elesnet*0.3
get_score(predictions,y_train)
'''
gbm = lgb.LGBMRegressor(bagging_fraction=0.8, bagging_freq=5, bagging_seed=9,
	boosting_type='gbdt', colsample_bytree=1.0, feature_fraction=0.2319,
	feature_fraction_seed=9, learning_rate=0.01, max_bin=55,
	max_depth=-1, min_child_samples=20, min_child_weight=0.001,
	min_data_in_leaf=2, min_split_gain=0.0, min_sum_hessian_in_leaf=11,
	n_estimators=3862, n_jobs=-1, num_leaves=5, objective='regression',
	random_state=None, reg_alpha=0.0, reg_lambda=0.0, silent=True,
	subsample=1.0, subsample_for_bin=200000, subsample_freq=1,
	verbose=0)

elesnet = ElasticNet(alpha=0.0004, l1_ratio=1.2)
gbm = gbm.fit(x_train,y_train)
elesnet = elesnet.fit(x_train,y_train)

#Final_labels = np.exp(gbm.predict(x_test))
Final_labels = np.exp(gbm.predict(x_test))*0.5 + np.exp(elesnet.predict(x_test))*0.5
pd.DataFrame({'Id': test_ID, 'SalePrice': Final_labels}).to_csv('submission.csv', index =False)