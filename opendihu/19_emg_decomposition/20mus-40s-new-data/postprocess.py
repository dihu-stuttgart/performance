
import numpy as np
from sklearn.cluster import KMeans
import sys
import os

y_predictions = np.loadtxt('prediction.csv', delimiter=',')
print(y_predictions.shape)
#    y_predictions = model.predict(test_data_gen)
#    np.savetxt('prediction.csv', y_predictions, delimiter=',')
#    model.save('2040_IPT_MODEL.h5')
    # Kmeans clustering for converting to timestamp
predictions = KMeans(n_clusters=15, random_state=0).fit(y_predictions)
print("predictions: {}, shape: {}".format(predictions.labels_, predictions.labels_.shape))
IPT = []
n_classes = max(predictions.labels_)+1
print("n_classes: {}".format(n_classes))

with open('ipt_prediction.csv', 'wb') as f:
  for i in range(n_classes):
    if np.where(predictions.labels_ == i):
      class_IPT = np.where(predictions.labels_ == i)
      IPT.append(class_IPT)
      np.savetxt(f, class_IPT, delimiter=';')
threshold_IPT = np.array(IPT).reshape(n_classes,-1)
print("IPT.shape: {}".format(threshold_IPT.shape))
#np.savetxt('threshold_IPT.csv', threshold_IPT, delimiter=',')


