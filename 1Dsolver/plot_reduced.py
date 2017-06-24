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

# determine if plots are shown
show_plots = True
if len(sys.argv) >= 2:
  show_plots = False
  
remove_outlier = True
outlier_top = 1
outlier_bottom = 0
  
# read csv file
#report_filename = "serial_scaling_solvers.csv"
report_filename = "duration.00000.csv"


caption = u'Runtime over problem size'
#caption = u'Weak scaling, cuboid muscle, helium'
#caption = u'Weak scaling, cuboid muscle, bwunicluster'

print "report file: {}".format(report_filename)
data = []
with open(report_filename) as csvfile:
  reader = csv.reader(csvfile, delimiter=';')
  for row in reader:
    if len(row) > 0:
      if '#' not in row[0]:
        data.append(row)

n = len(data)

def getCol(colno):
  cols = []
  for i in range(len(data)):
    cols.append(data[i][colno])
  return cols  
  
def isfloat(value):
  try:
    float(value)
    return True
  except ValueError:
    return False
    
def isint(value):
  try:
    int(value)
    return True
  except ValueError:
    return False
    
# 0  Stamp
# 1  Host
# 2  NProc
# 3  X
# 4  Y
# 5  Z
# 6  F
# 7  Total FE
# 8  Total M
# 9  End Time
# 10 Dur. Init
# 11 Stretch Sim
# 12 Int. Init
# 13 Main Sim
# 14 Total
# 15 Total (User)
# 16 Total (System)
# 17 ODE
# 18 Parabolic
# 19 FE
# 20 FE before Main Sim
# 21 memory consumption after simulation
# 22 memory consumption at shutdown
# 23 Parabolic reason
# 24 Newton reason
# 25 parabolic n. iter
# 26 min
# 27 max
# 28 newton n. iter
# 29 min
# 30 max 
descriptions = {
   0:  "Stamp",
   1:  "Host",
   2:  "NProc",
   3:  "X",
   4:  "Y",
   5:  "Z",
   6:  "F",
   7:  "Total FE",
   8:  "Total M",
   9:  "End Time",
  10:  "Dur. Init",
  11:  "Stretch Sim",
  12:  "Int. Init",
  13:  "Main Sim",
  14:  "Total",
  15:  "Total (User)",
  16:  "Total (System) ",
  17:  "ODE",
  18:  "Parabolic",
  19:  "FE",
  20:  "FE before Main Sim",
  21:  "Mem. Consumption after 1st timestep",
  22:  "Memory Consumption At End ",
  23:  "Parabolic reason",
  24:  "Newton reason",
  25:  "parabolic n. iter",
  26:  "min",
  27:  "max",
  28:  "newton n. iter",
  29:  "min",
  30:  "max",
  31:  "1. problem solve",
  32:  "1.1/2 pre solve",
  33:  "problem_solver_pre_solve",
  34:  "1.1. problem cellml solve",
  35:  "cellml solve (*)",
  36:  "1.1.1. cellml field2cellml update",
  37:  "1.1.2. cellml field var get",
  38:  "1.1.3. cellml data get",
  39:  "1.1.4. cellml integrate",
  40:  "cellml call rhs",
  41:  "1.1.5. cellml data restore",
  42:  "1.1.6. cellml field update",
  43:  "problem_solver_post_solve",
  44:  "1.2. dynamic linear solve (*)",
  45:  "1.2.1 assemble equations",
  46:  "1.2.2 get loop time",
  47:  "1.2.3 solve",
  48:  "1.2.4 back-substitute",
  49:  "1.1/2 post solve",
  50:  "1.2.3.1 dynamic mean predicted calculate",
  51:  "1.2.3.2 dynamic assemble",
  52:  "1.2.3.3 solve linear system",
  53:  "1.2.3.4 update dependent field",
  54:  "1.3.1 pre solve",
  55:  "1.3.2 apply incremented BC",
  56:  "1.3.3 solve",
  57:  "1.3.3.1 static nonlinear solve (*)",
  58:  "1.3.3.1.1 apply BC, assemble",
  59:  "1.3.3.1.2 assemble interface conditions",
  60:  "1.3.3.1.3 solve",
  61:  "1.3.3.1.3.1 newton update solution vector",
  62:  "1.3.3.1.3.2 newton Petsc solve",
  63:  "1.3.3.1.3.3 newton diagnostics",
  64:  "1.3.3.1.4 update residual",
  65:  "1.3.4 post solve",
  66:  "distributed vector cmiss DP (memory)",
  67:  "distributed vector cmiss DP (size 1 el.)",
  68:  "distributed vector cmiss DP (n. objects)",
  69:  "distributed vector cmiss INTG (memory)",
  70:  "distributed vector cmiss INTG (size 1 el.)",
  71:  "distributed vector cmiss INTG (n. objects)",
  72:  "distributed matrix petsc, compr. row storage diag (memory)",
  73:  "distributed matrix petsc, compr. row storage diag (size 1 el.)",
  74:  "distributed matrix petsc, compr. row storage diag (n. objects)",
  75:  "distributed matrix petsc, compr. row storage, offdiag (memory)",
  76:  "distributed matrix petsc, compr. row storage, offdiag (size 1 el.)",
  77:  "distributed matrix petsc, compr. row storage, offdiag (n. objects)",
  78:  "distributed matrix petsc, compr. row storage, row ind. (memory)",
  79:  "distributed matrix petsc, compr. row storage, row ind. (size 1 el.)",
  80:  "distributed matrix petsc, compr. row storage, row ind. (n. objects)",
  81:  "distributed matrix petsc, compr. row storage, col. ind. (memory)",
  82:  "distributed matrix petsc, compr. row storage, col. ind. (size 1 el.)",
  83:  "distributed matrix petsc, compr. row storage, col. ind. (n. objects)",
  84:  "distributed matrix petsc, compr. row storage (local to global mapping) (memory)",
  85:  "distributed matrix petsc, compr. row storage (local to global mapping) (size 1 el.)",
  86:  "distributed matrix petsc, compr. row storage (local to global mapping) (n. objects)",
  87:  "distributed vector petsc (memory)",
  88:  "distributed vector petsc (size 1 el.)",
  89:  "distributed vector petsc (n. objects)",
  90:  "FE solver (pre load)",
  91:  "ODE solver (pre load)",
  92:  "parabolic solver (pre load)",
  93:  "file output (pre load)",
  94:  "export EMG (user)",
  95:  "export EMG (system)",
  96:  "file output (user)",
  97:  "file output (system)",
  98:  "file output (system, pre load)",
  99:  "MsolverId",
 100:  "MprecondId",
 101:  "odeSolverId",
}


