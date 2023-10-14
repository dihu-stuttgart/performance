#!/usr/bin/python3

import os, sys
import numpy as np
import matplotlib.pyplot as plt
import datetime
import pandas as pd
import pandas_utility
import re
import traceback

# load opencmiss log files
opencmiss_t=[]
opencmiss_m=[]

print("opencmiss")
path = "opencmiss_run"
for n_ranks in [1,2,4,8,12,18]:
  # determine filename of log file
  log_filename = os.path.join(path,"log_{:02}.txt".format(n_ranks))

  # load file contents
  try:
    with open(log_filename, "r") as f:
      log_contents = f.read()
  except:
    print("Could not open {}.".format(log_filename))

  try:
    # extract start and end time
    items = log_contents.split(" ")
    string_start = " ".join(items[0:2]).strip()   # 12.01.2021 16:14:25
    string_end = " ".join(items[-5:-3]).strip()   # 12.01.2021 16:14:25
    time_start = datetime.datetime.strptime(string_start, "%d.%m.%Y %H:%M:%S")
    time_end = datetime.datetime.strptime(string_end, "%d.%m.%Y %H:%M:%S")
    time_delta = time_end - time_start
    duration = time_delta.total_seconds()
  
    # extract memory consumption
    results = re.findall("Resident:[ ]*[0-9.]*[ GMKB]*",log_contents)
    memory_list = []
    for result in results:
      gigabytes = float([x for x in re.findall("[0-9.]*",result) if x != ""][0])
      memory_list.append(gigabytes)
    memory_consumption_gb = max(memory_list)
    opencmiss_t.append(duration)
    opencmiss_m.append(memory_consumption_gb)
    print("{}: duration {} s, memory consumption per process (high watermark): {} GB".format(n_ranks, duration, memory_consumption_gb))
  except Exception as e:
    print(e)
    traceback.print_exc()

# load opendihu data from log
opendihu_t_ws=[]
opendihu_t2_ws=[]
opendihu_t_opt=[]
opendihu_t2_opt=[]
opendihu_m=[]
print("opendihu")
filename = "opendihu_run/logs/log.csv"
df = pandas_utility.load_df(filename)
df = df.groupby(['nRanks','scenarioName'])

# output opendihu data
total_user_time = df.agg("totalUsertime").mean()
duration_total_time = df.agg("duration_total").mean()
memory_consumption = df.agg("memoryResidentSet").mean()
for n_ranks in [-1,1,2,4,8,12,18]:
  if n_ranks == -1:
    n_ranks = 1
    scenario_name = "gpu-double-1fiber"
    opendihu_t_gpu = total_user_time[(n_ranks,scenario_name)]
    opendihu_t2_gpu = duration_total_time[(n_ranks,scenario_name)]
    print("{}: duration: {:.1f}s, {:.1f}s, memory consumption per process (high watermark): {:.3f} GB".
      format(n_ranks,total_user_time[(n_ranks,scenario_name)],duration_total_time[(n_ranks,scenario_name)],memory_consumption[(n_ranks,scenario_name)]/1e9))
  else:
    scenario_name = "vc-{}-ws".format(n_ranks)
    print("{}: duration: {:.1f}s, {:.1f}s, memory consumption per process (high watermark): {:.3f} GB, speedup to opencmiss: {}".
      format(n_ranks,total_user_time[(n_ranks,scenario_name)],duration_total_time[(n_ranks,scenario_name)],memory_consumption[(n_ranks,scenario_name)]/1e9,
      opencmiss_t[len(opendihu_t_ws)]/total_user_time[(n_ranks,scenario_name)]))
    opendihu_t_ws.append(total_user_time[(n_ranks,scenario_name)])
    opendihu_t2_ws.append(duration_total_time[(n_ranks,scenario_name)])
    
    scenario_name = "vc-{}-opt".format(n_ranks)
    print("{}: duration: {:.1f}s, {:.1f}s, memory consumption per process (high watermark): {:.3f} GB, speedup to opencmiss: {}".
      format(n_ranks,total_user_time[(n_ranks,scenario_name)],duration_total_time[(n_ranks,scenario_name)],memory_consumption[(n_ranks,scenario_name)]/1e9,
      opencmiss_t[len(opendihu_t_ws)-1]/total_user_time[(n_ranks,scenario_name)]))
    opendihu_t_opt.append(total_user_time[(n_ranks,scenario_name)])
    opendihu_t2_opt.append(duration_total_time[(n_ranks,scenario_name)])
    opendihu_m.append(memory_consumption[(n_ranks,scenario_name)]/1e9)


