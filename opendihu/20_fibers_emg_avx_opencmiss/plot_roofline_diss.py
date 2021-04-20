#!/usr/bin/python3

import os, sys
import numpy as np
import matplotlib.pyplot as plt
import datetime
import pandas as pd
import pandas_utility
import re
import traceback

# source of perf command: https://github.com/LucaCanali/Miscellaneous/blob/master/Spark_Notes/Tools_Linux_Memory_Perf_Measure.md

def process_perf_log(filename):
  # example log file:
  """# started on Mon Jan 18 20:20:21 2021                                                                                                                         
                                                                                                                                                              
                                                                                                                                                          
 Performance counter stats for 'system wide':                                                                                                                 
                                                                                                                                                              
      2,160,281.53 msec task-clock                #   35.995 CPUs utilized                      
   276,993,048,088      cycles                    #    0.128 GHz                      (17.83%)
   550,392,916,159      instructions              #    1.99  insn per cycle           (21.41%)
    69,213,224,882      branches                  #   32.039 M/sec                    (21.41%)       
    ...
  """
  
  # load file contents
  try:
    f = open(filename, "r")
  except OSError:
    print("Could not open {}.".format(filename))
    return 0,0,0
  
  try:
    events = {}
    
    # loop over lines of perf log
    for line in f:
      
      # skip non-data rows
      if "#" not in line[1:] and "seconds time elapsed" not in line:
        continue
      
      if "#" in line:
        # parse numbers, also first number
        match = re.search("[0-9,.]+", line)
        number = (float)(match.group().replace(",",""))
        #print("number: {}".format(number))
        
        # if there is no number ("<not supported> ")
        if match.end() > 20:
          continue
        
        line = line[match.end()+1:]
        event_name = line[5:line.find("#")]
        event_name = event_name.strip()
        #print("event_name: {}".format(event_name))
          
        events[event_name] = number
          
      else: 
        n_seconds = (float)(re.search("[0-9,.]+", line).group())
        #print("n_seconds: {}".format(n_seconds))
          
    #print(events)
          
    # note: captured events and explanations (run showevtinfo from libpfm4 and perf list to get these)
    # task-clock
    # cycles
    # instructions
    # branches
    # branch-misses
    # cache-references
    # cache-misses
    # LLC-loads
    # LLC-load-misses
    # LLC-stores
    # LLC-store-misses
    # L1-dcache-loads
    # L1-dcache-load-misses
    # L1-dcache-stores
    # r5301d1       MEM_LOAD_RETIRED:L1_HIT      Retired load uops with L1 cache hits as data source
    # r5302d1       MEM_LOAD_RETIRED:L2_HIT      Retired load uops with L2 cache hits as data source
    # r5304d1       MEM_LOAD_RETIRED:L3_HIT      Retired load uops with L3 cache hits as data source
    # r5308d1       MEM_LOAD_RETIRED:L1_MISS     Retired load uops which missed the L1D
    # r5310d1       MEM_LOAD_RETIRED:L2_MISS     Retired load uops which missed the L2. Unknown data source excluded
    # r5320d1       MEM_LOAD_RETIRED:L3_MISS     Retired load uops which missed the L3
    # r5380d1       MEM_LOAD_RETIRED:LOCAL_PMM   Retired load instructions with local persistent memory as the data source where the request missed all the caches
    # r5301c7       FP_ARITH_INST_RETIRED:SCALAR_DOUBLE : Number of scalar double precision floating-point arithmetic instructions (multiply by 1 to get flops)
    # r5302c7       FP_ARITH_INST_RETIRED:SCALAR_SINGLE : Number of scalar single precision floating-point arithmetic instructions (multiply by 1 to get flops)
    # r5304c7       FP_ARITH_INST_RETIRED:128B_PACKED_DOUBLE : Number of scalar 128-bit packed double precision floating-point arithmetic instructions (multiply by 2 to get flops)
    # r5308c7       FP_ARITH_INST_RETIRED:128B_PACKED_SINGLE : Number of scalar 128-bit packed single precision floating-point arithmetic instructions (multiply by 4 to get flops)
    # r5310c7       FP_ARITH_INST_RETIRED:256B_PACKED_DOUBLE : Number of scalar 256-bit packed double precision floating-point arithmetic instructions (multiply by 4 to get flops)
    # r5320c7       FP_ARITH_INST_RETIRED:256B_PACKED_SINGLE : Number of scalar 256-bit packed single precision floating-point arithmetic instructions (multiply by 8 to get flops)
    # r5340c7       FP_ARITH_INST_RETIRED:512B_PACKED_DOUBLE : Number of scalar 512-bit packed double precision floating-point arithmetic instructions (multiply by 8 to get flops)
    # r5380c7       FP_ARITH_INST_RETIRED:512B_PACKED_SINGLE : Number of scalar 512-bit packed single precision floating-point arithmetic instructions (multiply by 16 to get flops)

    # compute flops and flops/second
    n_flop = events["r5301c7"] + events["r5304c7"]*2 + events["r5310c7"]*4 + events["r5340c7"]*8
    performance = n_flop / n_seconds
          
    # compute memory bandwidth
    memory_amount = events["r5301d1"] + events["r5302d1"] + events["r5304d1"] + events["r5320d1"]
    memory_bandwidth = memory_amount / n_seconds
    intensity = n_flop / memory_bandwidth
    
    return performance,memory_bandwidth,intensity
    
  except Exception as e:
    print(e)
    traceback.print_exc()
    
  return 0,0,0
  
