#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# solvers for multidomain with fat

import sys
import numpy as np
import subprocess
import datetime
import time
from cycler import cycler
import os
import pandas_utility

input_filename = "logs/log-combined.csv"
list_columns = False
show_plots = False

# parse arguments
for arg in sys.argv[1:]:
  if ".csv" in arg:
    input_filename = arg
  else:
    if "l" in arg:
      list_columns = True
    if "p" in arg:
      show_plots = True

if len(sys.argv) == 1:
  print("usage: {} [-l] [-p] [<input_filename>]".format(sys.argv[0]))
  print("   -l: list column names")
  print("   -p: show plot window (else create pdf plot)")
  print("   <input_filename> log file, default: logs/log.csv")
  print("")


# load matplotlib
import matplotlib
if not show_plots:
  matplotlib.use('Agg')

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

# define global plotting parameters
matplotlib.rcdefaults()
plt.rcParams.update({'font.size': 16})
plt.rcParams['lines.linewidth'] = 2

df = pandas_utility.load_df(input_filename)

# filter data
if 'nIterations_multidomainLinearSolver' in df:
  df = df.loc[df['nIterations_multidomainLinearSolver'] != 0]       # exclude runs where solver diverged (no number of iterations)
#df = df.loc[df['nIterations_multidomainLinearSolver'] < 1000]

filtered_scenarios = [
    'gmres_none_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse',#      "No preconditioner",
    'gmres_euclid_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse',#    "Euclid",
    'gmres_euclid_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symTrue_lumpFalse',#     "Euclid (symmetric)",
    'gmres_bjacobi_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse',#   "Block jacobi",
    'gmres_bjacobi_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symTrue_lumpFalse',#    "Block jacobi (symmetric)",
    'gmres_sor_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse',#       "Parallel SOR",
    'gmres_sor_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symTrue_lumpFalse',#        "Parallel SOR (symmetric)",
  ]

def filter_function(df):
  try:
    for f in filtered_scenarios:
      if f in df["scenarioName"]:
        return True
  except:
    pass
  return False

df = df[df.apply(lambda x: filter_function(x), axis=1)]

print("n filtered entries: {}".format(len(df.index)))


try:
  df['duration_init'] = df['totalUsertime'] - df['duration_total'] + df['durationParaview3DInit'] + df['durationParaview1DInit']
except:
  df['duration_init'] = 0

# Info about the data structure
#print("df info:")
#df.info()
#print(df.head())

# set options for console display
pd.set_option('display.max_rows', 500)
pd.set_option('display.max_columns', 500)
pd.set_option('display.width', 1000)
pd.set_option('display.max_colwidth', 100)

def merge_dicts(x, y):
  z = x.copy()   # start with x's keys and values
  z.update(y)    # modifies z with y's keys and values & returns None
  return z