# create plots
# ---------------
#print(plt.rcParams.keys())
plt.rcParams.update({'font.size': 16})
plt.rcParams.update({'lines.markersize': 10})
plt.rcParams['lines.linewidth'] = 2 

# combined plot
fig = plt.figure(0,figsize=(6,6))
ax = fig.add_subplot(111)

# runtime
color = "blue"
ranks = [1,2,4,8,12,18]
p1, = ax.plot(ranks, opencmiss_t, "o:", color=color, label="OpenCMISS")
p2, = ax.plot(ranks, opendihu_t2_ws, "o-", color=color, label="OpenDiHu (all fibers)")
p2opt, = ax.plot(ranks, opendihu_t2_opt, "o-", color=color, label="OpenDiHu (only active parts)")
p2b, = ax.plot([1], opendihu_t2_gpu, 's', color=color, label="Runtime OpenDiHu GPU 1 fiber")

ax.set_xscale("log")
ax.set_yscale("log",basey=10)

ax.set_xticks(ranks)
ax.set_xticklabels(ranks)
ax.set_ylim(0,max(opencmiss_t)*1.1)
ax.set_ylabel("Total runtime [s]")
ax.set_xlabel("Number of processes")
ax.yaxis.label.set_color(color)
ax.grid(which="major")
ax.tick_params(axis='y', colors=color,)

# memory
color = "orange"
ax2 = ax.twinx()  # instantiate a second axes that shares the same x-axis
p3, = ax2.plot(ranks,opencmiss_m, "o:", color=color, label="Memory OpenCMISS")
p4, = ax2.plot(ranks,opendihu_m, "o-", color=color, label="Memory OpenDiHu")
ax2.set_yscale("log",basey=2)
ax2.set_ylabel("Memory consumption high water mark [GB]")
ax2.set_ylim(0,max(opencmiss_m)*1.1)
ax2.yaxis.label.set_color(color)
ax2.tick_params(axis='y', colors=color,)

lines = [p3, p1, p4, p2]
plt.legend(lines, [line.get_label() for line in lines], loc="lower left", bbox_to_anchor=(0,1.1), frameon=False)
plt.subplots_adjust(bottom=0.15,left=0.15,right=0.85,top=0.7)

plt.savefig("0_strong_scaling.pdf")
plt.savefig("0_strong_scaling.png")

# -------------------
# runtime
fig = plt.figure(1,figsize=(6,6))
ax = fig.add_subplot(111)

ranks = [1,2,4,8,12,18]
p1, = ax.plot(ranks, opencmiss_t, "o:", label="OpenCMISS")
p2, = ax.plot(ranks, opendihu_t_ws, "o-", label="OpenDiHu (all fibers)")
p2opt, = ax.plot(ranks, opendihu_t_opt, "o-", label="OpenDiHu (only active parts)")
p2b, = ax.plot([1], opendihu_t2_gpu*81, 's', label="OpenDiHu 1 fiber on GPU, ×81")

ax.set_yscale("log")
ax.set_xscale("log")
ax.set_xticks(ranks)
ax.set_xticklabels(ranks)
ax.set_xlabel("Number of processes")
ax.set_ylabel("Runtime [s]")
ax.grid(which="major")
plt.legend(loc="lower left", bbox_to_anchor=(0,1.1), frameon=False)
plt.subplots_adjust(top=0.7)

plt.savefig("0_strong_scaling_runtime.pdf")
plt.savefig("0_strong_scaling_runtime.png")

# -----------------
# memory
fig = plt.figure(2,figsize=(6,6))
ax = fig.add_subplot(111)

