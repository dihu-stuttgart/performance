#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
import numpy as np
import matplotlib.pyplot as plt
import csv
import collections
import copy
from sets import Set

# load format package
SCENARIO='cuboid'
#sys.path.insert(0, src_path+"/evaluation")
import format as fo

paper_version = True
paper_no_legend = False

# determine if plots are shown
show_plots = True
if len(sys.argv) >= 2:
  show_plots = False
  
remove_outlier = True
outlier_top = 1
outlier_bottom = 0
  
# read csv file
report_filename = "error.csv"

print "report file: {}".format(report_filename)
data = []
with open(report_filename) as csvfile:
  reader = csv.reader(csvfile, delimiter=';')
  for row in reader:
    if len(row) > 0:
      if '#' not in row[0]:
        data.append(row)

n = len(data)

# 0 {date}
# 1 {hostname}
# 2 {splitting_type}
# 3 {n_0D}
# 4 {n_1D}
# 5 {error}
# 6 {duration_0D}
# 7 {duration_1D}
# 8 {duration_0D_solve}
# 9 {duration_1D_solve}
# 10{duration_total}

#print data
xlist_error = [0.5,0.4,0.3,0.2,0.1, 0.08,0.06,0.04,0.02,0.01,0.008,0.006,0.004,0.002,0.001, 0.0008,0.0006,0.0004,0.0002,0.0001]
ylist_godunov_duration = []
ylist_godunov_duration_n0D = []
ylist_godunov_duration_n1D = []
ylist_strang_duration = []
ylist_strang_duration_n0D = []
ylist_strang_duration_n1D = []

for error in xlist_error:
  
  godunov_duration = -1
  godunov_duration_n0D = 0
  godunov_duration_n1D = 0
  
  strang_duration = -1
  strang_duration_n0D = 0
  strang_duration_n1D = 0
  
  for dataset in data:
    #print "error",dataset[5],error
    if float(dataset[5]) < error:
      
      if int(dataset[2]) == 0:     # godunov
        if float(dataset[6])+float(dataset[7]) < godunov_duration or godunov_duration==-1:
          godunov_duration = float(dataset[6])+float(dataset[7])
          godunov_duration_n0D = float(dataset[3])
          godunov_duration_n1D = float(dataset[4])
      else:
        if float(dataset[6])+float(dataset[7]) < strang_duration or strang_duration==-1:
          strang_duration = float(dataset[6])+float(dataset[7])
          strang_duration_n0D = float(dataset[3])
          strang_duration_n1D = float(dataset[4])
  
  ylist_godunov_duration.append(godunov_duration)
  ylist_godunov_duration_n0D.append(godunov_duration_n0D)
  ylist_godunov_duration_n1D.append(godunov_duration_n1D)
  
  ylist_strang_duration.append(strang_duration)
  ylist_strang_duration_n0D.append(strang_duration_n0D)
  ylist_strang_duration_n1D.append(strang_duration_n1D)
  
#print "xlist_error: ", xlist_error
#print "ylist_godunov_duration:",ylist_godunov_duration
  
