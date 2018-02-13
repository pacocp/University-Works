# -*- coding: utf-8 -*-
"""
Autor:
    Jorge Casillas
Fecha:
    Octubre/2017
Contenido:
    Ejemplo de uso de clustering en Python
    Inteligencia de Negocio
    Grado en Ingeniería Informática
    Universidad de Granada
"""

'''
Modificaciones: Francisco Carrillo Pérez
'''

'''
Documentación sobre clustering en Python:
    http://scikit-learn.org/stable/modules/clustering.html
    http://www.learndatasci.com/k-means-clustering-algorithms-python-intro/
    http://hdbscan.readthedocs.io/en/latest/comparing_clustering_algorithms.html
    https://joernhees.de/blog/2015/08/26/scipy-hierarchical-clustering-and-dendrogram-tutorial/
    http://www.learndatasci.com/k-means-clustering-algorithms-python-intro/
'''

import time
from tqdm import tqdm

import matplotlib.pyplot as plt
import pandas as pd

from sklearn.cluster import KMeans,AgglomerativeClustering,MeanShift,AffinityPropagation
from sklearn.cluster import DBSCAN, Birch, SpectralClustering
from sklearn.mixture import GaussianMixture
from sklearn import metrics
from sklearn import preprocessing
from math import floor
import numpy as np 
import warnings
warnings.filterwarnings("ignore")

accidentes = pd.read_csv('accidentes_2013.csv')

# Sección para la selección de los distintos casos de uso
# Caso 1: accidentes de colisión de vehículos en una vía convencional
# Caso 2: accidentes de vuelco en la calzada con el suelo mojado
# Caso 3: atropello a peatón aislado o en grupo en Granada

subset1 = accidentes[accidentes['TIPO_ACCIDENTE'].str.contains("Colisión de vehículos")]
subset1 = subset1[subset1['TIPO_VIA'].str.contains("VÍA CONVENCIONAL")]

subset2 = accidentes[accidentes['TIPO_ACCIDENTE'].str.contains("Vuelco en la calzada")]
subset2 = subset2[subset2['SUPERFICIE_CALZADA'].str.contains("MOJADA")]

subset3=accidentes[accidentes['TIPO_ACCIDENTE'].str.contains("Atropello a peatón aislado o en grupo")]
subset3=subset3[subset3['PROVINCIA'].str.contains('Granada')]

subset4 = accidentes[accidentes['TIPO_ACCIDENTE'].str.contains("Colisión de vehículos")]
subset4 = subset4.loc[(subset4['DIASEMANA'] == 6) | (subset4["DIASEMANA"] == 7)]

#seleccionar variables de interés para clustering
#usadas = ['HORA', 'DIASEMANA', 'TOT_VICTIMAS', 'TOT_MUERTOS', 'TOT_HERIDOS_GRAVES', 'TOT_HERIDOS_LEVES', 'TOT_VEHICULOS_IMPLICADOS']
#usadas = ['TOT_MUERTOS', 'TOT_HERIDOS_GRAVES', 'TOT_HERIDOS_LEVES', 'TOT_VEHICULOS_IMPLICADOS']
usadas = ['TOT_MUERTOS', 'TOT_HERIDOS_GRAVES', 'TOT_HERIDOS_LEVES']
usadas2 = ['TOT_HERIDOS_LEVES','DIASEMANA','MES']
X_subset1 = subset1[usadas]
X_subset2 = subset2[usadas]
X_subset3 = subset3[usadas]
#X_subset4 = subset4[usadas]
# Size of the dataset

print("----- El tamaño del subset1: {} \n".format(len(subset1)))
print("----- El tamaño del subset2: {} \n".format(len(subset2)))
print("----- El tamaño del subset3: {} \n".format(len(subset3)))
print("----- El tamaño del subset4: {} \n".format(len(subset4)))

###########################
# para quedarnos con menos datos podemos hacer un X = X.sample(tamaño) y creamos un conjunto
# de datos más pequeño
###########################

# se deben normalizar los datos para las distancias
X_subset1 = X_subset1.sample(1000)
#X_subset4 = X_subset4.sample(1000)
X_normal_1 = preprocessing.normalize(X_subset1, norm='l2')
X_normal_2 = preprocessing.normalize(X_subset2, norm='l2')
X_normal_3 = preprocessing.normalize(X_subset3, norm='l2')
#X_normal_4 = preprocessing.normalize(X_subset4, norm='l2')


subsets = []
subsets.append(X_normal_1)
subsets.append(X_normal_2)
subsets.append(X_normal_3)
#subsets.append(X_normal_4)

subsets_original = []
subsets_original.append(X_subset1)
subsets_original.append(X_subset2)
subsets_original.append(X_subset3)
#subsets_original.append(X_subset4)
# diccionarios para el guardado de las variables
metrics_CH = dict()
metrics_SC = dict()
cluster_predict_all = dict()

