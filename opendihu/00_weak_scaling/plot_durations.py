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
input_filename = "logs/log.csv"

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
  
  # compute framework overhead
  #df['duration_overhead'] = df['duration_total'] - df['duration_0D'] - df['duration_1D'] - df['duration_bidomain']
  df['duration_overhead'] = df['duration_total'] - df['duration_subdomains_xy'] - df['duration_bidomain']
  df['duration_overhead_monodomain'] = df['duration_monodomain'] - df['duration_0D'] - df['duration_1D']
  
  df['duration_1gmres'] = df['duration_bidomain'] / df['nIterations_activationSolver']
  #? df['duration_bidomain'] = 10000*df['duration_1gmres']
  
  return df

df = load_df(input_filename)

# Info about the data structure
print("df info:")
df.info()
print(df.head())




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
 
def print_table(df, title, filename, columns_to_print, column_shortnames, ordered_values=None):

  x = {column_name: np.mean for column_name in columns_to_print}

  # add columns with no short name to column_shortnames dict
  for column in columns_to_print:
    if column not in column_shortnames:
      column_shortnames[column] = column

  # create ordered_values
  if ordered_values is None:
    ordered_values = columns_to_print
    
    short_ordered_values = []
    for long_value in ordered_values:
      if long_value in column_shortnames:
        short_ordered_values.append(column_shortnames[long_value])
      else:
        short_ordered_values.append(long_value)
    
    ordered_values = short_ordered_values
    
    print("ordered_values: ",ordered_values)
    
  print("")
  print("------------")
  print(title)
  print(filename)
  print(df.groupby(['nRanks']).\
    agg(merge_dicts(x,{'n': np.size, "memoryResidentSet": lambda v: "{:.3f} GB".format(np.mean(v)/(1024.**3))})).rename(columns=column_shortnames)[ordered_values])

#############################
# weak scaling

df_weak_scaling = df[df['scenarioName'].str.contains("weak_scaling")]

# plot
#columns_to_plot = ["totalUsertime", "duration_init", "duration_bidomain", "duration_1D", "duration_0D", "duration_overhead", "duration_overhead_monodomain", "durationComputeMappingBetweenMeshes"]
mylabels = ["total", "initialization", "3D model", "1D model", "0D model", "framework overhead total", "framework overhead monodomain", "map 1D-3D", "initialize mapping"]

columns_to_plot = ["totalUsertime", "duration_init", "durationOnlyWrite", "duration_bidomain", "duration_1D", "duration_0D", "durationComputeMappingBetweenMeshes"]
mylabels = ["total", "initialization", "file output", "3D model", "1D model", "0D model", "map 1D-3D"]

#columns_to_plot = ["totalUsertime", "duration_init", "durationReadGeometry", "durationOnlyWrite", "duration_1D", "duration_0D"]
#mylabels = ["total", "read geometry files", "write VTK files", "1D model", "0D model", ]
colors = ['k', (0.7,0.76,0.7), (0.1,0.1,0.6), 'r', 'y', (0.6,0.6,1.0), 'm', (1.0, 0.5, 0.0), 'c', (0.2,0.4,0.9)]
plot(df_weak_scaling, "", "weak_scaling", columns_to_plot, mylabels, None, colors)

# print table in console
columns_to_print = ["duration_total", "duration_0D", "duration_1D", "duration_bidomain", "totalUsertime", "durationReadGeometry", "durationSetStiffnessMatrix", 
  "durationOnlyWrite", "durationAssembleBoundaryConditions", "durationInitCellml", "durationComputeMappingBetweenMeshes",
   "durationMap", "memoryResidentSet", "nIterations_activationSolver",
   "durationWriteOutput", "duration_overhead", "duration_overhead_monodomain"]

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
  "durationParaview3DInit": "paraview3DInit",
}

print_table(df_weak_scaling, "", "weak_scaling", columns_to_print, column_shortnames)

df1200 = df_weak_scaling[df['nRanks'] == 1200]

# timestamp;hostname;version;nRanks;rankNo;durationAssembleBoundaryConditions;n;durationComputeMappingBetweenMeshes;n;durationInitCellml;n;durationMap;n;durationParaview1D;n;
#durationParaview1DInit;n;durationParaview1DReduction;n;durationParaview1DWrite;n;durationParaview3D;n;durationParaview3DInit;n;durationParaview3DReduction;n;durationParaview3DWrite;n;
#durationParaviewOutput;n;durationReadGeometry;n;durationSetRightHandSide;n;durationSetStiffnessMatrix;n;durationSolve_activationSolver;n;durationSolve_implicitSolver;n;
#durationSolve_potentialFlowSolver;n;durationWriteOutput;n;duration_0D;n;duration_1D;n;duration_bidomain;n;duration_monodomain;n;duration_monodomain_advanceTimeSpan1;n;
#duration_monodomain_advanceTimeSpan2;n;duration_monodomain_transfer12;n;duration_monodomain_transfer21;n;duration_subdomains_xy;n;duration_subdomains_xy_init;n;duration_subdomains_z;n;
#duration_subdomains_z_init;n;duration_total;n;duration_total_advanceTimeSpan1;n;duration_total_advanceTimeSpan2;n;duration_total_transfer12;n;duration_total_transfer21;n;
#activationSolver_preconditionerType;activationSolver_solverType;currentSimulationTime;dt_0D;dt_1D;dt_3D;dt_bidomain;duration_subdomains_xy_n;duration_subdomains_z_n;endTime;
#exit;implicitSolver_preconditionerType;implicitSolver_solverType;memoryData;memoryPage;memoryResidentSet;memoryVirtual;nInstancesComputedGlobally;nIterations_activationSolver;
#nIterations_implicitSolver;nIterations_potentialFlowSolver;potentialFlowSolver_preconditionerType;potentialFlowSolver_solverType;residualNorm_activationSolver;residualNorm_implicitSolver;
#residualNorm_potentialFlowSolver;scenarioName;totalUsertime;~nDofs;~nDofs3Dmesh;~nDofsFiber0;~nElements;~nElements3Dmesh;~nElementsFiber0;~nNodes;~nNodes3Dmesh;
#~nNodesFiber0;nIterationsTotal_activationSolver;nIterationsTotal_implicitSolver;nIterationsTotal_potentialFlowSolver;

columns_to_print = ["duration_monodomain", "duration_monodomain_advanceTimeSpan1", "duration_0D", "duration_monodomain_advanceTimeSpan2", "duration_1D", "durationSolve_implicitSolver", "duration_monodomain_transfer12", "duration_monodomain_transfer21"]
print_table(df1200, "", "0D, 1D durations", columns_to_print, column_shortnames)

columns_to_print = ["duration_total", "duration_total_advanceTimeSpan1", "duration_subdomains_xy", "duration_total_advanceTimeSpan2", "duration_bidomain", "duration_total_transfer12", "duration_total_transfer21", "duration_overhead", "durationMap", "durationComputeMappingBetweenMeshes"]
print_table(df1200, "", "overhead", columns_to_print, column_shortnames)

if show_plots:
  plt.show()
exit()
