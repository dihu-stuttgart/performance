#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import gridspec
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
#report_filename = "paper_std2.csv"
report_filename = "improvements.csv"
report_filename_baseline = "baseline.csv"


caption = u'Runtime over problem size, neon'

print "report file: {}".format(report_filename)
data = []
with open(report_filename) as csvfile:
  reader = csv.reader(csvfile, delimiter=';')
  for row in reader:
    if len(row) > 0:
      if '#' not in row[0]:
        data.append(row)

# parse baseline
data_baseline = []
with open(report_filename_baseline) as csvfile:
  reader = csv.reader(csvfile, delimiter=';')
  for row in reader:
    if len(row) > 0:
      if '#' not in row[0]:
        data_baseline.append(row)


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

def extract_data(data,tag):

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
    key = "{}{:04d}".format(tag,new_data[8])
      
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
      
      if len(value_list) > 0:
        print "key=",key, ",len=",len(value_list)
      
      # remove outlier
      value_list = sorted(value_list)
      n = len(value_list)
      
      #if i==15:
        #print "key=",key,"i=",i,"n=",n
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
  
datasets = extract_data(data,"improvements")
datasets_baseline = extract_data(data_baseline,"baseline")

# merge dicts
z = datasets.copy()   # start with x's keys and values
z.update(datasets_baseline)    # modifies z with y's keys and values & returns None
datasets = z

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
# plot serial scaling
plt.rcParams.update({'font.size': 20})
plt.rcParams['lines.linewidth'] = 3
plt.rcParams['lines.markersize'] = 8

output_path = ""

colors = {

  15: "ko-",      # total
  36: "yd-",      # 0D
  37: "rv-",      # 1D
  
  "baseline15": "ko-",      # total
  "baseline36": "yd-",      # 0D
  "baseline37": "rv-",      # 1D
  "baseline38": "gs-",      # 3D
  "baseline39": "bp-",      # 1D->3D
  "baseline40": "c<-",      # 3D->1D
  "baseline41": "bx-",      # file output
  "baseline22": "mo-",      # memory consumption
  
  "improvements15": "ko--",      # total
  "improvements36": "yd--",      # 0D
  "improvements37": "rv--",      # 1D
  "improvements38": "gs--",      # 3D
  "improvements39": "bp--",      # 1D->3D
  "improvements40": "c<--",      # 3D->1D
  "improvements41": "bx--",      # file output
  "improvements22": "mo--",      # memory consumption
}

labels = {
  "baseline15": "total",                # total
  "baseline36": "solver 0D model",      # 0D
  "baseline37": "solver 1D model",      # 1D
  "baseline38": "solver 3D model",      # 3D
  "baseline39": u"homogenization, 1D to 3D",     # 1D->3D
  "baseline40": u"interpolation, 3D to 1D",      # 3D->1D
  "baseline41": "file output",          # file output
  "baseline22": "memory consumption",   # memory consumption
}

######################
# create plot multi node
caption = "Serial scaling, neon,\n x,y,z=(2,2,2), xi=(xi1,3,3) "
output_path = ""
outfile = output_path+SCENARIO+'_serial_scaling_comparison.png'
if paper_no_legend:
  plt.figure("serial scaling std (12)", figsize=(8,10))
else:
  plt.figure("serial scaling std (12)", figsize=(14,10))

output_path = ""
plotdata = collections.OrderedDict()
xdata = Set()
xtickslist = []
plotkeys = Set()
plotkeys_speedup = Set()