# k = len(set(cluster_predict)) para ver cuantos clusters se han obtenido
# if k>1 and name is not ward en caso contrario pon las métricas a 0

print("------ Declarando los algoritmos")
k_means = KMeans(n_clusters=3,init='k-means++')
ward = AgglomerativeClustering(n_clusters=3,linkage='ward')
birch = Birch(n_clusters=3)
dbscan = DBSCAN(eps=0.01,min_samples=10)
spectral = SpectralClustering(n_clusters=3,affinity="nearest_neighbors")
#affinity_propagation = AffinityPropagation()
#ms = MeanShift()

clustering_algorithms = [
    ("k-means",k_means),
    ("ward",ward),
    ("birch",birch),
    ("dbscan",dbscan),
    ('spectral',spectral)
]


index = 1
for subset in subsets:
    print("Trabajando con subset {}".format(index))
    for name,algorithm in clustering_algorithms:
        print("{:7s}, ".format(name),end='')
        tiempo = time.time()
        cluster_predict = algorithm.fit_predict(subset)
        cluster_predict_all[name+str(index)] = cluster_predict
        k = len(set(cluster_predict))
        print("k: {:3.0f}, ".format(k),end='')
        print("{:0.2f} segundos, ".format(tiempo),end='')
        if (k>1) and (name is not "ward"):
            metric_CH = metrics.calinski_harabaz_score(subset, cluster_predict)
            metrics_CH[name+str(index)] = metric_CH
            metric_SC = metrics.silhouette_score(subset, cluster_predict, metric='euclidean', sample_size=floor(0.1*len(subset)), random_state=123456)
            metrics_SC[name+str(index)] = metric_SC
        else:
            metric_CH = 0
            metrics_CH[name+str(index)] = metric_CH
            metric_SC = 0
            metrics_SC[name+str(index)] = metric_SC
        print("Calinski-Harabaz Index: {:.3f}, ".format(metric_CH),end='')
        print("Silhouette Coefficient: {:.5f}\n".format(metric_SC))
        #se convierte la asignación de clusters a DataFrame
        clusters = pd.DataFrame(cluster_predict,index=subsets_original[index-1].index,columns=['cluster'])

        #y se añade como columna a X
        alg = pd.concat([subsets_original[index-1], clusters], axis=1)
        
        
        print("---------- Preparando el scatter matrix...")
        import seaborn as sns
        sns.set()
        sns.plt.title("Scatter matrix caso de estudio "+str(index)+"alg "+str(name))
        variables = list(alg)
        variables.remove('cluster') # debemos eliminarla para que no salga como variable
        sns_plot = sns.pairplot(alg, vars=variables, hue="cluster", palette='Paired', plot_kws={"s": 25}, diag_kind="hist")
        sns_plot.fig.subplots_adjust(wspace=.03, hspace=.03);
        sns_plot.savefig("Caso_de_estudio"+str(index)+str(name)+"scatter3.png")

        
        print("---------- Preparando el heatmap...")
        plt.clf()
        plt.cla()
        plt.close()
        sns.set()
        sns.plt.title("Heatmap caso de estudio "+str(index)+"alg "+str(name))
        variables = alg.copy()
        variables.pop('cluster') # debemos eliminarla para que no salga como variable
        heatmap_plot = sns.heatmap(variables)
        heatmap_plot.figure.savefig("Caso_de_estudio"+str(index)+str(name)+"heatmap3.png")
        
        print("---------- Preparando el dendogram...")
        plt.clf()
        plt.cla()
        plt.close()
        sns.set()
        sns.plt.title("Dendogram caso de estudio "+str(index)+"alg "+str(name))
        variables = alg.copy()
        variables.pop('cluster') # debemos eliminarla para que no salga como variable
        dendogram_plot = sns.clustermap(variables)
        dendogram_plot.savefig("Caso_de_estudio"+str(index)+str(name)+"dendogram3.png")
        
        
        print("---------- Visualización 3D")
        from mpl_toolkits.mplot3d import Axes3D
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')
        variables = alg.copy()
        x = subsets_original[index-1]['TOT_HERIDOS_LEVES'].values
        y = subsets_original[index-1]['DIASEMANA'].values
        z = subsets_original[index-1]['MES'].values
        plt.title("Caso_de_estudio "+str(index)+" "+str(name)+" con "+str(k)+" clusters")
        ax.scatter(x,y,z, marker="s", c=alg["cluster"], s=40, cmap="RdBu")
        ax.set_xlabel('TOT_HERIDOS_LEVES')
        ax.set_ylabel('DIASEMANA')
        ax.set_zlabel('MES')
        fig.savefig("Caso_de_estudio"+str(index)+str(name)+"3D3.png", bbox_inches='tight')
        
    index = index + 1
