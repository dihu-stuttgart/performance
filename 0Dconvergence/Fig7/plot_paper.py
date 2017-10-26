#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
import numpy as np
import matplotlib.pyplot as plt
import csv
import collections
import copy
from sets import Set


data1 = np.genfromtxt("ConvSplittingi1.txt")
data3 = np.genfromtxt("ConvSplittingi3.txt")

#print data_euler[:,]
#print data_heun

plt.figure("speedup_single (12)", figsize=(14,8))


plt.rcParams.update({'font.size': 28})
plt.rcParams['lines.linewidth'] = 5
plt.rcParams['lines.markersize'] = 10

plt.plot(abs((data1[:,2]+23.5219216213)/23.5219216213), ((data1[:,0]+data1[:,1])/(1.7331368923187256+2.5334513187408447)), 'bo', label=r"Godunov")
plt.plot(abs((data3[:,2]+23.5219216213)/23.5219216213), ((data3[:,0]+data3[:,1])/(1.7331368923187256+2.5334513187408447)), 'go', label=r"Strang")

ax = plt.gca()
ax.set_xscale('log', basey=10) 
ax.set_yscale('log', basey=10) 
#ax.set_xlim([4e-1, 5e0])
ax.set_ylim([0.1, 1.1])
#ax.set_xscale('log', basey=2) 
#ticks = list(np.linspace(10**4, 10**5, 10)) + list(np.linspace(10**5, 10**6, 10))
#ax.set_xticks(ticks)
#ax.set_xticklabels([int(i/1000.) for i in ticks])

plt.subplots_adjust(right=0.57, top=0.84, bottom=0.12)
plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0., frameon=False)

ax.tick_params(direction='out', pad=4)
#ax.set_xticks(np.linspace(000,60000,5))

plt.xlabel(r'Relative error of $V_\mathrm{m}$')
#ax.set_ylim([0.5, 8e3])
ax.xaxis.set_label_coords(0.5, -0.1)
plt.ylabel('Normalized CPU-time')
#plt.legend(loc='best')
plt.grid(axis='y', which='both')
plt.grid(axis='x', which='major')

plt.savefig("fig7.png")

plt.show()
sys.exit(0)


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
  38: "gs-",      # 3D
  39: "bp-",      # 1D->3D
  40: "c<-",      # 3D->1D
  41: "bx-",      # file output
  22: "mo-",      # memory consumption
}

labels = {
  15: "total",                # total
  36: "solver 0D model",      # 0D
  37: "solver 1D model",      # 1D
  38: "solver 3D model",      # 3D
  39: u"homogenization, 1D to 3D",     # 1D->3D
  40: u"interpolation, 3D to 1D",      # 3D->1D
  41: "file output",          # file output
  22: "memory consumption",   # memory consumption
}

######################
# create plot multi node
caption = "Serial scaling, neon,\n x,y,z=(2,2,2), xi=(xi1,3,3) "
output_path = ""
outfile = output_path+SCENARIO+'_serial_scaling_std.png'
if paper_no_legend:
  plt.figure("serial scaling std (12)", figsize=(8,8))
else:
  plt.figure("serial scaling std (12)", figsize=(14,8))

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
    
  # loop over different curves (e.g. different measurements)
  for plotkey_number in [15, 36, 37, 38, 39, 40]:
    
    plotkey = plotkey_number
    
    # define x value and y value
    xvalue = nM*2
    yvalue = dataset[plotkey_number]
    yvalue_variance = variances[plotkey_number]
      
    print labels[plotkey_number],":",yvalue
      
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
#print "plotkeys: ",plotkeys
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
ax.set_xscale('log', basey=10) 
ax.set_yscale('log', basey=10) 
#ax.set_xlim([1e3, 3e5])
#ax.set_xscale('log', basey=2) 
#ticks = list(np.linspace(10**4, 10**5, 10)) + list(np.linspace(10**5, 10**6, 10))
#ax.set_xticks(ticks)
#ax.set_xticklabels([int(i/1000.) for i in ticks])

if not paper_no_legend:
  plt.subplots_adjust(right=0.57, top=0.84, bottom=0.12)
  plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0., frameon=False)

#ax.set_xticks(np.linspace(000,60000,5))

plt.xlabel('Number of 1D elements per fibre, $s_x$')
ax.xaxis.set_label_coords(0.5, -0.1)
plt.ylabel('Runtime (s)')
#plt.legend(loc='best')
plt.grid(which='major')

if not paper_version:
  plt.title(caption, y=1.1)
  plt.tight_layout()
  
#plt.tight_layout()
plt.savefig(outfile)

if show_plots:
  plt.show()
#quit()

