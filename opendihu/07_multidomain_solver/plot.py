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

input_filename = "logs/log.csv"
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

def remove_duplicates(seq):
  seen = set()
  seen_add = seen.add
  return [x for x in seq if not (x in seen or seen_add(x))]

def determine_column_names(line):
  if "~nDofs" in line:
    pos = line.find("~nDofs")
    line = line[0:pos]
  column_names = list(line.split(";"))

  # rename "n" columns 
  for i, column_name in enumerate(column_names):
    if column_name == "n":
      column_names[i] = "{}_n".format(column_names[i-1])

  while "" in column_names:
    column_names.remove("")

  # remove duplicates
  seen = set()
  column_names2 = []
  for x in list(column_names):
    if x not in seen:
      seen.add(x)
      column_names2.append(x)
    else:
      print("  Note: column \"{}\" appears multiple times".format(x))
      while x in seen:
        x = "{}_2".format(x)
      seen.add(x)
      column_names2.append(x)

  column_names = column_names2
  return column_names
  n_columns = len(column_names)

# determine columns to load from the log file
with open(input_filename) as f:
  
  # separate lines of file in blocks for a single scenario
  scenario_blocks = []
  current_lines = []
  column_names = None
  for line in f:
    if "~nDofs" in line:
      if current_lines != []:
        scenario_blocks.append(current_lines)
      current_lines = []
    current_lines.append(line)
    
  print("File \"{}\" contains data from {} runs".format(input_filename,len(scenario_blocks)))
    
  # loop over scenario blocks
  df_blocks = []
  for scenario_block in scenario_blocks:
    if "~nDofs" in scenario_block[0]:
      column_names = determine_column_names(scenario_block[0])
      n_columns = len(column_names)
      print("parse block with {} columns".format(n_columns))
      with open("a","w") as fout:
        for line in scenario_block:
          fout.write(line)
              
    # load data frame
    df_block = pd.read_csv("a", sep=';', error_bad_lines=False, warn_bad_lines=True, comment="#", header=None, names=column_names, usecols=range(n_columns), mangle_dupe_cols=True)
    df_blocks.append(df_block)
  
if list_columns:
	print("File {} contains {} colums: {}".format(input_filename, n_columns, column_names))

# concat the blocks of all scenarios
df = pd.concat(df_blocks)

# load data frame
#df = pd.read_csv(input_filename, sep=';', error_bad_lines=False, warn_bad_lines=True, comment="#", header=None, names=column_names, usecols=range(n_columns), mangle_dupe_cols=True)

# filter data
df = df.loc[df['nIterations_multidomainLinearSolver'] != 0]       # exclude runs where solver diverged (no number of iterations)
#df = df.loc[df['nIterations_multidomainLinearSolver'] < 1000]

