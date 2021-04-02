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

input_filename = "logs/log.csv"
list_columns = False
show_plots = True
scenario_name = None

# parse arguments
next_is_scenario_name = False
for arg in sys.argv[1:]:
  if next_is_scenario_name:
    scenario_name = arg
    continue
  next_is_scenario_name = False
  
  if ".csv" in arg:
    input_filename = arg
  elif "-s" in arg:
    next_is_scenario_name = True
  else:
    if "l" in arg:
      list_columns = True
    if "p" in arg:
      show_plots = True
  

if len(sys.argv) == 1:
  print("usage: {} [-l] [-p] [-s <scenario_name>] [<input_filename>]".format(sys.argv[0]))
  print("   -l: list column names")
  print("   -p: show plot window (else create pdf plot)")
  print("   -s: only filter scenario name")
  print("   <input_filename> log file, default: logs/log.csv")
  print("")


# load matplotlib
import matplotlib
#if not matplotlib.is_interactive() or not show_plots:
#  matplotlib.use('Agg')

import matplotlib.pyplot as plt
import matplotlib.transforms as transforms
import pandas as pd
import numpy as np

# define global plotting parameters
plt.rcParams.update({'font.size': 14})
plt.rcParams['lines.linewidth'] = 2

def remove_duplicates(seq):
  seen = set()
  seen_add = seen.add
  return [x for x in seq if not (x in seen or seen_add(x))]

# determine columns to load from the log file
with open(input_filename) as f:
  line = f.readline()
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

  seen = set()
  column_names2 = []
  for x in list(column_names):
    if x not in seen:
      seen.add(x)
      column_names2.append(x)
    else:
      print("Note: column \"{}\" appears multiple times".format(x))
      while x in seen:
        x = "{}_2".format(x)
      seen.add(x)
      column_names2.append(x)

  column_names = column_names2
  n_columns = len(column_names)
  
if list_columns:
	print("File {} contains {} colums: {}".format(input_filename, n_columns, column_names))

# load data frame
df = pd.read_csv(input_filename, sep=';', error_bad_lines=False, warn_bad_lines=True, comment="#", header=None, names=column_names, usecols=range(n_columns), mangle_dupe_cols=True, low_memory=False)

# filter data
if scenario_name is not None:
  print("Using scenario {}".format(scenario_name))
  df = df.loc[df['scenarioName'] == scenario_name]

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


scaling_factor = 1000 / df.iloc[0]["endTime"]
print(scaling_factor)
df["duration_bidomain"] *= scaling_factor
df["duration_1D"] *= scaling_factor
df["duration_0D"] *= scaling_factor
df['duration_total'] *= scaling_factor

# Info about the data structure
#print("df info:")
#df.info()
#print(df.head())

# set options for console display
pd.set_option('display.max_rows', 500)
pd.set_option('display.max_columns', 500)
pd.set_option('display.width', 1000)

def merge_dicts(x, y):
  z = x.copy()   # start with x's keys and values
  z.update(y)    # modifies z with y's keys and values & returns None
  return z

