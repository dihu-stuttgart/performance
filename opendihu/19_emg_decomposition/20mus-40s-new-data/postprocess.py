#!/usr/bin/python3

# Use this script to convert the training output to a file that contains the IPTs for plotting.
# you have to manually adjust the file names.


import numpy as np
from sklearn.cluster import KMeans
import sys
import os

# -- first approach: using KMeans
y_predictions = np.loadtxt('prediction.csv', delimiter=',')
n_mus = y_predictions.shape[1]
print("n MUs: {}".format(n_mus-1))

with open('ipt_prediction_ground_truth_more_electrodes_class_weights0.csv', 'wb') as f:
  predictions = np.argmax(np.array(y_predictions), axis=1)
  IPT = []
  for i in range(1,n_mus):
    if np.where(predictions == i): 
      IPT.append(np.where(predictions == i)) 
      np.savetxt(f, np.where(predictions == i), delimiter=';')

# -- second approach: using maximum
y_prediction = np.loadtxt('y_prediction.csv', delimiter=',')
n_times = len(y_prediction)
n_mus = (int)(np.max(y_prediction))
print("n MUs: {}, n times: {}".format(n_mus, n_times))

firing_times = [[] for _ in range(n_mus+1)]
for i,mu_no in enumerate(y_prediction):
  mu_no = int(mu_no)
  firing_times[mu_no].append(i)
  
print(firing_times)
  
try:
  os.remove('ipt_prediction_ground_truth_more_electrodes_class_weights.csv')
except:
  pass
with open('ipt_prediction_ground_truth_more_electrodes_class_weights.csv', 'ab') as f:
  for mu_no,times in enumerate(firing_times):
    if mu_no > 0:
      print(np.array(times))
      np.savetxt(f, np.array([times]), delimiter=';')