max_index = 102 

float_indices = range(10, 21) + range(31, 66) + range(90, 99) 
string_indices = [0, 1]


# all other are int_indices
int_indices = list(set(range(max_index)) - set(float_indices) - set(string_indices))

def extract_data(data):

  datasets = dict()
  
  # extract lines
  n = 0
  for dataset in data:
    
    if len(dataset) < 17:
      print "Warning: invalid data set"
      continue
    
    # copy dataset to new_data
    new_data = dataset
    
    # fill dataset to size of max_index
    if len(dataset) < max_index+1:
      new_data += (max_index+1-len(dataset)) * [0]
      
    # extract some values
    for index in int_indices:
      new_data[index] = int(new_data[index])     if isint(new_data[index])    else 0
    for index in float_indices:
      new_data[index] = float(new_data[index])     if isfloat(new_data[index])    else 0.0
      
    # define sorting key
    
    block = 2**int(max(1,np.log2(new_data[8])-2))
    
    
    key = "{:04d}|{:01d}|{:01d}".format(int(new_data[8]/block)*block, new_data[99], new_data[100])
      
    # store extracted values
    if key not in datasets:
      datasets[key] = dict()
      datasets[key]["value"] = []
    
    datasets[key]['value'].append(new_data)
    n += 1
    
  # compute mean value
  for key in datasets:
    
    result = copy.copy(datasets[key]['value'][0])
    variances = copy.copy(datasets[key]['value'][0])
    result += [0]
    
    for i in int_indices + float_indices:
      
      # reduce values
      result[i] = 0
      value_list = []
      for j in range(len(datasets[key]['value'])):
        value = datasets[key]['value'][j][i]
        
        if value != 0:
          value_list.append(value)
      
      # remove outlier
      value_list = sorted(value_list)
      n = len(value_list)
      
      #print "i={}, value_list for {}: {}".format(i, key, value_list)
      
      if n > outlier_bottom+outlier_top and remove_outlier:
        value_list = value_list[outlier_bottom:-outlier_top]
        
      # compute mean and standard deviation
      result[i] = np.mean(value_list)
      variances[i] = np.std(value_list)
      #print "mean: {}, std: {}".format(result[i], variances[i])
        
    result[max_index+1] = len(datasets[key]["value"])
        
    datasets[key]['value'] = result
    datasets[key]['variance'] = variances
    
  datasets = collections.OrderedDict(sorted(datasets.items()))
    
  return datasets
  
