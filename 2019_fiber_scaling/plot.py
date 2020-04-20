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

pd.set_option('display.width', 1000)

input1_filename = "logs/log.csv"
#input1_filename = "logs/log-old.csv"
input2_filename = "duration.00000.csv"
#input2_filename = "duration.00000-old.csv"

print("filenames: {}, {}".format(input1_filename, input2_filename))
	
show_plots = True

plt.rcParams.update({'font.size': 24})
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
    #print("column_names:",column_names)

  # load data frame
  df = pd.read_csv(filename, sep=';', error_bad_lines=False, warn_bad_lines=True, comment="#", header=None, names=column_names, usecols=range(n_columns))
  return df

df_opendihu = load_df(input1_filename)
#df_opendihu.info()

df_opendihu["n_fibers"] = df_opendihu["nInstancesComputedGlobally"]
df_opendihu["duration_total"] = df_opendihu["totalUsertime"]

#print("scenarioName")
#print(df_opendihu["scenarioName"])

df_opendihu_no_vectorization = df_opendihu[df_opendihu["scenarioName"] == "no_vectorization"]
df_opendihu = df_opendihu[df_opendihu["scenarioName"] != "no_vectorization"]

if False:
  print("df_opendihu_no_vectorization info:")
  df_opendihu_no_vectorization.info()
  sys.exit(0)

  print(df_opendihu["n_fibers"])
  print(df_opendihu["duration_0D"])
  print(df_opendihu["duration_1D"])
  print(df_opendihu["duration_total"])

# load opencmiss data
df_opencmiss = load_df(input2_filename)
#print(df_opencmiss)
#df_opencmiss.info()

df_opencmiss["n_fibers"] = df_opencmiss[" Total M"] / 1480.
df_opencmiss["duration_total"] = df_opencmiss[" Total (User)"]
df_opencmiss["duration_0D"] = df_opencmiss[" ODE"]
df_opencmiss["duration_1D"] = df_opencmiss[" Parabolic"]

if False:
  print(df_opencmiss["n_fibers"])
  print("opencmiss:")
  print(df_opencmiss["duration_total"])
  print("opendihu normal:")
  print(df_opendihu["duration_total"])
  print("opendihu without vectorization:")
  print(df_opendihu_no_vectorization["duration_total"])

#print("speedup total opencmiss to opendihu: ")
#df_opendihu["speedup"] = df_opendihu["duration_total"] / df_opencmiss

for n_fibers in df_opencmiss["n_fibers"]:
  duration_opencmiss = df_opencmiss[df_opencmiss["n_fibers"] == n_fibers]["duration_total"].to_numpy()[0]
  duration_opendihu = df_opendihu[df_opendihu["n_fibers"] == n_fibers]["duration_total"].to_numpy()[0]
  print("n_fibers: {}, duration_opencmiss: [{}], duration_opendihu: [{}], speedup: {}".format(n_fibers,duration_opencmiss,duration_opendihu,duration_opencmiss / duration_opendihu))
  
  df_opendihu.loc[df_opendihu["n_fibers"] == n_fibers, "speedup_opencmiss"] = duration_opencmiss / duration_opendihu
  
#print(df_opendihu["speedup_opencmiss"])

#print("Speedup 0D solver with vectorization:")
print("")
for n_fibers in df_opendihu["n_fibers"]:
  duration_no_vectorization = df_opendihu_no_vectorization[df_opendihu_no_vectorization["n_fibers"] == n_fibers]["duration_0D"].to_numpy()[0]
  duration_opendihu = df_opendihu[df_opendihu["n_fibers"] == n_fibers]["duration_0D"].to_numpy()[0]
  #print("n_fibers: {}, duration_no_vectorization: {}, duration_opendihu: {}, speedup: {}".format(n_fibers,duration_no_vectorization,duration_opendihu,duration_no_vectorization / duration_opendihu))
  df_opendihu.loc[df_opendihu["n_fibers"] == n_fibers, "speedup_vectorization"] = duration_no_vectorization / duration_opendihu
  
#print(df_opendihu["speedup_vectorization"])

print("\ndf_opendihu")
print(df_opendihu[["n_fibers","duration_total","duration_0D","speedup_opencmiss","speedup_vectorization"]])

if False:
  print("\ndf_opendihu_no_vectorization")
  print(df_opendihu_no_vectorization[["n_fibers","duration_total","duration_0D"]])

  print("\ndf_opencmiss")
  print(df_opencmiss[["n_fibers","duration_total"]])



plt.figure(figsize=(11,8))

max_x = 20

plt.plot([], [], 'k-', lw=3, label="OpenCMISS")
plt.plot([], [], 'm-', lw=3, label="OpenDiHu")
plt.plot([], [], 'c-', lw=3, label="OpenDiHu without \nexplicit vectorization")
plt.plot([], [], ' ', label="\n")
plt.plot([], [], color="grey", linestyle='-')
plt.plot([], [], color="grey", linestyle='--')
plt.plot([], [], color="grey", linestyle='-.')

# plot opencmiss
plt.plot(df_opencmiss["n_fibers"][0:max_x], df_opencmiss["duration_total"][0:max_x], "k-", lw=3, label="total duration")
plt.plot(df_opencmiss["n_fibers"][0:max_x], df_opencmiss["duration_0D"][0:max_x], "k--", label="0D model")
plt.plot(df_opencmiss["n_fibers"][0:max_x], df_opencmiss["duration_1D"][0:max_x], "k-.", label="1D model")

# plot opendihu
plt.plot(df_opendihu["n_fibers"][0:max_x], df_opendihu["duration_total"][0:max_x], "m-", lw=3)
plt.plot(df_opendihu["n_fibers"][0:max_x], df_opendihu["duration_0D"][0:max_x], "m--")
plt.plot(df_opendihu["n_fibers"][0:max_x], df_opendihu["duration_1D"][0:max_x], "m-.")

# plot opendihu without vectorization
plt.plot(df_opendihu_no_vectorization["n_fibers"][0:max_x], df_opendihu_no_vectorization["duration_total"][0:max_x], "c-", lw=3)
plt.plot(df_opendihu_no_vectorization["n_fibers"][0:max_x], df_opendihu_no_vectorization["duration_0D"][0:max_x], "c--")
plt.plot(df_opendihu_no_vectorization["n_fibers"][0:max_x], df_opendihu_no_vectorization["duration_1D"][0:max_x], "c-.")

ax = plt.gca()
#ax.set_xscale('log', basex=10)
#ax.set_yscale('log', basey=10)
plt.subplots_adjust(right=0.68, top=0.84)
plt.title("Improved runtime of opendihu\n compared to OpenCMISS")
#plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0., frameon=False)
plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0., frameon=False, labels=
  ["OpenCMISS", "OpenDiHu", "OpenDiHu without \nexplicit vectorization", "",
  "total duration", "0D model", "1D model"])
plt.grid(which='major')
plt.xlabel("number of fibers")
plt.ylabel("duration [s]")

#plt.yscale('log', basey=10)
plt.savefig("opencmiss-opendihu.pdf")
plt.savefig("opencmiss-opendihu.png")

ax.set_xscale('log', basex=10)
ax.set_yscale('log', basey=10)
plt.savefig("opencmiss-opendihu-loglog.pdf")
plt.savefig("opencmiss-opendihu-loglog.png")
plt.show()