opencmiss_intensity_list=[]
opencmiss_flops_list=[]
opencmiss_ranks = [1,2,4,8,12,18]

print("opencmiss")
path = "opencmiss_run"
for n_ranks in opencmiss_ranks:
  # determine filename of log file
  filename = os.path.join(path,"perf_{:02}.txt".format(n_ranks))
  performance,memory_bandwidth,intensity = process_perf_log(filename)
  opencmiss_flops_list.append(performance)
  opencmiss_intensity_list.append(intensity)
  
  print("{} rank(s), performance: {:.3f} GFLOP/s, mem bandwidth: {:.3f} GB/s, intensity: {:.3f} FLOP/B".format(n_ranks,performance/1e9,memory_bandwidth/1e9,intensity))

# load opendihu perf log files
opendihu_intensity_ws_list=[]
opendihu_flops_ws_list=[]
opendihu_intensity_opt_list=[]
opendihu_flops_opt_list=[]

print("\nopendihu ws")
path = "opendihu_run"
opendihu_ranks = [1,2,4,8,12,18]
for n_ranks in opendihu_ranks:
  # determine filename of log file
  filename = os.path.join(path,"perf_{}_ws.txt".format(n_ranks))
  performance,memory_bandwidth,intensity = process_perf_log(filename)
  opendihu_flops_ws_list.append(performance)
  opendihu_intensity_ws_list.append(intensity)
  
  print("{} rank(s), performance: {:.3f} GFLOP/s, mem bandwidth: {:.3f} GB/s, intensity: {:.3f} FLOP/B".format(n_ranks,performance/1e9,memory_bandwidth/1e9,intensity))

print("\nopendihu sparse fibers")
for n_ranks in opendihu_ranks:
  # determine filename of log file
  filename = os.path.join(path,"perf_{}_opt.txt".format(n_ranks))
  performance,memory_bandwidth,intensity = process_perf_log(filename)
  opendihu_flops_opt_list.append(performance)
  opendihu_intensity_opt_list.append(intensity)
  print("{} rank(s), performance: {:.3f} GFLOP/s, mem bandwidth: {:.3f} GB/s, intensity: {:.3f} FLOP/B".format(n_ranks,performance/1e9,memory_bandwidth/1e9,intensity))
  
# create plots
# ---------------
plt.rcParams.update({'font.size': 16})
plt.rcParams.update({'lines.markersize': 10})
plt.rcParams['lines.linewidth'] = 2 
#plt.rcParams['text.usetex'] = True

# -------------------
# roofline model
# measured using https://bitbucket.org/berkeleylab/cs-roofline-toolkit/src/master/



fig = plt.figure(1,figsize=(8,6))
ax = fig.add_subplot(111)

peak_performance = 715e9
l1_bandwidth = 3679e9
l2_bandwidth = 2442e9
l3_bandwidth = 36e9
dram_bandwidth = 94e9

# F/B = F/s * (B/s)^-1
intensity_roof_corner = peak_performance / l1_bandwidth

# axis limits of plot
intensity_max = 1000
performance_min = 1e9
performance_max = 1000e9
intensity_min = performance_min / l1_bandwidth