###############################################################
#######################################################
#######################################################
# plot runtime
if True:
  plt.rcParams.update({'font.size': 16})
  plt.rcParams['lines.linewidth'] = 3
  plt.rcParams['lines.markersize'] = 8

  output_path = ""

  #caption = "Serial scaling, neon,\n x,y,z=(2,2,2), xi=(xi1,3,3) "
  output_path = ""
  outfile = output_path+SCENARIO+'_timesteps_convergence.png'
  plt.figure("timesteps_convergence (12)", figsize=(12,8))

  output_path = ""
  plotdata = collections.OrderedDict()
  xdata = Set()
  xtickslist = []
  plotkeys = Set()

  plt.plot(xlist_error, ylist_godunov_duration, 'ro-', label='Godunov')
  plt.plot(xlist_error, ylist_strang_duration, 'go-', label='Strang')

  ax = plt.gca()
  ax.set_xscale('log', basey=10) 
  ax.set_yscale('log', basey=10) 
  ax.invert_xaxis()
  #ax.set_xlim([1e3, 3e5])
  #ax.set_xscale('log', basey=2) 
  #ticks = list(np.linspace(10**4, 10**5, 10)) + list(np.linspace(10**5, 10**6, 10))
  #ax.set_xticks(ticks)
  #ax.set_xticklabels([int(i/1000.) for i in ticks])

  if not paper_no_legend:
    plt.subplots_adjust(right=0.58, top=0.84)
    plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0.)

  #ax.set_xticks(np.linspace(000,60000,5))

  plt.xlabel('Error')
  plt.ylabel('Runtime 0D+1D (s)')
  #plt.legend(loc='best')
  plt.grid(which='both')

  if not paper_version:
    plt.title(caption, y=1.1)
    plt.tight_layout()
    
  #plt.tight_layout()
  plt.savefig(outfile)

########################################################
# plot error over number of timesteps
if True:
  xlist_godunov = []
  xlist_strang = []
  ylist_godunov = []
  ylist_strang = []

# 0 {date}
# 1 {hostname}
# 2 {splitting_type}
# 3 {n_0D}
# 4 {n_1D}
# 5 {error}
# 6 {duration_0D}
# 7 {duration_1D}
# 8 {duration_0D_solve}
# 9 {duration_1D_solve}
# 10{duration_total}

  for dataset in data:
    
    if int(dataset[3]) == 2:    # n_0D
      if int(dataset[2]) == 0:     # godunov
        xlist_godunov.append(int(dataset[4]))   # n_1D
        ylist_godunov.append(float(dataset[5])) # error
      
      else: # strang
        xlist_strang.append(int(dataset[4]))   # n_1D
        ylist_strang.append(float(dataset[5])) # error

  zipped = zip(xlist_godunov, ylist_godunov)
  zipped.sort()
  xlist_godunov, ylist_godunov = zip(*zipped)
  
  zipped = zip(xlist_strang, ylist_strang)
  zipped.sort()
  xlist_strang, ylist_strang = zip(*zipped)

  print "xlist_godunov:",xlist_godunov

  plt.rcParams.update({'font.size': 16})
  plt.rcParams['lines.linewidth'] = 3
  plt.rcParams['lines.markersize'] = 8

  output_path = ""

  #caption = "Serial scaling, neon,\n x,y,z=(2,2,2), xi=(xi1,3,3) "
  output_path = ""
  outfile = output_path+SCENARIO+'_timesteps_duration.png'
  plt.figure("timesteps_duration (12)", figsize=(12,8))

  output_path = ""
  plotdata = collections.OrderedDict()
  xdata = Set()
  xtickslist = []
  plotkeys = Set()

  plt.plot(xlist_godunov, ylist_godunov, 'ro-', label='Godunov')
  plt.plot(xlist_strang, ylist_strang, 'go-', label='Strang')

  ax = plt.gca()
  ax.set_xscale('log', basex=2)
  ax.set_yscale('log', basey=2)
  #ax.invert_xaxis()
  #ax.set_xlim([1e3, 3e5])
  #ax.set_xscale('log', basey=2) 
  #ticks = list(np.linspace(10**4, 10**5, 10)) + list(np.linspace(10**5, 10**6, 10))
  #ax.set_xticks(ticks)
  #ax.set_xticklabels([int(i/1000.) for i in ticks])

  if not paper_no_legend:
    plt.subplots_adjust(right=0.58, top=0.84)
    plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0.)

  #ax.set_xticks(np.linspace(000,60000,5))

  plt.xlabel('Number of timesteps')
  plt.ylabel('Error')
  #plt.legend(loc='best')
  plt.grid(which='both')

  if not paper_version:
    plt.title(caption, y=1.1)
    plt.tight_layout()
    
  #plt.tight_layout()
  plt.savefig(outfile)




if show_plots:
  plt.show()
#quit()