def plot(df, items):
  scenario_names = [s for s in df['scenarioName'].unique() if not isinstance(s,float) and not "preonly_lu" in s]
  
  df = df.groupby('scenarioName').agg(items)
  
  lines_runtime = {}
  lines_n_iterations = {}
  
  print("plot df")
  # collect lines for plot
  for scenario_name in scenario_names:
    
    # example for scenario_name:
    # gmres_bjacobi_dt0.001_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse_10mus
    pos = scenario_name.rfind("_")
    
    row_name = scenario_name[0:pos]
    n_mus = (int)(scenario_name[pos+1:scenario_name.find("mus")])
    value = df.loc[scenario_name]["duration_multidomain"]
    n_iterations = (float)(df.loc[scenario_name]["nIterations_multidomainLinearSolver"])
    
    if row_name not in lines_runtime:
      lines_runtime[row_name] = [np.nan,np.nan,np.nan,np.nan,np.nan]
    if row_name not in lines_n_iterations:
      lines_n_iterations[row_name] = [np.nan,np.nan,np.nan,np.nan,np.nan]
      
    #if n_mus == 4: i = 0
    
    if n_mus < 4:
      continue
    
    if n_mus == 4: i = -1
    elif n_mus == 6: i = 0
    elif n_mus == 8: i = 1
    elif n_mus == 10: i = 2
    elif n_mus == 12: i = 3
    i+=1
    print("n_mus={},i={}".format(n_mus,i))
    lines_runtime[row_name][i] = value
    
    if n_iterations != 0:
      lines_n_iterations[row_name][i] = n_iterations
    
  label = {
    'gmres_boomeramg_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse': "BoomerAMG",
    'gmres_boomeramg_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symTrue_lumpFalse':  "BoomerAMG (symmetric)",
    'gmres_euclid_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse':    "Parallel ILU",
    'gmres_euclid_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symTrue_lumpFalse':     "Parallel ILU (symmetric)",
    'gmres_bjacobi_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse':   "Block Jacobi, GMRES",
    'gmres_bjacobi_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symTrue_lumpFalse':    "Block Jacobi, GMRES (symmetric)",
    'gmres_sor_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse':       "Block Jacobi, Gauß-Seidel",
    'gmres_sor_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symTrue_lumpFalse':        "Block Jacobi, Gauß-Seidel (symmetric)", 
    'gmres_pilut_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse':     "Pilut",
    'gmres_pilut_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symTrue_lumpFalse':      "Pilut (symmetric)",
    'gmres_none_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse':      "No preconditioner",
    'gmres_none_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symTrue_lumpFalse':       "No preconditioner (symmetric)",
    'gmres_sor,ilu_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse':   "Block Gauss-Seidel with ILU",
    'gmres_bjacobi,gamg_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse': "Block Jacobi with AMG",
    'gmres_bjacobi,cg-euclid_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse': "Block Jacobi with Euclid",
    'gmres_boomeramg,hypre_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse': 'BoomerAMG w/ coord.',
    'gmres_boomeramg,hypre_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symTrue_lumpFalse': 'BoomerAMG w/ coord (symmetric)',
    'gmres_bjacobi,hypre_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse': 'Block Jacobi + AMG',
  }
  
  #order = sorted(lines.iteritems())
  
  order = [
    'gmres_none_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse',#      "No preconditioner",
    'gmres_pilut_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse',#     "Pilut",
    'gmres_pilut_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symTrue_lumpFalse',#     "Pilut (symmetric)",
    'gmres_boomeramg_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse',# "BoomerAMG",
    'gmres_boomeramg_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symTrue_lumpFalse',#  "BoomerAMG (symmetric)",
    'gmres_bjacobi_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse',#   "Block jacobi",
    'gmres_bjacobi_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symTrue_lumpFalse',#    "Block jacobi (symmetric)",
    'gmres_sor_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse',#       "Block Gauss-Seidel",
    'gmres_sor_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symTrue_lumpFalse',#        "Block Gauss-Seidel (symmetric)",
    'gmres_bjacobi,gamg_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse',# "Block Jacobi with AMG",
    'gmres_bjacobi,cg-euclid_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse', #Block Jacobi with Euclid",
    'gmres_boomeramg,hypre_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse', #'BoomerAMG w/ coord.',
    'gmres_boomeramg,hypre_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symTrue_lumpFalse', #'BoomerAMG w/ coord (symmetric)',
    'gmres_bjacobi,hypre_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse', #'Block Jacobi + AMG',
    'gmres_euclid_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse',#    "Euclid",
    'gmres_euclid_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symTrue_lumpFalse',#     "Euclid (symmetric)",
  ]
  
  mylabels = None
  
  
  #plt.style.use('ggplot')
  prop_cycle = plt.rcParams['axes.prop_cycle']
  colors = prop_cycle.by_key()['color']
  
  #colors = ["r","m","c","b"]
  #linestyle_cycler = cycler.cycler('linestyle',['-','--',':','-.'])
  # (cycler.cycler('color', ["k",(0.3,0.3,0.7),(0.7,0.7,1.0), "r", "y"])+cycler.cycler('linestyle', ['-', '--', ':', '-', '-'])))
  plt.rc('axes', prop_cycle=(cycler('color', [colors[0],colors[1],colors[1],colors[2],colors[2],colors[3],colors[3],colors[4],colors[4],colors[5],colors[5],colors[6],colors[7],colors[8],colors[8],colors[9]]) +
                             cycler('linestyle', ['-', '-', '--', '-', '--', '-', '--',  '-', '--', '-', '--','-','-','-','--','-']) +
                             cycler('marker', ['o', 'o', 'x', 'o', 'x', 'o', 'x', 'o', 'x', 'o', 'x', 'o', 'o', 'o', 'x', 'o'])
                             ))
  #plt.rc('axes', prop_cycle=("cycler('color', 'rgb') + cycler('linestyle',  ['-', '-', ':'])"))
  
  # -------------------------------------
  # combined plot
  fig = plt.figure(figsize=(12,7))
  # iterations
  plt.subplot(2,1,1)
  for name in order:
    
    x_values = [4,6,8,10,12]
    try:
      y_values = lines_n_iterations[name]
    except:
      continue
    
    plt.plot(x_values, y_values, label=label[name])
  
  ax = plt.gca()
  ax.set_yscale('log')
  ax.set_ylim(1e2,2e4)
  ax.grid(which='major')
  ax.set_ylabel('Number of \nGMRES iterations')
  ax.set_xticks([4,6,8,10,12])
  ax.set_xticklabels([])
  
  # legend
  if mylabels is not None:
    ax.legend(labels=mylabels)
  ax.legend(bbox_to_anchor=(1.0, 1.0),frameon=False)
  
  # runtime
  plt.subplot(2,1,2)
  for name in order:
    
    x_values = [4,6,8,10,12]
    try:
      y_values = lines_runtime[name]
    except:
      continue
    
    plt.plot(x_values, y_values, label=label[name])
  
  ax = plt.gca()
  ax.set_yscale('log')
  ax.set_ylim(2e2,2e4)
  ax.grid(which='major')
  ax.set_ylabel('Total Solver\nRuntime [s]')
  
  # x
  ax.set_xticks([4,6,8,10,12])
  ax.set_xticklabels(["4\n24","6\n36","8\n48","10\n60","12\n72"])
  ax.set_xlabel('Number of motor units\nNumber of processes')
    
  fig.subplots_adjust(bottom=0.2, right=0.5, left=0.14)

  plt.savefig("multidomain_solvers_selected.png")
  plt.savefig("multidomain_solvers_selected.pdf")

  plt.show()
 