yscale = 1e9  # scaling factor for the y axis, 1e9 = Giga, 1e12 = Tera
mem_color = (0.4,0.4,0.4)
ax.plot([performance_min / l1_bandwidth, peak_performance / l1_bandwidth], [performance_min / yscale, peak_performance / yscale], linestyle="-", color=mem_color)   # L1 bandwidth
ax.plot([performance_min / l2_bandwidth, peak_performance / l2_bandwidth], [performance_min / yscale, peak_performance / yscale], linestyle="-", color=mem_color)   # L2 bandwidth
ax.plot([performance_min / l3_bandwidth, peak_performance / l3_bandwidth], [performance_min / yscale, peak_performance / yscale], linestyle="-", color=mem_color)   # L3 bandwidth
ax.plot([performance_min / dram_bandwidth, peak_performance / dram_bandwidth], [performance_min / yscale, peak_performance / yscale], linestyle="-", color=mem_color)   # DRAM bandwidth
ax.plot([intensity_roof_corner, intensity_max], [peak_performance / yscale, peak_performance / yscale], "k-") # top roof ridge

# text
# old measurement which was FP32
#ax.text(4e-1, peak_performance / yscale + 1e2, "$P_{max}$: 606.1 GFlop/s")
#ax.text(1e-3, 10, "L1: 3259 GB/s", ha="left", color=mem_color, rotation=65)
#ax.text(8e-3, 10, "L2: 2020 GB/s", ha="left", color=mem_color, rotation=65)
#ax.text(1e-1, 10, "L3: 40.4 GB/s", ha="left", color=mem_color, rotation=65)
#ax.text(5e-1, 10, "DRAM: 28.4 GB/s", ha="left", color=mem_color, rotation=65)

# new measurement with FP64
ax.text(4e-1, peak_performance / yscale + 5e1, "$P_{max}$: 715 GFLOP/s")
ax.text(1.5e-3, 10, "L1: 3679 GB/s", ha="left", color=mem_color, rotation=58)
ax.text(5e-3, 10, "L2: 2442 GB/s", ha="left", color=mem_color, rotation=58)
ax.text(6.5e-2, 10, "L3: 36.1 GB/s", ha="left", color=mem_color, rotation=58)
ax.text(4e-1, 10, "DRAM: 94 GB/s", ha="left", color=mem_color, rotation=58)

# data points
p1, = ax.plot(opencmiss_intensity_list, [y/yscale for y in opencmiss_flops_list], "o-", label="OpenCMISS")
p2, = ax.plot(opendihu_intensity_ws_list, [y/yscale for y in opendihu_flops_ws_list], "o-", label="OpenDiHu")
p2, = ax.plot(opendihu_intensity_opt_list, [y/yscale for y in opendihu_flops_opt_list], "o-", label="OpenDiHu (sparse fibers)")

# annotations
for r,x,y in zip(opencmiss_ranks,opencmiss_intensity_list,opencmiss_flops_list):
  ax.text(x,y/yscale, "{} ".format(r), ha="right", verticalalignment='center')
  
for r,x,y in zip(opendihu_ranks,opendihu_intensity_opt_list,opendihu_flops_opt_list):
  if r == 18:
    ax.text(x,y/yscale, "{} ".format(r), ha="right", verticalalignment='center')
  elif r == 12:
    ax.text(x,y/yscale-10, "{} ".format(r), ha="right", verticalalignment='center')
  else:
    ax.text(x,y/yscale, " {}".format(r), ha="left", verticalalignment='center')
  
for r,x,y in zip(opendihu_ranks,opendihu_intensity_ws_list,opendihu_flops_ws_list):
  ax.text(x,y/yscale, " {}".format(r), ha="left", verticalalignment='center')


ax.set_yscale("log")
ax.set_xscale("log")
ax.set_xlabel("Computational intensity [FLOP/Byte]")
ax.set_ylabel("Performance [GFLOP/s]")
ax.set_xlim(intensity_min, intensity_max)
ax.set_ylim(performance_min / yscale, performance_max / yscale)

ax.grid(which="major", axis="x")
ax.grid(which="both", axis="y")

#plt.legend(loc="lower left", bbox_to_anchor=(0,1.0), frameon=False)
plt.subplots_adjust(left=0.15, top=0.7)
plt.tight_layout()

plt.savefig("0_roofline.pdf")
print("Created \"0_roofline.pdf\".")

plt.show()