ranks = [1,2,4,8,12,18]
p1, = ax.plot(ranks, opencmiss_m, "o:", label="Memory OpenCMISS")
p2, = ax.plot(ranks, opendihu_m, "o-", label="Memory OpenDiHu")
#p2b, = ax.plot([1], opendihu_t2_gpu, 's', label="memory OpenDiHu GPU 1 fiber")

ax.set_xscale("log")
ax.set_xticks(ranks)
ax.set_xticklabels(ranks)
ax.set_xlabel("Number of processes")
ax.set_ylabel("Memory consumption per process [GB]")
ax.grid(which="major")
plt.legend(loc="lower left", bbox_to_anchor=(0,1.1), frameon=False)
plt.subplots_adjust(top=0.7)

plt.savefig("0_strong_scaling_memory.pdf")
plt.savefig("0_strong_scaling_memory.png")

# -------------
# efficiency
fig = plt.figure(3,figsize=(6,6))
ax = fig.add_subplot(111)

# runtime
color = "blue"
ranks = [1,2,4,8,12,18]
p1, = ax.plot(ranks, [opencmiss_t[0]/(p*v) for p,v in zip(ranks,opencmiss_t)], "o:", color=color, label="Runtime OpenCMISS")
p2, = ax.plot(ranks, [opendihu_t_ws[0]/(p*v) for p,v in zip(ranks,opendihu_t_ws)], "o-", color=color, label="Runtime OpenDiHu")
p2b, = ax.plot(ranks, [opendihu_t_opt[0]/(p*v) for p,v in zip(ranks,opendihu_t_opt)], "o-", color=color, label="Runtime OpenDiHu (sparse fibers)")

ax.set_xscale("log")
ax.set_xticks(ranks)
ax.set_xticklabels(ranks)
ax.set_xlabel("Number of processes")
ax.set_ylim(0,1.1)
ax.set_ylabel("Parallel efficiency")
ax.grid(which="major")

# memory
color = "orange"
ax2 = ax
p3, = ax2.plot(ranks,[opencmiss_m[0]/(p*v) for p,v in zip(ranks,opencmiss_m)], "o:", color=color, label="Memory OpenCMISS")
p4, = ax2.plot(ranks,[opendihu_m[0]/(p*v) for p,v in zip(ranks,opendihu_m)], "o-", color=color, label="Memory OpenDiHu")

lines = [p2, p1, p4, p3] 
plt.legend(lines, [line.get_label() for line in lines], loc="lower left", bbox_to_anchor=(0,1.1), frameon=False)
plt.subplots_adjust(left=0.15,top=0.7)

plt.savefig("0_strong_scaling_efficiency.pdf")
plt.savefig("0_strong_scaling_efficiency.png")

# -------------------
# runtime for poster
fig = plt.figure(4,figsize=(6,6))
ax = fig.add_subplot(111)

ranks = [1,2,4,8,12,18]
p1, = ax.plot(ranks, opencmiss_t, "o:", label="OpenCMISS")
p2, = ax.plot(ranks, opendihu_t_ws, "o-", label="OpenDiHu")

plt.rcParams.update({'font.size': 30})
plt.rcParams.update({'axes.labelsize': 30})
plt.rcParams.update({'axes.titlesize': 30})
plt.rcParams.update({'xtick.labelsize': 30})
plt.rcParams.update({'ytick.labelsize': 30})
plt.rcParams.update({'lines.markersize': 14})
plt.rcParams['lines.linewidth'] = 4 

ax.set_yscale("log")
ax.set_xscale("log")
ax.set_xticks(ranks)
ax.set_xticklabels(ranks, fontsize=24)
ax.set_xlabel("Number of processes", fontsize=30)
ax.set_ylabel("Runtime [s]", fontsize=30)
ax.grid(which="major")
plt.legend(loc="lower left", bbox_to_anchor=(0,1.1), frameon=False)
#plt.subplots_adjust(top=0.7)
plt.tight_layout()

plt.savefig("0_runtime_poster.png")

plt.show()



