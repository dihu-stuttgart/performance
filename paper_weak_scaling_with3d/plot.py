#!/usr/bin/env python
# -*- coding: utf-8 -*-

# with 3D problem

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
outlier_bottom = 2
  
# read csv file
report_filename = "paper_multi_node.csv"
report_filename = "c.csv"


caption = u'Nodel-level weak scaling, Hazel Hen'
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
  31:  "level 0: stimulation handling",
  32:  "level 0: problem solve",
  33:  "level 1: MAIN_TIME_LOOP overhead",
  34:  "level 1: MONODOMAIN_TIME_LOOP overhead",
  35:  "level 1: ELASTICITY_LOOP overhead",
  36:  "level 1: SolverDAE solve",
  37:  "level 1: SolverParabolic solve",
  38:  "level 1: SolverFE solve",
  39:  "level 1: interpolate 1D->3D",
  40:  "level 1: interpolate 3D->1D",
  41:  "level 1: file output",
  42:  "level 2: solver overhead",
  43:  "level 2: 0D solve",
  44:  "level 2: 1D solve",
  45:  "level 2: 3D solve",
  46:  "level 3: 1D assembly",
  47:  "level 3: 1D solve",
  48:  "level 3: 1D other",
  49:  "level 3: 3D assembly",
  50:  "level 3: 3D solve",
  51:  "level 3: 3D other",      
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
 102:  "NumberOfElementsInAtomX",
 103:  "NumberOfElementsInAtomY",
 104:  "NumberOfElementsInAtomZ",
 105:  "nSubdomainsX",
 106:  "nSubdomainsY",
 107:  "nSubdomainsZ",
 108:  "ModelType",
}


max_index = 109

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
      
    if dataset[0] < "19.09.2017 16:38:55" and dataset[2] == 192:
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
      
    # define sorting key, defines one unique data point (x-axis value without the y-axis value)
      
    nFE = new_data[7]
    nM = new_data[8]
    nMperFE = float(nM)/nFE
    if new_data[105] == 1:    # nSubdomains=1
      s = "-"
    else:
      s = "o"
    key = "{}{}".format(new_data[2], s)
      
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
      
      if i==37 and "192" in key:
        value_list2 = []
        for value in value_list:
          if value < 100:
            value_list2 += [value]
        value_list = value_list2
      
      
      if (i == 0 and "192" in key):
        print "key=",key,", i=",i,",value_list:",value_list,",value:", value
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
print "{:10}, {:6}, {:6}, {:6}, {:10}, {:10}, {:10}, {:13}, {:10}, {:10}, {:10}".\
format("key", "nproc", "#M", "#FE", "total", "total: 0D", "1D", "3D", "solve: 0D", "1D", "3D")
for key in datasets:
  
  print "{:10}, {:6}, {:6d}, {:6d}, {:10}, {:10}, {:10}, {:13}, {:10}, {:10}, {:10}".\
  format(key, datasets[key]["value"][2], int(datasets[key]["value"][8]), int(datasets[key]["value"][7]), 
  fo.str_format_seconds(datasets[key]["value"][15]),
  fo.str_format_seconds(datasets[key]["value"][36]),
  fo.str_format_seconds(datasets[key]["value"][37]),
  fo.str_format_seconds(datasets[key]["value"][38]),
  fo.str_format_seconds(datasets[key]["value"][43]),
  fo.str_format_seconds(datasets[key]["value"][47]),
  fo.str_format_seconds(datasets[key]["value"][50]),
  )
print ""
print ""
  
if False:
  print ""
  print "--------- timing -------------------------"
  for key in datasets:
    print "nproc: {}".format(datasets[key]["value"][2])
    for item in range(31, 66):
      print "   ", str(item).ljust(2), descriptions[item].ljust(50), ": ", datasets[key]["value"][item]


