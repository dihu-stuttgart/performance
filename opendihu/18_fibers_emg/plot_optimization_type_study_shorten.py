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
import pandas_utility

input_filename = "logs/log_optimization_type_study_shorten.csv"
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
if not matplotlib.is_interactive() or not show_plots:
  matplotlib.use('Agg')

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

# define global plotting parameters
plt.rcParams.update({'font.size': 16})
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
df = pandas_utility.load_df(input_filename)
#df = pd.read_csv(input_filename, sep=';', error_bad_lines=False, warn_bad_lines=True, comment="#", header=None, names=column_names, usecols=range(n_columns), mangle_dupe_cols=True)

# filter data
#df = df.loc[df['endTime'] == 1]

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

def plot(df, title, columns_to_plot, mylabels=None):
  means = df.groupby(['scenarioName']).mean()
  if len(means) == 0:
    return
  
  errors = df.groupby(['scenarioName']).std()
  
  
  fig, ax = plt.subplots(figsize=(11,6))
  
  width = 0.35    # width of the bars
  ind = range(12)  # indices
  
  means["duration_0D"] = means["duration_0D"].fillna(0)
  errors["duration_0D"] = errors["duration_0D"].fillna(0)
  means["duration_1D"] = means["duration_1D"].fillna(0)
  errors["duration_1D"] = errors["duration_1D"].fillna(0)
  
  order = [4,5,6,7,2,3,8,11,9,10,0,1]
  means = means.iloc[order]
  errors = errors.iloc[order]
  
  
  p1 = ax.barh(ind, means["duration_0D"], width, label="0D solver", color="y", zorder=1)
  p2 = ax.barh(ind, means["duration_1D"], width, left=means["duration_0D"], label="1D solver", color="r", zorder=1)
  p3 = ax.barh(ind, means["duration_bidomain"], width, left=means["duration_0D"]+means["duration_1D"], label='3D solver', color="b", zorder=1)
  p4 = ax.barh(ind, means["duration_total"]-means["duration_bidomain"]-means["duration_1D"]-means["duration_0D"], width, 
    left=means["duration_0D"]+means["duration_1D"]+means["duration_bidomain"], label='total computation', color="gray", zorder=1)
  
  
  for i,p in enumerate(p4):

    duration = (float)(means["duration_total"].iloc[i])

    # Center the text vertically in the bar
    yloc = p.get_y() + p.get_height() / 2
    xloc = 410
    clr = 'black'
    align = 'right'
    label = ax.annotate(
        "{:.1f} s".format(duration), xy=(width, yloc), xytext=(xloc, 0),
        textcoords="offset points",
        horizontalalignment=align, verticalalignment='center',
        color=clr, clip_on=True)
    #rect_labels.append(label)

  
  ax.xaxis.grid(True,which='both')
  ax.set_axisbelow(True)
  scenario_names = list(means.index)
  ax.set_ylabel('Scenario')
  ax.set_xlabel('Runtime [s]')
  ax.set_xlim(0,10000)
  ax.set_yticks(ind)
  ax.set_yticklabels(scenario_names)
  ax.invert_yaxis()  # labels read top-to-bottom
  #ax.set_title(title)
  plt.subplots_adjust(left=0.19,bottom=0.15,right=0.71)
  plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0., frameon=False)

  plot_filename = "fibers_emg_study_shorten.pdf"
  plt.savefig(plot_filename)
  print("Created \"{}\".".format(plot_filename))
  
  if show_plots:
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
}

# define columns for table and plot (long names)
columns_to_print = ["meta_partitioning", "totalUsertime", "duration_total", "duration_0D", "duration_1D", "duration_bidomain", "duration_multidomain", "duration_mechanics", "duration_init", "durationOnlyWrite", "memoryResidentSet", "n"]
columns_to_plot = ["duration_total", "duration_init", "durationOnlyWrite", "duration_0D", "duration_1D", "duration_bidomain", "duration_multidomain", "duration_mechanics"]

plot_labels = ["total", "initialization", "write VTK files", "0D model", "1D model", "3D model"]

title = input_filename
output(df, title, columns_to_print, columns_to_plot, plot_labels)

