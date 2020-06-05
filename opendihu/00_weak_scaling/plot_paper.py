#!/usr/bin/env python
# -*- coding: utf-8 -*-

# parallel weak scaling

import sys
import numpy as np
import subprocess
import datetime
import time
from cycler import cycler
import os

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

input_filename_no_rr = "logs/log_no_rr.csv"
input_filename = "logs/weak_scaling_paper.csv"

show_plots = True
if len(sys.argv) > 1:
  show_plots = False;

n_columns = 60

plt.rcParams.update({'font.size': 16})
plt.rcParams['lines.linewidth'] = 2

def load_df(input_filename):

  # determine number of columns
  with open(input_filename) as f:
    line = f.readline()
    if "~nDofsFiber0" in line:
      pos = line.find("~nDofsFiber0")
      column_names = line[0:pos].split(";")
      n_columns = len(column_names)
    else:
      column_names = line.split(";")
      n_columns = len(column_names)

  # load data frame
  df = pd.read_csv(input_filename, sep=';', error_bad_lines=False, warn_bad_lines=True, comment="#", names=column_names, usecols=range(n_columns), engine='python')

  # filter data to only include those with endTime == 1
  df = df.loc[df['endTime'] == 1]

  # parse timestamp
  df['# timestamp'] =  pd.to_datetime(df['# timestamp'])

  # compute new field for initialization time
  if 'durationParaview3DInit' not in df:
      df['durationParaview3DInit'] = 0
  if 'durationParaview1DInit' not in df:
      df['durationParaview1DInit'] = 0
  if 'durationParaview1DWrite' not in df:
      df['durationParaview1DWrite'] = 0
      
  if 'durationParaview3DWrite' not in df:
    if 'durationParaviewOutput' in df:
      df['durationOnlyWrite'] = df['durationParaviewOutput']
    else:
      df['durationOnlyWrite'] = df['durationWriteOutput']
  else:
    df['durationOnlyWrite'] = df['durationParaview3DWrite'] + df['durationParaview1DWrite']

      
  df['duration_init'] = df['totalUsertime'] - df['duration_total'] + df['durationParaview3DInit'] + df['durationParaview1DInit']
  
  df['duration_1gmres'] = df['duration_bidomain'] / df['nIterations_activationSolver']
  #? df['duration_bidomain'] = 10000*df['duration_1gmres']
  
  return df

df = load_df(input_filename)

# Info about the data structure
print("df info:")
df.info()
print(df.head())

columns_to_extract = ["duration_total", "duration_0D", "duration_1D", "duration_bidomain", "totalUsertime", "durationReadGeometry", "durationSetStiffnessMatrix", 
  "durationOnlyWrite", "durationAssembleBoundaryConditions", "durationInitCellml", "durationComputeMappingBetweenMeshes",
   "durationMap", "memoryResidentSet", "nIterations_activationSolver",
   "durationWriteOutput"]

column_shortnames = {
  "totalUsertime": "total",
  "duration_total": "computation",
  "duration_0D": "0D",
  "duration_1D": "1D",
  "duration_init": "duration_init",
  "duration_bidomain": "bidomain",
  "nIterations_activationSolver": "nIt",
  "durationAssembleBoundaryConditions": "initBC",
  "durationSetStiffnessMatrix": "stiffness",
  "durationComputeMappingBetweenMeshes": "compMap",
  "durationMap": "map",
  "durationReadGeometry": "read",
  "durationOnlyWrite": "write",
  "durationInitCellml": "initCell",
  "memoryResidentSet": "mem",
  "durationWriteOutput": "writeOutput",
  "durationParaviewOutput": "writeParaview",
  "durationParaview1DWrite": "paraview1DWrite",
  "durationParaview3DWrite": "paraview3DWrite",
  "durationParaview1DInit": "paraview1DInit",
  "durationParaview3DInit": "paraview3DInit"
}

# column_shortnames.values()
ordered_values = ['n', "total", '0D', '1D', "bidomain", "nIt", "computation", 'stiffness', 'initCell', 'initBC', 'read', 'write',
'compMap', 'map', "mem", "writeOutput"]



#df_cray = df[df['version'].str.contains("Cray Cray")]
#df_gnu = df[df['version'].str.contains("GCC 8")]

print("n rows:")
print(len(df.index))

# set options for console display
pd.set_option('display.max_rows', 500)
pd.set_option('display.max_columns', 500)
pd.set_option('display.width', 1000)

def merge_dicts(x, y):
  z = x.copy()   # start with x's keys and values
  z.update(y)    # modifies z with y's keys and values & returns None
  return z

x = {column_name: np.mean for column_name in columns_to_extract}
 