if False:
  print ""
  print "------------- n iterations -------------------------------------------"
  print "{:10}, {:6}, {:6}, {:10}, {:10}, {:10}, {:10}, {:10}, {:10}, {:10}, {:10}, {:8}".\
  format("key", "F", "#M", "Parabolic", "Newton", "p. n. iter", "min", "max", "n. n. iter", "min", "max", "n fibres" )
  for key in datasets:
    
    nFE = datasets[key]["value"][7]
    nM = datasets[key]["value"][8]
    nMperFE = float(nM)/nFE
    
    n_fibrelines_per_element = 1
    print nMperFE
    if nMperFE==80:
      n_fibrelines_per_element = 4
    elif nMperFE==120:
      n_fibrelines_per_element = 6
    elif nMperFE==16:
      n_fibrelines_per_element = 4
    elif nMperFE==3:
      n_fibrelines_per_element = 1
      
    nfibres = datasets[key]["value"][3]*datasets[key]["value"][3]*n_fibrelines_per_element
    
    print "{:10}, {:6}, {:6}, {:10}, {:10}, {:10}, {:10}, {:10}, {:10}, {:10}, {:10}, {:8}".\
    format(key, datasets[key]["value"][6], datasets[key]["value"][8], 
    datasets[key]["value"][23],
    datasets[key]["value"][24],
    datasets[key]["value"][25],
    datasets[key]["value"][26],
    datasets[key]["value"][27],
    datasets[key]["value"][28],
    datasets[key]["value"][29],
    datasets[key]["value"][30],
    nfibres,
    )
###############################################################
#######################################################
# plot
# x-axis: n processes
# y-axis: total time
plt.rcParams.update({'font.size': 20})
plt.rcParams['lines.linewidth'] = 3
plt.rcParams['lines.markersize'] = 8

output_path = ""

colors = {
  "15o": "ko-",      # total
  "36o": "yd-",      # 0D
  "37o": "rv-",      # 1D
  "38o": "gs-",      # 3D
  "39o": "bp-",     # 1D->3D
  "40o": "c<-",      # 3D->1D
  "41o": "bx-",      # file output
  22: "mo-",      # memory consumption
  "22o": "mo-",      # memory consumption
  "ghosto": "ko-",   # ghost layer size
  
  "15-": "ko--",      # total
  "36-": "yd--",      # 0D
  "37-": "rv--",      # 1D
  "38-": "gs--",      # 3D
  "39-": "bp--",     # 1D->3D
  "40-": "c<--",      # 3D->1D
  "41-": "bx-",      # file output
  "22-": "mo--",      # memory consumption
  
  "ghost-": "ko--",   # ghost layer size
}

labels = {
  "15o": "total",      # total
  "36o": "solver 0D model",      # 0D
  "37o": "solver 1D model",      # 1D
  "38o": "solver 3D model",      # 3D
  "39o": u"homogenization, 1D to 3D",     # 1D->3D
  "40o": u"interpolation, 3D to 1D",      # 3D->1D
  "41o": "file output",      # file output
  22: "memory consumption",      # memory consumption
  "22o": "mem. cubes",      # memory consumption
  "22-": "mem. elongated",      # memory consumption
  "ghosto": "ghost layer size"   # ghost layer size
}
#plotkeys = [13, 17, 18, 19, 20]

######################
# create plot multi node
caption = "Multi-node weak scaling, Hazel Hen,\n xi=(3,2,2), 12 1D el./3D el. "
outfile = output_path+SCENARIO+'_weak_scaling_with_3d.png'
if paper_no_legend:
  plt.figure("multi-node (12)", figsize=(10,8))
else:
  plt.figure("multi-node (12)", figsize=(14,8))

output_path = ""
plotdata = collections.OrderedDict()
xdata = Set()
xtickslist = []
plotkeys = Set()

# key is the initially defined sorting key
for key in datasets:
  
  dataset = datasets[key]['value']
  variances = datasets[key]['variance']
  nproc = dataset[2]
  
  nFE = dataset[7]
  nM = dataset[8]
  
  nMperFE = float(nM)/nFE
    
  if dataset[105] == 1:
    s = "-"     # pillars, fibres not subdivided
  else:
    s = "o"     # cubic
  
  xtickslist.append((nM,nproc))
  
  # loop over different curves (e.g. different measurements)
  for plotkey_number in [15, 36, 37, 38]:
    
    plotkey = str(plotkey_number) + s
    
    # define x value and y value
    xvalue = nM
    yvalue = dataset[plotkey_number]
    yvalue_variance = variances[plotkey_number]
      
    if plotkey not in plotdata:
      plotdata[plotkey] = dict()
      plotdata[plotkey]['value'] = collections.OrderedDict()
      plotdata[plotkey]['variance'] = collections.OrderedDict()
      
    plotdata[plotkey]['value'][xvalue] = yvalue
    plotdata[plotkey]['variance'][xvalue] = yvalue_variance
    xdata.add(xvalue)
    plotkeys.add(plotkey)