# key is the initially defined sorting key
for key in datasets:
  
  dataset = datasets[key]['value']
  variances = datasets[key]['variance']
  nproc = dataset[2]
  
  nFE = dataset[7]
  nM = dataset[8]
  
  nMperFE = float(nM)/nFE
    
  # loop over different curves (e.g. different measurements)
  for plotkey_number in [15, 36, 37, 38, 39, 40]:
    
    if "baseline" in key:
      plotkey = "baseline"+str(plotkey_number)
    else:
      plotkey = "improvements"+str(plotkey_number)
    
    # define x value and y value
    xvalue = nM
    yvalue = dataset[plotkey_number]
    yvalue_variance = variances[plotkey_number]
      
    if plotkey_number in labels:
      print labels[plotkey_number],":",yvalue
      
    if plotkey not in plotdata:
      plotdata[plotkey] = dict()
      plotdata[plotkey]['value'] = collections.OrderedDict()
      plotdata[plotkey]['variance'] = collections.OrderedDict()
      
    plotdata[plotkey]['value'][xvalue] = yvalue
    plotdata[plotkey]['variance'][xvalue] = yvalue_variance
    xdata.add(xvalue)
    plotkeys.add(plotkey)

  
  if "baseline" in key:
    other_key = "improvements"+key[8:]
      
    dataset_baseline = datasets[key]['value']
    if other_key not in datasets:
      continue
    dataset_improvements = datasets[other_key]['value']
    nproc = dataset_baseline[2]
    
    nFE = dataset_baseline[7]
    nM = dataset_baseline[8]
    
    nMperFE = float(nM)/nFE
      
    # loop over different curves (e.g. different measurements)
    for plotkey_number in [15, 36, 37]:
      
      plotkey = plotkey_number
      
      # define x value and y value
      xvalue = nM
      yvalue = dataset_baseline[plotkey_number] / dataset_improvements[plotkey_number]
        
      print key," ",descriptions[plotkey_number],", xvalue: ", xvalue,", speedup: ",yvalue
        
      if plotkey not in plotdata:
        plotdata[plotkey] = dict()
        plotdata[plotkey]['value'] = collections.OrderedDict()
        plotdata[plotkey]['variance'] = collections.OrderedDict()
        
      plotdata[plotkey]['value'][xvalue] = yvalue
      plotdata[plotkey]['variance'][xvalue] = 0
      xdata.add(xvalue)
      plotkeys_speedup.add(plotkey)

# loop over curves and plot data with given label and color
plotkeys = sorted(plotkeys)
plotkeys_speedup = sorted(plotkeys_speedup)


gs = gridspec.GridSpec(2,1,height_ratios=[3,1])
plt.subplot(gs[0])
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
  plt.errorbar([2*x for x in xlist], ylist, fmt=color, yerr=yerr, label=label)
  
plt.plot([], [], 'k-', label="baseline implementation")
plt.plot([], [], 'k--', label="improvements")
plt.plot([], [], ' ', label="\n")
  
ax = plt.gca()
ax.set_xscale('log', basey=10) 
ax.set_yscale('log', basey=10) 
#ax.set_xlim([1e3, 3e5])
#ax.set_xscale('log', basey=2) 
#ticks = list(np.linspace(10**4, 10**5, 10)) + list(np.linspace(10**5, 10**6, 10))
#ax.set_xticks(ticks)
#ax.set_xticklabels([int(i/1000.) for i in ticks])


if paper_no_legend:
  plt.subplots_adjust(bottom=0.12)
else:
  plt.subplots_adjust(right=0.57, top=0.84, bottom=0.12)
  plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0., frameon=False)

plt.ylabel('Runtime (s)')
#plt.legend(loc='best')
plt.grid(which='major')

plt.subplot(gs[1])
for plotkey in plotkeys_speedup:
    
  xlist = sorted(plotdata[plotkey]["value"])
  ylist = [item[1] for item in sorted(plotdata[plotkey]["value"].items())]
  yerr = [item[1] for item in sorted(plotdata[plotkey]["variance"].items())]

  label = None
  if plotkey in labels:
    label = labels[plotkey]
  color = ""
  if plotkey in colors:
    color = colors[plotkey]
  plt.plot([2*x for x in xlist], ylist, color, label=label)
  
ax = plt.gca()
ax.set_xscale('log', basey=10) 
ax.set_yscale('log', basey=2) 

#ax.set_xlim([1e3, 3e5])
#ax.set_xscale('log', basey=2) 
#ticks = list(np.linspace(10**4, 10**5, 10)) + list(np.linspace(10**5, 10**6, 10))
#ax.set_xticks(ticks)
#ax.set_xticklabels([int(i/1000.) for i in ticks])


#ax.set_xticks(np.linspace(000,60000,5))

plt.xlabel('Number of 1D elements per fibre')
ax.xaxis.set_label_coords(0.5, -0.3)
plt.ylabel('Speedup (-)')
#plt.legend(loc='best')
plt.grid(which='major')

y_offset1 = 0.2
y_offset2 = 0.5
x_offset = 200
plt.annotate(s="3.1", xy=(576, 3.10330480237), xytext=(576-x_offset, 3.10330480237+y_offset2))
plt.annotate(s="5.3", xy=(159624, 5.29661820054), xytext=(159624, 5.29661820054+y_offset2))

plt.annotate(s="1.2", xy=(576, 1.24104304423), xytext=(576-x_offset, 1.24104304423+y_offset1))
plt.annotate(s="1.2", xy=(159624, 1.22459647275), xytext=(159624, 1.22459647275+y_offset1))

if not paper_version:
  plt.title(caption, y=1.1)
  plt.tight_layout()
  
#plt.tight_layout()
plt.savefig(outfile)

if show_plots:
  plt.show()
#quit()