def plot(df, title, filename, columns_to_plot, mylabels=None, labels_loc=None, colors=None):
  means = df.groupby(['nRanks']).mean()
  if len(means) == 0:
    return
  
  #linestyle_cycler = cycler.cycler('linestyle',['-','--',':','-.'])
  # (cycler.cycler('color', ["k",(0.3,0.3,0.7),(0.7,0.7,1.0), "r", "y"])+cycler.cycler('linestyle', ['-', '--', ':', '-', '-'])))
  if colors is None:
    colors = ['k', (0.6,0.6,1.0), (0.1,0.1,0.6), 'r', 'y']
  plt.rc('axes', prop_cycle=(cycler('color', colors)))
  #plt.rc('axes', prop_cycle=("cycler('color', 'rgb') + cycler('linestyle',  ['-', '-', ':'])"))
    
  errors = df.groupby(['nRanks']).std()
  ax = means.plot(figsize=(8,6.5), y=columns_to_plot, title = "weak scaling", logx=True, logy=True, yerr=errors, marker='o')
  
  rank_nos = sorted(list(set(df["nRanks"])))
  
  ax = plt.gca()
  ax.set_xticks(rank_nos)
  
  if len(rank_nos) > 8:
    rank_nos[7] = "\n{}".format(rank_nos[7])
  if len(rank_nos) > 9:
    rank_nos[9] = "\n{}".format(rank_nos[9])
  
  ax.set_xticklabels(rank_nos)
  ax.grid(which='major')
  ax.set_xlabel('number of processes')
  ax.set_ylabel('runtime [s]')
  
  ax.set_title(title)
  if mylabels is not None:
    ax.legend(labels=mylabels, loc=labels_loc)
  
  plt.tight_layout()
  filename += ".pdf"
  plt.savefig(filename)
  print("wrote file \"{}\"".format(filename))
 
def print_table(df, title, filename, columns_to_plot, mylabels=None, labels_loc=None, colors=None):

  print("")
  print("------------")
  print(title)
  print(filename)
  print(df.groupby(['nRanks']).\
    agg(merge_dicts(x,{'n': np.size, "memoryResidentSet": lambda v: "{:.3f} GB".format(np.mean(v)/(1024.**3))})).rename(columns=column_shortnames)[ordered_values])
    
  # write plot to file
  plot(df, title, filename, columns_to_plot, mylabels, labels_loc, colors)

#############################
# weak scaling

df_weak_scaling = df[df['scenarioName'].str.contains("weak_scaling")]

#df_weak_scaling['totalUsertime'] = (df_weak_scaling['totalUsertime']-df_weak_scaling['duration_init'])*1000
df_weak_scaling['duration_bidomain']*=1000
df_weak_scaling['duration_1D']*=1000
df_weak_scaling['duration_0D']*=1000
df_weak_scaling['durationComputeMappingBetweenMeshes']*=1000

#mylabels = ["bad placement", "optimal placement"]
columns_to_plot = ["duration_init", "duration_bidomain", "duration_1D", "duration_0D", "durationComputeMappingBetweenMeshes"]
#columns_to_plot = ["totalUsertime", "duration_init", "durationOnlyWrite", "duration_bidomain", "duration_1D", "duration_0D"]
#columns_to_plot = ["totalUsertime", "duration_init", "durationReadGeometry", "durationOnlyWrite", "duration_1D", "duration_0D"]
#mylabels = ["total", "read geometry files", "write VTK files", "1D model", "0D model", ]
mylabels = ["initialization", "3D model", "1D model", "0D model", "map 3D-1D"]
print_table(df_weak_scaling, "", "weak_scaling", columns_to_plot, mylabels, None, [(0.7,0.76,0.7), (0.1,0.1,0.6), 'r', 'y', (0.6,0.6,1.0)])


#############################
# rank reordering

columns_to_extract = ["duration_1D", "nRanks"]
df_no_rr = load_df(input_filename_no_rr)

#df_no_rr = df_no_rr[df_no_rr['scenarioName'].str.contains("no_rank_reordering")]

#columns_to_plot = ["duration_1D"]
#print_table(df_no_rr, "", "no_rr", columns_to_plot, None)

# rename columns with "_no_rr" suffix
columns = list(df_no_rr)
print("columns")
print(columns)
column_dict = {name: "{}_no_rr".format(name) for name in columns if name != "nRanks"}
df_no_rr = df_no_rr.rename(columns=column_dict)

df_weak_scaling = df_weak_scaling[df_weak_scaling['nRanks'] <= 7776]

df = pd.concat([df_weak_scaling,df_no_rr])

df['duration_1D_no_rr'] *= 1000
columns_to_plot = ["duration_1D_no_rr", "duration_1D"]
mylabels = ["round-robin placement", "optimal placement"]
colors = [(0.9,0.6,0.0),'r']
print_table(df, "", "rank_placement", columns_to_plot, mylabels, None, colors)

if show_plots:
  plt.show()
exit()


# old code
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