if not list_columns:
  print("File {} contains {} rows and {} colums.".format(input_filename, len(df.index), n_columns))

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
  
  print(scenario_names)
  df = df.groupby('scenarioName').agg(items)
  
  lines_runtime = {}
  lines_n_iterations = {}
  
  print("plot df")
  # collect lines for plot
  for scenario_name in scenario_names:
    
    print("scenario_name: {}".format(scenario_name))
    
    # example for scenario_name:
    # gmres_bjacobi_dt0.001_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse_10mus
    pos = scenario_name.rfind("_")
    
    row_name = scenario_name[0:pos]
    n_mus = (int)(scenario_name[pos+1:scenario_name.find("mus")])
    value = df.loc[scenario_name]["duration_multidomain"]
    n_iterations = (float)(df.loc[scenario_name]["nIterations_multidomainLinearSolver"])
    
    if row_name not in lines_runtime:
      lines_runtime[row_name] = [np.nan,np.nan,np.nan,np.nan]
    if row_name not in lines_n_iterations:
      lines_n_iterations[row_name] = [np.nan,np.nan,np.nan,np.nan]
      
    #if n_mus == 4: i = 0
    if n_mus == 6: i = 0
    elif n_mus == 8: i = 1
    elif n_mus == 10: i = 2
    elif n_mus == 12: i = 3
    lines_runtime[row_name][i] = value
    
    print(n_iterations)
    if n_iterations != 0:
      lines_n_iterations[row_name][i] = n_iterations
    
  print("lines")
  print(lines_runtime.keys())
  label = {
    'gmres_boomeramg_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse': "BoomerAMG",
    'gmres_boomeramg_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symTrue_lumpFalse':  "BoomerAMG (symmetric)",
    'gmres_euclid_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse':    "Euclid",
    'gmres_euclid_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symTrue_lumpFalse':     "Euclid (symmetric)",
    'gmres_bjacobi_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse':   "Block jacobi",
    'gmres_bjacobi_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symTrue_lumpFalse':    "Block jacobi (symmetric)",
    'gmres_sor_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse':       "Block Gauss-Seidel",
    'gmres_sor_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symTrue_lumpFalse':        "Block Gauss-Seidel (symmetric)", 
    'gmres_pilut_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse':     "Pilut",
    'gmres_pilut_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symTrue_lumpFalse':      "Pilut (symmetric)",
    'gmres_none_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse':      "No preconditioner",
    'gmres_none_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symTrue_lumpFalse':       "No preconditioner (symmetric)"
  }
  
  #order = sorted(lines.iteritems())
  
  order = [
    'gmres_none_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse',#      "No preconditioner",
    'gmres_pilut_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse',#     "Pilut",
    'gmres_pilut_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symTrue_lumpFalse',#     "Pilut (symmetric)",
    'gmres_boomeramg_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse',# "BoomerAMG",
    'gmres_boomeramg_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symTrue_lumpFalse',#  "BoomerAMG (symmetric)",
    'gmres_euclid_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse',#    "Euclid",
    'gmres_euclid_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symTrue_lumpFalse',#     "Euclid (symmetric)",
    'gmres_bjacobi_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse',#   "Block jacobi",
    'gmres_bjacobi_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symTrue_lumpFalse',#    "Block jacobi (symmetric)",
    'gmres_sor_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symFalse_lumpFalse',#       "Block Gauss-Seidel",
    'gmres_sor_dt0.0005_atol1e-15_rtol1e-15_theta1.0_symTrue_lumpFalse',#        "Block Gauss-Seidel (symmetric)", 
  ]
  
  mylabels = None
  
  
  #plt.style.use('ggplot')
  prop_cycle = plt.rcParams['axes.prop_cycle']
  colors = prop_cycle.by_key()['color']
  
  #colors = ["r","m","c","b"]
  #linestyle_cycler = cycler.cycler('linestyle',['-','--',':','-.'])
  # (cycler.cycler('color', ["k",(0.3,0.3,0.7),(0.7,0.7,1.0), "r", "y"])+cycler.cycler('linestyle', ['-', '--', ':', '-', '-'])))
  plt.rc('axes', prop_cycle=(cycler('color', [colors[0],colors[1],colors[1],colors[2],colors[2],colors[3],colors[3],colors[4],colors[4],colors[5],colors[5]]) +
                             cycler('linestyle', ['-', '-', '--', '-', '--', '-', '--',  '-', '--', '-', '--']) +
                             cycler('marker', ['o', 'o', 'x', 'o', 'x', 'o', 'x', 'o', 'x', 'o', 'x'])
                             ))
  #plt.rc('axes', prop_cycle=("cycler('color', 'rgb') + cycler('linestyle',  ['-', '-', ':'])"))
  
  # -------------------------------------
  # plot runtime
  fig = plt.figure(figsize=(12,5))
  for name in order:
    
    x_values = [6,8,10,12]
    y_values = lines_runtime[name]
    
    print(label[name])
    
    plt.plot(x_values, y_values, label=label[name])
  
  ax = plt.gca()
  ax.set_xticks([6,8,10,12])
  ax.set_xticklabels(["6\n36","8\n48","10\n60","12\n72"])
  ax.set_yscale('log')
  ax.grid(which='major')
  ax.set_xlabel('number of motor units\nnumber of processes')
  ax.set_ylabel('runtime of solver [s]')
  if mylabels is not None:
    ax.legend(labels=mylabels)
  ax.legend(bbox_to_anchor=(1.0, 1.0))
    
  fig.subplots_adjust(bottom=0.2, right=0.7)
  
  if show_plots:
    pass
    #plt.show()
  else:
    plt.tight_layout()
    plot_filename = "{}.pdf".format(title.replace(" ", "").replace("/", ""))
    plt.savefig(plot_filename)
    print("Created \"{}\".".format(plot_filename))
   
  # -------------------------------------
  # plot number of iterations
  fig = plt.figure(figsize=(12,5))
  for name in order:
    
    x_values = [6,8,10,12]
    y_values = lines_n_iterations[name]
    print(name,y_values)
    
    plt.plot(x_values, y_values, label=label[name])
  
  ax = plt.gca()
  ax.set_xticks([6,8,10,12])
  ax.set_xticklabels(["6\n36","8\n48","10\n60","12\n72"])
  ax.set_yscale('log')
  ax.grid(which='major')
  ax.set_xlabel('number of motor units\nnumber of processes')
  ax.set_ylabel('number of iterations')
  if mylabels is not None:
    ax.legend(labels=mylabels)
  ax.legend(bbox_to_anchor=(1.0, 1.0))
    
  fig.subplots_adjust(bottom=0.2, right=0.7)
  
  if show_plots:
    plt.show()
  else:
    plt.tight_layout()
    plot_filename = "{}.pdf".format(title.replace(" ", "").replace("/", ""))
    plt.savefig(plot_filename)
    print("Created \"{}\".".format(plot_filename))
 
 
 
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
  print(df.groupby(['scenarioName','nRanks']).agg(items).rename(columns = column_shortnames)[table_shortnames])
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