def output(df, title, columns_to_print, columns_to_plot, plot_labels=None):
  """
  print values to console and produce plot
  """
  columns_to_extract = list(set(columns_to_plot + columns_to_print + ["totalUsertime", "durationReadGeometry", "durationSetStiffnessMatrix", 
    "durationOnlyWrite", "durationAssembleBoundaryConditions", "durationInitCellml", "durationComputeMappingBetweenMeshes",
     "durationMap"]))

  # create auxiliary columns that will be computed
  if not "memoryResidentSet" in df:
    df["memoryResidentSet"] = 0
  df["n"] = 0

  # remove column that are not present in the df
  for column in list(columns_to_extract):
    if column not in df:
      print("Note: remove invalid column {} from columns_to_extract".format(column))
      columns_to_extract.remove(column)
  
  for column in list(columns_to_print):
    if column not in df:
      print("Note: remove invalid column {} from columns_to_print".format(column))
      columns_to_print.remove(column)
  
  for column in list(columns_to_plot):
    if column not in df:
      print("Note: remove column {} from columns_to_plot".format(column))
      columns_to_plot.remove(column)

  # select the captions for the table
  table_shortnames = [column_shortnames[long_name] if long_name in column_shortnames else long_name for long_name in columns_to_print]
  
  # define items to be printed, the columns "n" and "memoryResidentSet" need to be already present in the df
  items = merge_dicts(
    {column_name: lambda v: (np.mean(v) if v.dtype == np.float64 else str(v.iloc[0]) ) for column_name in columns_to_extract},
    {'n': np.size, "memoryResidentSet": lambda v: "{:.3f} GB".format(np.mean(v)/(1024.**3))}
  )

  print("-"*120)
  print(title)
  try:
    print(df.groupby(['scenarioName','nRanks']).agg(items).rename(columns = column_shortnames)[table_shortnames])
  except:
    print("print failed")
  print("-"*120)

  # create plot
  plot(df, items)

# ------------------------------------------------
# define shortnames for the table, each line is
#  long_name : short_name
column_shortnames = {
  "totalUsertime": "user",
  "duration_total": "total comp.",
  "duration_0D": "0D",
  "duration_1D": "1D",
  "duration_init": "duration_init",
  "duration_bidomain": "bidomain",
  "duration_mechanics": "mechanics",
  "duration_multidomain": "multidomain",
  "durationAssembleBoundaryConditions": "initBC",
  "durationSetStiffnessMatrix": "stiffness",
  "durationComputeMappingBetweenMeshes": "compMap",
  "durationMap": "map",
  "durationReadGeometry": "read",
  "durationOnlyWrite": "write",
  "durationInitCellml": "initCell",
  "memoryResidentSet": "mem",
  "meta_partitioning": "subdomains",
  "nIterations_multidomainLinearSolver": "niter",
}

# define columns for table and plot (long names)
columns_to_print = ["meta_partitioning", "totalUsertime", "duration_total", "duration_0D", "duration_1D", "duration_bidomain", "duration_multidomain", "duration_mechanics", "duration_init", "durationOnlyWrite", "nIterations_multidomainLinearSolver", "memoryResidentSet", "n"]
columns_to_plot = ["duration_total", "duration_init", "durationOnlyWrite", "duration_0D", "duration_1D", "duration_bidomain", "duration_multidomain", "duration_mechanics"]

plot_labels = ["total", "initialization", "write VTK files", "0D model", "1D model", "3D model"]

title = input_filename
output(df, title, columns_to_print, columns_to_plot, plot_labels)