# loop over curves and plot data with given label and color
plotkeys = sorted(plotkeys)
for plotkey in plotkeys:
    
  xlist = sorted(plotdata[plotkey]["value"])
  ylist = [item[1] for item in sorted(plotdata[plotkey]["value"].items())]
  yerr = [item[1] for item in sorted(plotdata[plotkey]["variance"].items())]

  label = None
  if plotkey in labels:
    label = labels[plotkey]
  color = ""
  if plotkey in colors:
    color = colors[plotkey]
  plt.errorbar(xlist, ylist, fmt=color, yerr=yerr, label=label)
  
  
ax = plt.gca()
ax.set_xscale('log', basey=2) 
ax.set_yscale('log', basey=10) 
ax.set_xlim([2e3,1e5])
#ax.set_xscale('log', basey=2) 
#ticks = list(np.linspace(10**4, 10**5, 10)) + list(np.linspace(10**5, 10**6, 10))
#ax.set_xticks(ticks)
#ax.set_xticklabels([int(i/1000.) for i in ticks])

if not paper_no_legend:
  plt.subplots_adjust(right=0.58, top=0.84)
  plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0., fontsize=20.)

#ax.set_xticks(np.linspace(000,60000,5))

plt.xlabel('Number of 1D elements')
plt.ylabel('Runtime (s)')
#plt.legend(loc='best')
plt.grid(which='both')

# twin axes for processes
ax2 = ax.twiny()
ax2.set_xlim(ax.get_xlim())
ax2.set_xscale('log', basey=2)

xtickslist = sorted(list(set(xtickslist)))
xtickslist = [(item[0],int(np.ceil(item[1]/24.))) for item in xtickslist]

# only leave certain values for number of processes
show_processes = [1, 2, 3, 4, 6, 8, 16, 32, 64]
xtickslist_new = list()
for item in xtickslist:
  
  # omit number of process values that are already present in xtickslist_new
  if item[1] in [itema[1] for itema in xtickslist_new]:
    continue
  
  # if the current number of process value is in show_processes, add it to xtickslist_new
  if item[1] in show_processes:
    xtickslist_new.append(item)

xtickslist = list(xtickslist_new)
xticks = [item[0] for item in xtickslist]
xlabels = [item[1] for item in xtickslist]
#xlabels = [int(np.ceil(item[1]/24.)) for item in xtickslist]

print "xticks:",xticks

ax2.set_xticks(xticks)
ax2.set_xticklabels(xlabels)
ax2.set_xlabel(r"Number of nodes (24 processes per node)")

#plt.gcf().subplots_adjust(right=0.89)
if not paper_version:
  plt.title(caption, y=1.1)
  plt.tight_layout()
  
#plt.tight_layout()
plt.savefig(outfile)

######################
# create plot multi node
caption = "Multi-node weak scaling, parallel efficiency, Hazel Hen,\n xi=(3,2,2), 12 1D el./3D el. "
outfile = output_path+SCENARIO+'_weak_scaling_with_3d_efficiency.png'
if paper_no_legend:
  plt.figure("multi-node efficiency (12)", figsize=(10,8))
else:
  plt.figure("multi-node efficiency (12)", figsize=(14,8))

output_path = ""
plotdata = collections.OrderedDict()
xdata = Set()
xtickslist = []
plotkeys = Set()

yreference_pillar = datasets["24-"]["value"]
yreference_cube = datasets["24-"]["value"]