def plot(df, title, columns_to_plot, mylabels=None):
  means = df.groupby(['nRanks']).mean()
  if len(means) == 0:
    return
  
  #linestyle_cycler = cycler.cycler('linestyle',['-','--',':','-.'])
  # (cycler.cycler('color', ["k",(0.3,0.3,0.7),(0.7,0.7,1.0), "r", "y"])+cycler.cycler('linestyle', ['-', '--', ':', '-', '-'])))
  plt.rc('axes', prop_cycle=(cycler('color', ['k', 'b', 'y', 'r', (0.7,0.7,1.0)]) +
                             cycler('linestyle', ['-', ':',  '--', '-.', '-'])))
  #plt.rc('axes', prop_cycle=("cycler('color', 'rgb') + cycler('linestyle',  ['-', '-', ':'])"))
    
  errors = df.groupby(['nRanks']).std()
  ax = means.plot(figsize=(7,6), y=columns_to_plot, logx=True, logy=True, yerr=errors, marker='o')
  
  rank_nos = sorted(list(set(df["nRanks"])))
  ax = plt.gca()
  ax.set_xticks(rank_nos)
  xticklabels = []
  for rank in rank_nos:
    if rank == 7744:
      xticklabels.append("\n7744  ")
    elif rank == 26912:
      xticklabels.append("\n  26912")
    else:
      xticklabels.append(str(rank))
      
  ax.set_xticklabels(["" for _ in rank_nos])
  
  # set text for number of fibers
  n_fibers = {
    4:    49,
    18:   169,
    64:   625,
    144:  1369,
    448:  4489,
    1152: 11881,
    3600: 34969,
    7744:  76729,
    18432: 182329,
    26912: 273529,
    51200: 273529,
  }
  
    
  # the x coords of this transformation are data, and the
  # y coord are axes
  trans = transforms.blended_transform_factory(ax.transData, ax.transAxes)
  
  for i,ranks in enumerate(rank_nos):
    string_ranks = ranks
    string_fibers = n_fibers[ranks]
    
    ypos_ranks = -0.08
    ypos_fibers = -0.14
    
    xpos_ranks = ranks
    xpos_fibers = ranks
    
    # adjust y pos
    if ranks == 7744 or ranks == 26912 or ranks == 1152:
      ypos_ranks -= 0.14
      ypos_fibers -= 0.14
    
    # adjust x pos
    if ranks == 7744:
      ranks -= 2000
    if ranks == 144:
      ranks += 20
    
    # number of ranks
    ax.text(ranks, ypos_ranks, s=string_ranks, color="black", ha="center", transform=trans)
    
    # number of fibers
    ax.text(ranks, ypos_fibers, s=string_fibers, color="grey", ha="center", transform=trans)
  
  ax.text(0.5, -0.38, "Number of processes", color="black", ha="center", transform = ax.transAxes)
  ax.text(0.5, -0.44, "Number of fibers", color="grey", ha="center", transform = ax.transAxes)
  
  ax.grid(which='major')
  ax.set_ylabel('Runtime [s]')
  ax.set_xlabel('')
  if mylabels is not None:
    ax.legend(labels=mylabels, loc="upper left", bbox_to_anchor=(1.0,1.0), frameon=False)
    #plt.legend(loc="lower left", bbox_to_anchor=(0,1.0), frameon=False)
    plt.subplots_adjust(right=0.68,bottom=0.3)

  plot_filename = "weak_scaling.pdf"
  #plot_filename = "weak_scaling_cg1e-5.pdf"
  plt.savefig(plot_filename)
  plot_filename_png = plot_filename.replace(".pdf",".png")
  plt.savefig(plot_filename_png)
  print("Created \"{}\" and \"{}\".".format(plot_filename,plot_filename_png))
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
  print(df.groupby(['scenarioName','nRanks']).agg(items).rename(columns = column_shortnames)[table_shortnames])
  print("-"*120)

  # create plot
  plot(df, title, columns_to_plot, plot_labels)

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
  "durationAssembleBoundaryConditions": "initBC",
  "durationSetStiffnessMatrix": "stiffness",
  "durationComputeMappingBetweenMeshes": "compMap",
  "durationMap": "map",
  "durationReadGeometry": "read",
  "durationOnlyWrite": "write",
  "durationInitCellml": "initCell",
  "memoryResidentSet": "mem",
  "meta_partitioning": "subdomains",
}

# define columns for table and plot (long names)
columns_to_print = ["meta_partitioning", "totalUsertime", "duration_total", "duration_0D", "duration_1D", "duration_bidomain", "duration_init", "durationOnlyWrite", "memoryResidentSet", "n"]
columns_to_plot = ["duration_total", "duration_bidomain", "duration_0D", "duration_1D", "duration_init"]

plot_labels = ["total", "3D model", "0D model", "1D model", "initialization"]

title = input_filename
output(df, title, columns_to_print, columns_to_plot, plot_labels)

