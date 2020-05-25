#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# weak scaling on Hazel Hen

import sys, os
import subprocess
import datetime
import time
import numpy as np
import pandas as pd
from cycler import cycler
import subprocess
import pandas_utility

# log files are copied from 00_weak_scaling

input_filename_fast = "log_10.csv"
input_filename_notfast_no_rr = "log_no_rr.csv"
input_filename_notfast = "weak_scaling_paper.csv"
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

# define global plotting parameters
matplotlib.rcdefaults()
plt.rcParams.update({'font.size': 18})
plt.rcParams['lines.linewidth'] = 3

# set options for console display
pd.set_option('display.max_rows', 500)
pd.set_option('display.max_columns', 500)
pd.set_option('display.width', 1000)
pd.set_option('display.max_colwidth', 100)

# filter data
#df = df.loc[df['nIterations_multidomainLinearSolver'] != 0]       # exclude runs where solver diverged (no number of iterations)
#df = df.loc[df['nIterations_multidomainLinearSolver'] < 1000]

# Info about the data structure
#print("df info:")
#df.info()
#print(df.head())

# ------------------------------------------------
# define shortnames for the table, each line is
#  long_name : short_name
column_shortnames = {
  "totalUsertime": "user",
  "duration_total": "total comp.",
  "duration_0D": "0D",
  "duration_1D": "1D",
  #"duration_init": "duration_init",
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
columns_to_print = [
  "meta_partitioning", 
  "totalUsertime", 
  "duration_total",
  "duration_init",  
  "durationOnlyWrite",
  "duration_0D", 
  "duration_1D", 
  "duration_bidomain", 
  "duration_multidomain", 
  "duration_mechanics", 
  "nIterations_multidomainLinearSolver",
  "memoryResidentSet", 
  "n"
]


#######################
# plot fast fibers

if True:
  # load data frame
  df = pandas_utility.load_df(input_filename_fast)
  
  
  df['duration_0D'] = df['duration_0D']*10000
  df['duration_1D'] = df['duration_1D']*10000
  df['duration_bidomain'] = df['duration_bidomain']*100   # 3D bidomain computed every 0.1s
  
  df['duration_transfer_01D'] = df['duration_total_advanceTimeSpan1'] - df['duration_0D'] - df['duration_1D']

  if list_columns:
    print(df.columns)

  title = "Weak scaling"
  columns_to_plot = ["duration_0D", "duration_1D", "duration_bidomain", "duration_init"]
  plot_labels = ["0D model", "1D model", "3D model", "initialization"]

  # print table
  pandas_utility.print_table(df, title, columns_to_print, column_shortnames)

  # plot weak scaling

  # define colors and linestyles
  plt.rc('axes', prop_cycle=(cycler('color', ['y', 'r', (0.1,0.1,0.6), (0.5,0.5,0.5), (1.0,0.7,0.2)]) +
                             cycler('linestyle', [ '-', '-', '-', '--','-'])))
  pandas_utility.plot_weak_scaling(df, title, columns_to_plot, ['nRanks'], plot_labels)

#######################
# new combined data set
df_notfast = pandas_utility.load_df(input_filename_notfast)
df_notfast_no_rr = pandas_utility.load_df(input_filename_notfast_no_rr)
df_fast = pandas_utility.load_df(input_filename_fast)

df_notfast = df_notfast.rename(columns = {"duration_1D": "duration_1D_notfast"})
df_notfast_no_rr = df_notfast_no_rr.rename(columns = {"duration_1D": "duration_1D_notfast_no_rr"})
df_fast = df_fast.rename(columns = {"duration_1D": "duration_1D_fast", "duration_0D": "duration_0D_fast"})


# print tables
pandas_utility.print_table(df_notfast,        "notfast", ["dt_0D", "dt_1D", "endTime", "nIterations_activationSolver"], column_shortnames)
pandas_utility.print_table(df_notfast_no_rr,  "notfast_no_rr", ["dt_0D", "dt_1D", "endTime", "nIterations_activationSolver"], column_shortnames)
pandas_utility.print_table(df_fast,           "fast", ["dt_0D", "dt_1D", "endTime", "nIterations_activationSolver"], column_shortnames)


df = pd.concat([df_fast, df_notfast, df_notfast_no_rr])
df['duration_transfer_01D'] = df['duration_total_advanceTimeSpan1'] - df['duration_0D_fast'] - df['duration_1D_fast']


title = "Comparison of 0D-1D computation schemes"
columns_to_print = [
  "meta_partitioning", 
  "totalUsertime", 
  "duration_total",
  "duration_init",  
  "durationOnlyWrite",
  "duration_0D_fast", 
  "duration_1D_notfast", 
  "duration_1D_notfast_no_rr",
  "duration_1D_fast",
  "duration_bidomain", 
  "n"
]
columns_to_plot = ["duration_1D_notfast_no_rr", "duration_1D_notfast", "duration_1D_fast", "duration_0D_fast", "duration_transfer_01D"]
columns_to_print = ["totalUsertime", "duration_1D_notfast_no_rr", "duration_1D_notfast", "duration_1D_fast", "duration_0D", "mem", "n"]
plot_labels = ["1D model with\n round-robin placement", "1D model with\n optimal placement", "1D model with\n local computation", "0D model", "communication 0D,1D"]

# print table
pandas_utility.print_table(df, title, columns_to_print, column_shortnames)

# plot weak scaling
# define colors and linestyles
plt.rc('axes', prop_cycle=(cycler('color', ['b', '#6d1e91', 'r', 'y', (1.0,0.7,0.2)]) +
                           cycler('linestyle', ['--', '-.', '-', '-', '-'])))
pandas_utility.plot_weak_scaling(df, title, columns_to_plot, ['nRanks'], plot_labels)



if show_plots:
  plt.show()