datasets = extract_data(data)

###############################################################
# output to console
print ""
print "------------- duration -------------------------------------------"
print "{:10}, {:6}, {:6}, {:6}, {:6}, {:10}, {:10}, {:10}, {:10}".\
format("key", "nproc", "F", "#M", "#FE", "init", "stretch", "init", "main")
for key in datasets:
  
  print "{:10}, {:6}, {:6}, {:6}, {:6}, {:10}, {:10}, {:10}, {:10}".\
  format(key, datasets[key]["value"][2], datasets[key]["value"][6], datasets[key]["value"][8], datasets[key]["value"][7], 
  fo.str_format_seconds(datasets[key]["value"][10]), 
  fo.str_format_seconds(datasets[key]["value"][11]), 
  fo.str_format_seconds(datasets[key]["value"][12]), 
  fo.str_format_seconds(datasets[key]["value"][13]))
print ""
print ""
  
print "{:10}, {:6}, {:6}, {:6}, {:6}, {:10}, {:10}, {:10}, {:10}".\
format("key", "nproc", "F", "#M", "#FE", "ODE", "Parabolic", "FE", "file output")
for key in datasets:
  
  print "{:10}, {:6}, {:6}, {:6}, {:6}, {:10}, {:10}, {:10}, {:10}".\
  format(key, datasets[key]["value"][2], datasets[key]["value"][6], datasets[key]["value"][8],  datasets[key]["value"][7], 
  fo.str_format_seconds(datasets[key]["value"][17]), 
  fo.str_format_seconds(datasets[key]["value"][18]), 
  fo.str_format_seconds(datasets[key]["value"][19]), 
  fo.str_format_seconds(datasets[key]["value"][96]))
  
  
if False:
  print ""
  print "--------- timing -------------------------"
  for key in datasets:
    print "nproc: {}".format(datasets[key]["value"][2])
    for item in range(31, 66):
      print "   ", str(item).ljust(2), descriptions[item].ljust(50), ": ", datasets[key]["value"][item]


  
print ""
print "------------- n iterations -------------------------------------------"
print "{:10}, {:6}, {:6}, {:10}, {:10}, {:10}, {:10}, {:10}, {:10}, {:10}, {:10}".\
format("key", "F", "#M", "Parabolic", "Newton", "p. n. iter", "min", "max", "n. n. iter", "min", "max" )
for key in datasets:
  
  print "{:10}, {:6}, {:6}, {:10}, {:10}, {:10}, {:10}, {:10}, {:10}, {:10}, {:10}".\
  format(key, datasets[key]["value"][6], datasets[key]["value"][8], 
  datasets[key]["value"][23],
  datasets[key]["value"][24],
  datasets[key]["value"][25],
  datasets[key]["value"][26],
  datasets[key]["value"][27],
  datasets[key]["value"][28],
  datasets[key]["value"][29],
  datasets[key]["value"][30])
###############################################################
#######################################################
# plot
# x-axis: n M elements
# y-axis: total time

#plt.rcParams.update({'font.size': 23})
plt.rcParams.update({'font.size': 16})
plt.rcParams['lines.linewidth'] = 4
output_path = ""
plotdata = collections.OrderedDict()
xdata = Set()
plotkeys = Set()

for key in datasets:
  
  dataset = datasets[key]['value']
  variances = datasets[key]['variance']
  nproc = dataset[2]
  nMelements = dataset[8]
  main_sim = dataset[13]
  