# key is the initially defined sorting key
for key in datasets:
  
  dataset = datasets[key]['value']
  variances = datasets[key]['variance']
  nproc = dataset[2]
  
  nFE = dataset[7]
  nM = dataset[8]
  
  nMperFE = float(nM)/nFE
    
  if dataset[105] == 1:
    s = "-"     # pillars, fibres not subdivided
    yreference = yreference_pillar
  else:
    s = "o"     # cubic
    yreference = yreference_cube
    continue
  
  xtickslist.append((nM,nproc))
  
  # loop over different curves (e.g. different measurements)
  for plotkey_number in [15, 36, 37, 38]:
    
    plotkey = str(plotkey_number) + s
    
    # define x value and y value
    xvalue = nM
    yvalue = yreference[plotkey_number] / dataset[plotkey_number]
    yvalue_variance = variances[plotkey_number]
    yvalue_variance = 0
      
    if plotkey not in plotdata:
      plotdata[plotkey] = dict()
      plotdata[plotkey]['value'] = collections.OrderedDict()
      plotdata[plotkey]['variance'] = collections.OrderedDict()
      
    plotdata[plotkey]['value'][xvalue] = yvalue
    plotdata[plotkey]['variance'][xvalue] = yvalue_variance
    xdata.add(xvalue)
    plotkeys.add(plotkey)


# loop over curves and plot data with given label and color
plotkeys = sorted(plotkeys)
for plotkey in plotkeys:
    
  xlist = sorted(plotdata[plotkey]["value"])
  ylist = [item[1] for item in sorted(plotdata[plotkey]["value"].items())]
  yerr = [item[1] for item in sorted(plotdata[plotkey]["variance"].items())]

  label = None
  if plotkey in labels:
    label = labels[plotkey]
  color = ""
  if plotkey in colors:
    color = colors[plotkey]
  plt.errorbar(xlist, ylist, fmt=color, yerr=yerr, label=label)
  
  
ax = plt.gca()
ax.set_xscale('log', basey=2) 
#ax.set_yscale('log', basey=10) 
ax.set_xlim([2e3,1e5])
#ax.set_xscale('log', basey=2) 
#ticks = list(np.linspace(10**4, 10**5, 10)) + list(np.linspace(10**5, 10**6, 10))
#ax.set_xticks(ticks)
#ax.set_xticklabels([int(i/1000.) for i in ticks])

if not paper_no_legend:
  plt.subplots_adjust(right=0.58, top=0.84)
  plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0., fontsize=20.)

#ax.set_xticks(np.linspace(000,60000,5))

plt.xlabel('Number of 1D elements')
plt.ylabel('Parallel efficiency')
#plt.legend(loc='best')
plt.grid(which='both')

# twin axes for processes
ax2 = ax.twiny()
ax2.set_xlim(ax.get_xlim())
ax2.set_xscale('log', basey=2)

xtickslist = sorted(list(set(xtickslist)))
xtickslist = [(item[0],int(np.ceil(item[1]/24.))) for item in xtickslist]

# only leave certain values for number of processes
show_processes = [1, 2, 3, 4, 6, 8, 16, 32, 64]
xtickslist_new = list()
for item in xtickslist:
  
  # omit number of process values that are already present in xtickslist_new
  if item[1] in [itema[1] for itema in xtickslist_new]:
    continue
  
  # if the current number of process value is in show_processes, add it to xtickslist_new
  if item[1] in show_processes:
    xtickslist_new.append(item)

xtickslist = list(xtickslist_new)
xticks = [item[0] for item in xtickslist]
xlabels = [item[1] for item in xtickslist]
#xlabels = [int(np.ceil(item[1]/24.)) for item in xtickslist]

print "xticks:",xticks

ax2.set_xticks(xticks)
ax2.set_xticklabels(xlabels)
ax2.set_xlabel(r"Number of nodes (24 processes per node)")

#plt.gcf().subplots_adjust(right=0.89)
if not paper_version:
  plt.title(caption, y=1.1)
  plt.tight_layout()
  
#plt.tight_layout()
plt.savefig(outfile)
######################
# create plot multi node, memory
caption = "Multi-node weak scaling, memory consumption, Hazel Hen,\n x,y,z=(4,2,1), xi=(3,2,2), 12 1D el./3D el. "
outfile = output_path+SCENARIO+'_weak_scaling_multi_equal_memory.png'
plt.figure("multi-node (12), memory", figsize=(8,7))

output_path = ""
plotdata = collections.OrderedDict()
xdata = Set()
plotkeys = Set()

# key is the initially defined sorting key
for key in datasets:
  
  dataset = datasets[key]['value']
  variances = datasets[key]['variance']
  nproc = dataset[2]
  
  nFE = dataset[7]
  nM = dataset[8]
  
  # compute ghost layer size
  
