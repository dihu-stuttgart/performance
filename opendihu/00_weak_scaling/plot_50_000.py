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

input_filename = "logs/log.csv"
input_filename = "logs/log_50_000.csv"

show_plots = True
if len(sys.argv) > 1:
  show_plots = False;

n_columns = 60

plt.rcParams.update({'font.size': 20})
plt.rcParams['lines.linewidth'] = 2

# determine number of columns
with open(input_filename) as f:
  line = f.readline()
  if "~nDofsFiber0" in line:
    pos = line.find("~nDofsFiber0")
    column_names = line[0:pos].split(";")
    n_columns = len(column_names)

# load data frame
df = pd.read_csv(input_filename, sep=';', error_bad_lines=False, warn_bad_lines=True, comment="#", header=None, names=column_names, usecols=range(n_columns))

# filter data
#df = df.loc[df['activationSolver_solverType'] == "gmres"]

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

df['duration_transfer_01D'] = df['duration_total_advanceTimeSpan1'] - df['duration_0D'] - df['duration_1D']

# Info about the data structure
print("df info:")
df.info()
print(df.head())

columns_to_plot = ["duration_total", "duration_0D", "duration_1D", "duration_bidomain"]

# too many values
#columns_to_plot = ["duration_total", "duration_0D", "duration_1D", "duration_bidomain", "durationInitCellml", "durationReadGeometry", "durationOnlyWrite"]

columns_to_extract = columns_to_plot + ["totalUsertime", "durationReadGeometry", "durationSetStiffnessMatrix", 
  "durationOnlyWrite", "durationAssembleBoundaryConditions", "durationInitCellml", "durationComputeMappingBetweenMeshes",
   "durationMap", "memoryResidentSet","duration_transfer_01D"]

column_shortnames = {
  "totalUsertime": "total",
  "duration_total": "computation",
  "duration_0D": "0D",
  "duration_1D": "1D",
  "duration_init": "duration_init",
  "duration_bidomain": "bidomain",
  "durationAssembleBoundaryConditions": "initBC",
  "durationSetStiffnessMatrix": "stiffness",
  "durationComputeMappingBetweenMeshes": "compMap",
  "durationMap": "map",
  "durationReadGeometry": "read",
  "durationOnlyWrite": "write",
  "durationInitCellml": "initCell",
  "memoryResidentSet": "mem",
  "duration_transfer": "transfer",
}

# column_shortnames.values()
ordered_values = ['n', "total", '0D', '1D', "bidomain", "computation", 'stiffness', 'initCell', 'initBC', 'read', 'write', 'compMap', 'map', "mem"]

df_cray = df[df['version'].str.contains("Cray Cray")]
df_gnu = df[df['version'].str.contains("GCC 8")]


print(df_gnu.groupby(['nRanks'])['activationSolver_solverType'])

df = df_gnu

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

 
def plot(df, title, columns_to_plot, mylabels=None):
  means = df.groupby(['nRanks']).mean()
  if len(means) == 0:
    return
  
  #linestyle_cycler = cycler.cycler('linestyle',['-','--',':','-.'])
  # (cycler.cycler('color', ["k",(0.3,0.3,0.7),(0.7,0.7,1.0), "r", "y"])+cycler.cycler('linestyle', ['-', '--', ':', '-', '-'])))
  plt.rc('axes', prop_cycle=(cycler('color', ['k', (0.6,0.6,1.0), (0.1,0.1,0.6), 'r', 'y', (1.0,0.7,0.2)]) +
                             cycler('linestyle', ['-', '--', '-.', '-', '-', '-'])))
  #plt.rc('axes', prop_cycle=("cycler('color', 'rgb') + cycler('linestyle',  ['-', '-', ':'])"))
    
  errors = df.groupby(['nRanks']).std()
  
  ax = means.plot.bar(figsize=(13,7), y=columns_to_plot, title = "Run with 50.000 ranks", logy=True, yerr=errors)
  ax = plt.gca()
  ax.set_ylabel('runtime [s]')
  ax.set_xlabel("")
  ax.set_title(title)
  if mylabels is not None:
    plt.subplots_adjust(right=0.66, top=0.94, bottom=0.18)
    ax.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0., frameon=False, labels=mylabels)  
  
  if show_plots:
    plt.show()
  else:
    #plt.tight_layout()
    plt.savefig("{}.pdf".format(title.replace(" ", "")))
    plt.savefig("{}.png".format(title.replace(" ", "")))
 
def print_table(df, title, columns_to_plot, mylabels=None):

  print("")
  print("------------")
  print(title)
  print(df.groupby(['nRanks']).\
    agg(merge_dicts(x,{'n': np.size, "memoryResidentSet": lambda v: "{:.3f} GB".format(np.mean(v)/(1024.**3))})).rename(columns=column_shortnames)[ordered_values])
    
  # write plot to file
  plot(df, title, columns_to_plot, mylabels)

#mylabels = ["bad placement", "optimal placement"]
mylabels=None
columns_to_plot = ["totalUsertime", "duration_init", "duration_bidomain", "duration_1D", "duration_0D"]
#columns_to_plot = ["totalUsertime", "duration_init", "durationReadGeometry", "durationOnlyWrite", "duration_1D", "duration_0D"]
#mylabels = ["total", "read geometry files", "write VTK files", "1D model", "0D model", ]
mylabels = ["total", "initialization", "3D model", "1D model", "0D model"]

print_table(df, "Run with 50.000 ranks", columns_to_plot, mylabels)

#print_table(df_cg, "CG", columns_to_plot, mylabels)
plt.show()
