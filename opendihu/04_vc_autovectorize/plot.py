#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import numpy as np
import subprocess
import datetime
import time
from cycler import cycler
import os
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401 unused import

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import itertools

if(len(sys.argv)) >= 2:
  input_filename = sys.argv[1]
else:
  input_filename = "log.csv"
print("filename: {}".format(input_filename))

show_plots = True
#if len(sys.argv) > 1:
#  show_plots = False;

n_columns = 60

plt.rcParams.update({'font.size': 16})
plt.rcParams['lines.linewidth'] = 2

def load_df(input_filename):

  # determine number of columns
  line_no = 0
  header_lines = []
  
  with open(input_filename) as f:
    line = f.readline()
    print("line_no: {}, line: [{}]".format(line_no, line))
    
    if '\n' in line:
      line = line.replace('\n','')
    if "~nDofsFiber0" in line:
      pos = line.find("~nDofsFiber0")
      column_names = line[0:pos].split(";")
      column_names = filter(None, column_names)
      header_lines.append([line_no, column_names])
      print("header_line")
    else:
      column_names = line.split(";")
      column_names = filter(None, column_names)
      n_columns = len(column_names)
    line_no += 1

  print("parsed total of {} header_lines:".format(len(header_lines)))
  print(header_lines)

  # set number of rows of chunks
  last_line_no = 0
  for i in range(1,len(header_lines)):
    current_line_no = header_lines[i][0]
    header_lines[i-1].append(current_line_no - last_line_no)
    
    last_line_no = current_line_no
  header_lines[-1].append(line_no - last_line_no)

  df = None

  # header_lines is a list of [[start_row_no,[column0,column1,column2,...],n_rows],[...],...]
  for start_row, column_names, n_rows in header_lines:
    
    n_columns = len(column_names)
    
    # load data frame
    current_df = pd.read_csv(input_filename, sep=';', warn_bad_lines=True, comment="#", names=column_names, usecols=range(n_columns), skiprows=start_row, nrows=n_rows, engine='python')
    print("")
    print("read current_df, start_row: {}, n_rows: {}, n_columns: {} ".format(start_row,n_rows,n_columns))
    current_df.info()
    print(current_df.head())
    
    if df is None:
      df = current_df
    else:
      df = df.merge(current_df)

  return df

df = load_df(input_filename)

# Info about the data structure
print("df info:")
df.info()
#print(df.head())

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

columns_to_plot = ["duration_0D", "duration_1D"]
df_all = df

df_vc = df_all[df_all["scenario_name"] == "fast_fibers"]
df_autovec = df_all[df_all["scenario_name"] == "fibers_emg"]

print(df_vc["duration_0D"])

fig = plt.figure()
ax = plt.axes()
fig=plt.figure()
ax2=plt.axes()

df_plot=pd.DataFrame()
marker = itertools.cycle(('o', '+', 's','^','d')) 
color=itertools.cycle(('r','r','r','r','r','g','g','g','g','g','b','b','b','b','b'))

for df in [df_vc, df_autovec]:
  means = df.groupby(['scenario_name']).mean()  
  errors = df.groupby(['scenario_name']).std()
  means.plot(ax=ax, y="duration_0D",logx=True, logy=True, marker=next(marker),yerr=errors)  
  #means.plot(ax=ax2, y="duration_1D",logx=True, logy=True, marker=next(marker)) 
     
  #for elem in [100,200,500,1000,1480]:
    #df_plot=df_solver[df_solver['~nElements']== elem]
    #means = df_plot.groupby(['nRanks']).mean()
    #errors = df_plot.groupby(['nRanks']).std()
    ##print(means)
    #means.plot(ax=ax,y="durationSolve_implicitSolver",logx=False, logy=True, color=next(color), marker=next(marker), yerr=errors)


#  if df_plot.empty:
#    df_plot=means
#  else:
#    df_plot=pd.DataFrame.append(df_plot,means)
      
ax.grid(which='minor')
#ax.legend(["lu", "cg","gmres", "gamg", "cg_boomeramg"])
#ax.legend(["lu", "cg","gamg"])
ax.legend(["lu", "cg","gmres","gamg"])
ax.set_xlabel("Elements")
ax.set_ylabel("Duration (s)")
#ax.legend(["lu-100","lu-200","lu-500","lu-1000","lu-1480","cg-100", "cg-200", "cg-500", "cg-1000", "cg-1480", "gamg-100", "gamg-200", "gamg-500", "gamg-1000", "gamg-1480"])

#ax2.legend(["lu", "cg", "gamg"])
ax2.legend(["lu", "cg","gmres", "gamg"])
ax2.set_xlabel("Elements")
ax2.set_ylabel("Iterations")
ax2.grid(which='minor')
plt.show()

#df_plot.info()
#df_plot.describe()
#print(df_plot)

#df_plot.plot(y="durationSolve_implicitSolver",logx=True, logy=True, marker='o')
#plt.show()