# 102:  "NumberOfElementsInAtomX",
# 103:  "NumberOfElementsInAtomY",
# 104:  "NumberOfElementsInAtomZ",
# 105:  "nSubdomainsX",
# 106:  "nSubdomainsY",
# 107:  "nSubdomainsZ",
  nx = dataset[105]
  ny = dataset[106]
  nz = dataset[107]
  x = dataset[3]
  y = dataset[4]
  z = dataset[5]
  
  subdomain_shape_x = np.ceil(x/nx)
  subdomain_shape_y = np.ceil(y/ny)
  subdomain_shape_z = np.ceil(z/nz)
  
  remainder_subdomain_shape_x = (1-nx)*subdomain_shape_x + x
  remainder_subdomain_shape_y = (1-ny)*subdomain_shape_y + y
  remainder_subdomain_shape_z = (1-nz)*subdomain_shape_z + z
  
  single_full_ghost_layer_size = subdomain_shape_x*subdomain_shape_y*2 + subdomain_shape_x*subdomain_shape_z*2 + subdomain_shape_y*subdomain_shape_z*2
  single_remainder_ghost_layer_size_xplus = remainder_subdomain_shape_x*subdomain_shape_y*2 + remainder_subdomain_shape_x*subdomain_shape_z*2 + subdomain_shape_y*subdomain_shape_z*2
  single_remainder_ghost_layer_size_yplus = subdomain_shape_x*remainder_subdomain_shape_y*2 + subdomain_shape_x*subdomain_shape_z*2 + remainder_subdomain_shape_y*subdomain_shape_z*2
  single_remainder_ghost_layer_size_zplus = subdomain_shape_x*subdomain_shape_y*2 + subdomain_shape_x*remainder_subdomain_shape_z*2 + subdomain_shape_y*remainder_subdomain_shape_z*2
   
  single_remainder_ghost_layer_size_xyplus = remainder_subdomain_shape_x*remainder_subdomain_shape_y*2 + remainder_subdomain_shape_x*subdomain_shape_z*2 + remainder_subdomain_shape_y*subdomain_shape_z*2
  single_remainder_ghost_layer_size_xzplus = remainder_subdomain_shape_x*subdomain_shape_y*2 + remainder_subdomain_shape_x*remainder_subdomain_shape_z*2 + subdomain_shape_y*remainder_subdomain_shape_z*2
  single_remainder_ghost_layer_size_yzplus = subdomain_shape_x*remainder_subdomain_shape_y*2 + subdomain_shape_x*remainder_subdomain_shape_z*2 + remainder_subdomain_shape_y*remainder_subdomain_shape_z*2
  
  single_remainder_ghost_layer_size_xyzplus = remainder_subdomain_shape_x*remainder_subdomain_shape_y*2 + remainder_subdomain_shape_x*remainder_subdomain_shape_z*2 + remainder_subdomain_shape_y*remainder_subdomain_shape_z*2  
    
  total_ghostlayer_elements = single_full_ghost_layer_size * (nx-1)*(ny-1)*(nz-1)\
    + single_remainder_ghost_layer_size_xplus * (ny-1)*(nz-1)\
    + single_remainder_ghost_layer_size_yplus * (nx-1)*(nz-1)\
    + single_remainder_ghost_layer_size_zplus * (nx-1)*(ny-1)\
    + single_remainder_ghost_layer_size_xyplus * (nz-1)\
    + single_remainder_ghost_layer_size_xzplus * (ny-1)\
    + single_remainder_ghost_layer_size_yzplus * (nx-1)\
    + single_remainder_ghost_layer_size_xyzplus * 1\
  
  if False:
    print ""
    print "ghostlayers"
    print "n subdomains: ",nx,ny,nz, ", xyz=",x,y,z
    print "subdomain shape: ", subdomain_shape_x,subdomain_shape_y,subdomain_shape_z
    print "remainder shape: ",remainder_subdomain_shape_x, remainder_subdomain_shape_y, remainder_subdomain_shape_z
    
    print "sum: ", single_full_ghost_layer_size," * ",(nx-1)*(ny-1)*(nz-1),\
    "+",single_remainder_ghost_layer_size_xplus," * ",(ny-1)*(nz-1),\
    "+",single_remainder_ghost_layer_size_yplus," * ",(nx-1)*(nz-1),\
    "+",single_remainder_ghost_layer_size_zplus," * ",(nx-1)*(ny-1),\
    "+",single_remainder_ghost_layer_size_xyplus," * ",(nz-1),\
    "+",single_remainder_ghost_layer_size_xzplus," * ",(ny-1),\
    "+",single_remainder_ghost_layer_size_yzplus," * ",(nx-1),\
    "+",single_remainder_ghost_layer_size_xyzplus," * ",1
  
  ghostlayer_size_per_process = total_ghostlayer_elements / nproc
  
  
  #print "ghostlayer_size_per_process:",ghostlayer_size_per_process
  
  nMperFE = float(nM)/nFE
  if nMperFE != 12 or nproc == 72:
    continue
  
  if dataset[105] == 1:
    s = "-"     # pillars, fibres not subdivided
  else:
    s = "o"     # cubic
  
  if s=="-":
    xtickslist.append((nM,nproc))
  
  # loop over different curves (e.g. different measurements)
  for plotkey_number in [22,"ghost"]:
    
    if plotkey_number == 22:
      plotkey = str(22) + s
      
      # define x value and y value
      xvalue = nM
      yvalue = dataset[plotkey_number]/(1024*1024.*1024)
      yvalue_variance = variances[plotkey_number]/(1024*1024.*1024)**2

    elif plotkey_number == "ghost":
      plotkey = "ghost" + s
      xvalue = nM
      yvalue = ghostlayer_size_per_process
      yvalue_variance = 0
        
    if plotkey not in plotdata:
      plotdata[plotkey] = dict()
      plotdata[plotkey]['value'] = collections.OrderedDict()
      plotdata[plotkey]['variance'] = collections.OrderedDict()
      
    plotdata[plotkey]['value'][xvalue] = yvalue
    plotdata[plotkey]['variance'][xvalue] = yvalue_variance
    xdata.add(xvalue)
    plotkeys.add(plotkey)


