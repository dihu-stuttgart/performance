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
  input_filename = "build_release_hh_cn/result.csv"
print("filename: {}".format(input_filename))
	
show_plots = True

plt.rcParams.update({'font.size': 12})
plt.rcParams['lines.linewidth'] = 2


values_shorten = []   # spatial resolution, velocity, dt
values_hh = []

true_vel = 0.09692151232846527
true_vel = 0.16965864537718423

# parse file
with open(input_filename, "r") as f:
  lines = f.read().split('\n')

print("lines: [{}]".format(lines))

# entries in line: scenario_name, resolution, velocity, dt
for line in lines:
  entries = line.split(';')
  print("entries: {}".format(entries))
  
  if len(entries) < 3:
    continue
  
  velocity = (float)(entries[2])
  dt = (float)(entries[3])
  resolution = (float)(entries[1])
  
  error = abs(velocity - true_vel)/true_vel
  
  #if "shorten" in entries[0]:
  
  #if dt < 0.0002 and resolution > 160:
  if resolution > 160 or "sh_cn" in input_filename:
    values_shorten.append([resolution, error, dt])
  
  #if "hodgkin_huxley" in entries[0]:
  #  values_hh.append([(float)(entries[1]), velocity, (float)(entries[3])])

print(values_shorten)


x_hh = [x for [x,y,dt] in values_hh]
y_hh = [y for [x,y,dt] in values_hh]


x_shorten = [x for [x,y,dt] in values_shorten]
y_shorten = [dt for [x,y,dt] in values_shorten]
z_shorten = [y for [x,y,dt] in values_shorten]

print("x_shorten: {}".format(x_shorten))
print("y_shorten: {}".format(y_shorten))
print("z_shorten: {}".format(z_shorten))

fig = plt.figure(0)
ax = fig.add_subplot(111, projection='3d')

plt.title("error of propagation velocity")
ax.scatter(x_shorten, y_shorten, z_shorten)

ax.set_xlabel("resolution [1/cm]")
ax.set_ylabel("dt [ms]")
ax.ticklabel_format(style='sci', scilimits=(0,0))
ax.set_zlabel("relative error of \n velocity")
#ax.set_xscale('log')
#ax.set_yscale('log')
#ax.set_zscale('log')

plt.grid(which='both')
plt.legend(loc="best")

scenario = "none"
if "sh_cn" in input_filename:
  scenario = "sh_cn"
elif "hh_cn" in input_filename:
  scenario = "hh_cn"
elif "sh_ie" in input_filename:
  scenario = "sh_ie"
elif "hh_ie" in input_filename:
  scenario = "hh_ie"
plt.savefig(scenario+"_error_3d.pdf")

fig = plt.figure(1)
plt.plot(x_shorten,z_shorten, 'o')
plt.yscale('log')
plt.xlabel("\nresolution [1/cm]")
plt.ylabel("relative error \n of velocity")
plt.grid(which='both')
plt.tight_layout()
plt.savefig(scenario+"_error_resolution.pdf")

fig = plt.figure(2)
plt.plot(y_shorten,z_shorten, 'o')
plt.yscale('log')
plt.xlabel("dt [ms]")
plt.ylabel("relative error")
plt.grid(which='both')
plt.tight_layout()
plt.savefig(scenario+"_error_dt.pdf")

#plt.yscale('log', basey=10)
plt.show()
