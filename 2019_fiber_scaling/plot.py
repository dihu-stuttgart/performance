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

input1_filename = "logs/log.csv"
#input1_filename = "logs/log-old.csv"
input2_filename = "duration.00000.csv"
#input2_filename = "duration.00000-old.csv"

print("filenames: {}, {}".format(input1_filename, input2_filename))
	
show_plots = True

plt.rcParams.update({'font.size': 14})
plt.rcParams['lines.linewidth'] = 2

# load opendihu data
def load_df(filename):
  # determine number of columns
  with open(filename) as f:
    line = f.readline()
    if "~nDofsFiber0" in line:
      pos = line.find("~nDofsFiber0")
      column_names = line[0:pos].split(";")
    else:
      column_names = line.split(";")
    
    n_columns = len(column_names)
    print(column_names)

  # load data frame
  df = pd.read_csv(filename, sep=';', error_bad_lines=False, warn_bad_lines=True, comment="#", header=None, names=column_names, usecols=range(n_columns))
  return df

df_opendihu = load_df(input1_filename)
df_opendihu.info()

df_opendihu["n_fibers"] = df_opendihu["nInstancesComputedGlobally"]
df_opendihu["duration_total"] = df_opendihu["totalUsertime"]

print(df_opendihu["n_fibers"])
print(df_opendihu["duration_0D"])
print(df_opendihu["duration_1D"])
print(df_opendihu["duration_total"])


# load opencmiss datae
df_opencmiss = load_df(input2_filename)
print(df_opencmiss)
df_opencmiss.info()

df_opencmiss["n_fibers"] = df_opencmiss[" Total M"] / 1480.
df_opencmiss["duration_total"] = df_opencmiss[" Total (User)"]
df_opencmiss["duration_0D"] = df_opencmiss[" ODE"]
df_opencmiss["duration_1D"] = df_opencmiss[" Parabolic"]

print(df_opencmiss["n_fibers"])
print("opencmiss:")
print(df_opencmiss["duration_total"])
print("opendihu:")
print(df_opendihu["duration_total"])

print("speedup total: ")
#df_opendihu["speedup"] = df_opendihu["duration_total"] / df_opencmiss

for n_fibers in df_opencmiss["n_fibers"]:
  duration_opencmiss = df_opencmiss[df_opencmiss["n_fibers"] == n_fibers]["duration_total"]
  duration_opendihu = df_opendihu[df_opendihu["n_fibers"] == n_fibers]["duration_total"]
  df_opendihu.loc[df_opendihu["n_fibers"] == n_fibers, "speedup"] = duration_opencmiss / duration_opendihu
  
print(df_opendihu["speedup"])

plt.figure(figsize=(10,8))

max_x = 20

plt.plot([], [], 'k-', label="baseline implementation")
plt.plot([], [], 'k--', label="improvements")
plt.plot([], [], ' ', label="\n")

# plot opencmiss
plt.plot(df_opencmiss["n_fibers"][0:max_x], df_opencmiss["duration_total"][0:max_x], "k-", lw=3, label="total duration")
plt.plot(df_opencmiss["n_fibers"][0:max_x], df_opencmiss["duration_0D"][0:max_x], "y-", label="0D model")
plt.plot(df_opencmiss["n_fibers"][0:max_x], df_opencmiss["duration_1D"][0:max_x], "r-", label="1D model")

# plot opendihu
plt.plot(df_opendihu["n_fibers"][0:max_x], df_opendihu["duration_total"][0:max_x], "k--", lw=3)
plt.plot(df_opendihu["n_fibers"][0:max_x], df_opendihu["duration_0D"][0:max_x], "y--")
plt.plot(df_opendihu["n_fibers"][0:max_x], df_opendihu["duration_1D"][0:max_x], "r--")

ax = plt.gca()
ax.set_xscale('log', basex=10)
ax.set_yscale('log', basey=10)
plt.subplots_adjust(right=0.58, top=0.84)
plt.title("runtime of simulation")
plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0., frameon=False, labels=["OpenCMISS", "opendihu", "", "total", "0D model", "1D model"])
plt.grid(which='major')
plt.xlabel("number of fibers")
plt.ylabel("duration [s]")

#plt.yscale('log', basey=10)
plt.show()