# loop over curves and plot data with given label and color
plotkeys = sorted(plotkeys)
for plotkey in ["22o"]:
    
  xlist = sorted(plotdata[plotkey]["value"])
  ylist = [item[1] for item in sorted(plotdata[plotkey]["value"].items())]
  yerr = [item[1] for item in sorted(plotdata[plotkey]["variance"].items())]

  label = None
  if plotkey in labels:
    label = labels[plotkey]
  color = ""
  if plotkey in colors:
    color = colors[plotkey]
  plt.errorbar(xlist, ylist, fmt=color, yerr=yerr, label=label)
  
  
ax = plt.gca()
#ax.set_xscale('log', basey=2) 
#ax.set_yscale('log', basey=10)
#ax.set_xscale('log', basey=2) 
ticks = list(np.linspace(10**4, 10**5, 10))
ax.set_xticks(ticks)
ax.set_xticklabels([int(i) for i in ticks])
plt.grid(which="major")


#ax.set_xticks(np.linspace(20000,180000,5))
ax.set_ylim(0,ax.get_ylim()[1])
plt.ylabel('Memory consumption per process (GiB)')

ax3 = ax.twinx()

for plotkey in ["ghosto", "ghost-"]:
  xlist = sorted(plotdata[plotkey]["value"])
  ylist = [item[1] for item in sorted(plotdata[plotkey]["value"].items())]
  yerr = [item[1] for item in sorted(plotdata[plotkey]["variance"].items())]

  label = None
  if plotkey in labels:
    label = labels[plotkey]
  color = ""
  if plotkey in colors:
    color = colors[plotkey]
  plt.plot(xlist, ylist, color, label=label)


#ax3.tick_params('y', colors='k')


plt.xlabel('Number of 1D elements')
plt.ylabel('Number of 3D ghost elements')
plt.legend(loc='best')
plt.grid(which='both')

# twin axes for processes
ax2 = ax.twiny()
ax2.set_xlim(ax.get_xlim())
#ax2.set_xscale('log', basey=2)

ax2.set_xticks(xticks)
ax2.set_xticklabels(xlabels)
ax2.set_xlabel(r"Number of nodes (24 processes per node)")

plt.gcf().subplots_adjust(right=0.89)
if not paper_version:
  plt.title(caption, y=1.1)
  plt.tight_layout()
plt.savefig(outfile)

if show_plots:
  plt.show()
#quit()