# 13 duration main sim
#  15:  "Total (User)",
# 17 ODE
# 18 Parabolic
# 19 FE
# 20 FE before Main Sim
#  96:  "file output (user)",
#  99:  "MsolverId",
# 100:  "MprecondId",
# 101:  "odeSolverId",
  for plotkey in [15, 17, 18, 19, 96]:
    
    
    xvalue = nMelements
    yvalue = dataset[plotkey]
    yvalue_variance = variances[plotkey]
      
    if plotkey == 18:   # parabolic
      plotkey = "parabolic{:01d}|{:01d}".format(int(dataset[99]), int(dataset[100]))
    
    if plotkey not in plotdata:
      plotdata[plotkey] = dict()
      plotdata[plotkey]['value'] = collections.OrderedDict()
      plotdata[plotkey]['variance'] = collections.OrderedDict()
      
    plotdata[plotkey]['value'][xvalue] = yvalue
    plotdata[plotkey]['variance'][xvalue] = yvalue_variance
    xdata.add(xvalue)
    plotkeys.add(plotkey)

xlist = sorted(xdata)

######################
# plot serial scaling
plt.figure(2, figsize=(10,8))

# 13 duration main sim
# 17 ODE
# 18 Parabolic
# 19 FE
# 20 FE before Main Sim
colors = {
  13: "ko-",
  15: "ko-",
  17: "yo-",
  "parabolic1|1": "c-",
  "parabolic2|1": "r-",
  "parabolic3|1": "m-",
  "parabolic3|2": "ro:",
  "parabolic3|3": "r+-",
  "parabolic3|4": "r+--",
  "parabolic3|5": "r+-.",
  "parabolic3|6": "r+:",
  "parabolic3|7": "mo-",
  "parabolic4|1": "mo--",
  18: "ro-",
  19: "go-",
  96: "bo-",
}
labels = {
  13: "Duration main simulation",
  15: "Total runtime",
  17: "0D model solver",
  "parabolic1|1": "1D model solver (LU)",
  "parabolic2|1": "1D model solver (GMRES)",
  "parabolic3|1": "1D model solver (CG)",
  "parabolic3|2": "Parabolic solver (CG, Jacobi)",
  "parabolic3|3": "Parabolic solver (CG, Block Jacobi)",
  "parabolic3|4": "Parabolic solver (CG, SOR)",
  "parabolic3|5": "Parabolic solver (CG, Incompl. Cholesky)",
  "parabolic3|6": "Parabolic solver (CG, Incompl. LU)",
  "parabolic3|7": "Parabolic solver (CG, Add. Schwarz)",
  "parabolic4|1": "Parabolic solver (CGS)",
  18: "Parabolic solver",
  19: "FE solver",
  96: "File output",
}

print "plotkeys: ",plotkeys

plotkeys = [15, 17, "parabolic2|1", "parabolic3|1", "parabolic1|1"]

for plotkey in plotkeys:
    
  xlist = sorted(plotdata[plotkey]["value"])
  ylist = [y for y in plotdata[plotkey]["value"].values()]
  yerr = [y for y in plotdata[plotkey]['variance'].values()]

  plt.errorbar(xlist, ylist, fmt=colors[plotkey], yerr=yerr, label=labels[plotkey])
  
ax = plt.gca()
#ax.set_xscale('log', basey=2) 
ax.set_yscale('log', basey=10) 
ax.set_xscale('log', basey=10) 
ax.set_xlim([1, 3e3])
#ax.set_xticks([1,2,4,8,12,16,24,32,64])
plt.xlabel('Number of 1D elements')
plt.ylabel('Runtime (s)')
plt.legend(loc='best')
plt.grid(which='both')

# twin axes for processes
#ax2 = ax.twiny()
#ax2.set_xlim(ax.get_xlim())
#ax2.set_xticks(xlist)
#ax2.set_xticklabels([1,2,4,8,12,16,24,32,64])
#ax2.set_xlabel(r"Number of processes")

plt.title(caption)
plt.tight_layout()
plt.savefig(output_path+SCENARIO+'_serial_scaling.png')

if show_plots:
  plt.show()
#quit()

