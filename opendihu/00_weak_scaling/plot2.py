#!/usr/bin/env python
# -*- coding: utf-8 -*-

# parallel weak scaling

import sys
import numpy as np
import subprocess
import datetime
import time
import os

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from IPython.display import display

input_filename = "logs/log.csv"

show_plots = True
if len(sys.argv) > 1:
  show_plots = False;

n_columns = 60

plt.rcParams.update({'font.size': 16})
plt.rcParams['lines.linewidth'] = 2

# determine number of columns
with open(input_filename) as f:
  line = f.readline()
  if "~nDofsFiber0" in line:
    pos = line.find("~nDofsFiber0")
    column_names = line[0:pos].split(";")
    n_columns = len(column_names)

#df = pd.DataFrame()
df = pd.read_csv(input_filename, sep=';', error_bad_lines=False, warn_bad_lines=True, comment="#", header=None, names=column_names, usecols=range(n_columns))

df = df.loc[df['endTime'] == 1]
df['# timestamp'] =  pd.to_datetime(df['# timestamp'])

# Info about the data structure
print("df info:")
df.info()
print(df.head())

df_ranks = df.groupby(['nRanks'])

columns_to_plot = ["total", "duration_0D", "duration_1D", "duration_bidomain"]

# too many values
#columns_to_plot = ["duration_total", "duration_0D", "duration_1D", "duration_bidomain", "durationInitCellml", "durationReadGeometry", "durationWriteOutput"]

columns_to_extract = columns_to_plot + ["durationReadGeometry", "durationSetStiffnessMatrix", 
  "durationWriteOutput", "durationAssembleBoundaryConditions", "durationInitCellml", "durationComputeMappingBetweenMeshes",
   "durationMap", "memoryResidentSet"]

column_shortnames = {
  "totalUsertime": "total",
  "duration_total": "totalComp",
  "duration_0D": "0D",
  "duration_1D": "1D",
  "duration_bidomain": "bidomain",
  "durationAssembleBoundaryConditions": "initBC",
  "durationSetStiffnessMatrix": "stiffness",
  "durationComputeMappingBetweenMeshes": "compMap",
  "durationMap": "map",
  "durationReadGeometry": "read",
  "durationWriteOutput": "write",
  "durationInitCellml": "initCell",
  "memoryResidentSet": "mem"
}

# column_shortnames.values()
ordered_values = ['n', 'totalComp', 'total', '0D', '1D', "bidomain", 'stiffness', 'initCell', 'initBC', 'read', 'write', 'compMap', 'map', "mem"]

df_cray = df[df['version'].str.contains("Cray Cray")]
df_gnu = df[df['version'].str.contains("GCC 8")]

print("n rows:")
print(len(df.index))
print("n cray:")
print(len(df_cray.index))
print("n GCC:")
print(len(df_gnu.index))

# set options for console display
pd.set_option('display.max_rows', 500)
pd.set_option('display.max_columns', 500)
pd.set_option('display.width', 1000)
def merge_dicts(x, y):
  z = x.copy()   # start with x's keys and values
  z.update(y)    # modifies z with y's keys and values & returns None
  return z


x = {column_name: np.mean for column_name in columns_to_extract}

 
def plot(df, title, columns_to_plot, mylabels=None):
  means = df.groupby(['nRanks']).mean()
  if len(means) == 0:
    return
  errors = df.groupby(['nRanks']).std()
  means.plot(marker='o', y=columns_to_plot, title = "weak scaling", logx=True, logy=True, yerr=errors)
  
  rank_nos = sorted(list(set(df["nRanks"])))
  ax = plt.gca()
  ax.set_xticks(rank_nos)
  ax.set_xticklabels(rank_nos)
  ax.grid(which='major')
  ax.set_xlabel('number of processes')
  ax.set_ylabel('runtime [s]')
  ax.set_title(title)
  if mylabels is not None:
    ax.legend(labels=mylabels)
  
  if show_plots:
    plt.show()
  else:
    plt.tight_layout()
    plt.savefig("{}.pdf".format(title.replace(" ", "")))
 
def print_table(df, title, columns_to_plot, mylabels=None):

  print("")
  print("------------")
  print(title)
  print(df.groupby(['nRanks']))
    
  print(df.groupby(['nRanks']).\
    agg(merge_dicts(x,{'n': np.size, "memoryResidentSet": lambda v: "{:.3f} GB".format(np.mean(v)/(1024.**3))})).rename(columns=column_shortnames))[ordered_values]
    
  # write plot to file
  plot(df, title, columns_to_plot, mylabels)

#mylabels = ["bad placement", "optimal placement"]
mylabels=None
columns_to_plot = ["totalUsertime", "duration_0D", "duration_1D", "durationReadGeometry", "durationWriteOutput"]
mylabels = ["total", "0D model", "1D model", "read geometry files", "write VTK files"]
print_table(df_cray, "", columns_to_plot, mylabels)
exit()



print_table(df_gnu, "GNU compiler (without rank reordering)", columns_to_plot)
    
#df_cray_reordering = df_cray[df_cray['# timestamp'] > pd.to_datetime("2019/2/27")]
#df_gnu_reordering = df_gnu[df_gnu['# timestamp'] > pd.to_datetime("2019/2/27")]

print_table(df_cray_reordering, "Cray compiler (with rank reordering)", columns_to_plot)
print_table(df_gnu_reordering, "GNU compiler (with rank reordering)", columns_to_plot)

columns = list(df_cray_reordering)
column_dict = {name: "{}_reordering".format(name) for name in columns if name != "nRanks"}
df_cray_reordering=df_cray_reordering.rename(columns=column_dict)

df_rr = pd.concat([df_cray_reordering,df_cray])
print(df_rr.info())
columns_to_plot0 = []

columns_to_plot0 = ["duration_1D", "duration_1D_reordering"]
mylabels = ["bad placement", "optimal placement"]
print_table(df_rr, "Effect of rank reordering", columns_to_plot0, mylabels)

    
# plot
