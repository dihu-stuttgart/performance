#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import numpy as np
import subprocess
import datetime
import time
from cycler import cycler
import os

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import itertools

if(len(sys.argv)) >= 2:
  input_filename = sys.argv[1]
else:
  input_filename = "build_release/result.csv"
print("filename: {}".format(input_filename))
	
show_plots = True

plt.rcParams.update({'font.size': 16})
plt.rcParams['lines.linewidth'] = 2


values_shorten = []
values_hh = []

# parse file
with open(input_filename, "r") as f:
  lines = f.read().split('\n')

print("lines: [{}]".format(lines))

for line in lines:
  entries = line.split(';')
  print("entries: {}".format(entries))
  
  if len(entries) < 3:
    continue
  
  velocity = (float)(entries[2])/(float)(entries[1])
  if "shorten" in entries[0]:
    values_shorten.append([(float)(entries[1]), velocity])
  if "hodgkin_huxley" in entries[0]:
    values_hh.append([(float)(entries[1]), velocity])

x_hh = [x for [x,y] in values_hh]
y_hh = [y for [x,y] in values_hh]

x_shorten = [x for [x,y] in values_shorten]
y_shorten = [y for [x,y] in values_shorten]

print values_hh


print x_hh, y_hh

fig = plt.figure(0)
plt.title("propagation velocity")
plt.plot(x_hh, y_hh, "o-", label="Hodgkin Huxley")
plt.plot(x_shorten, y_shorten, "o-", label="Shorten")
plt.xlabel("number of elements per cm [1/cm]")
plt.ylabel("velocity [cm/ms]")

plt.grid(which='both')
plt.legend(loc="best")

fig = plt.figure(1)
plt.title("Relative error")
plt.plot(x_hh, [abs(y-y_hh[-1])/y_hh[-1] for y in y_hh], "o-", label="Hodgkin Huxley")
plt.plot(x_shorten, [abs(y-y_shorten[-1])/y_shorten[-1] for y in y_shorten], "o-", label="Shorten")
plt.ylabel("relative error [-]")
plt.xlabel("number of elements per cm [1/cm]")
plt.grid(which='both')
plt.legend(loc="best")

#plt.yscale('log', basey=10)
plt.show()
