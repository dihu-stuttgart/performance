#!/usr/bin/python3
#

import sys

filename = "p.txt"
if len(sys.argv) > 1:
  filename = sys.argv[1]

print("filename: {}".format(filename))

nOps1 = 0  # number of scalar floating point operations (factor 1)
nOps4 = 0  # number of avx-2 floating point operations  (factor 4)
nOps8 = 0  # number of avx-2 fma operations  (factor 8)
nSeconds = 0.0

# AMDuProfCLI collect -e event=pmcx003,umask=0x80 -e event=pmcx003,umask=0x70 -e event=pmcx002,umask=0x7 -p `pgrep -d , fast_fibers` --duration 1

"""
PMCx002      Retired x87 Floating Point Operations
PMCx003      Retired SSE/AVX Operations

pmcx003
Possible unitmasks are: 
        0x80 - DpMultAddFLOPs: Double precision multiply-add FLOPs Multiply-add counts as 2 FLOPs.
        0x40 - DpDivFLOPs: Double precision divide/square root FLOPs
        0x20 - DpMultFLOPs: Double precision multiply FLOPs
        0x10 - DpAddSubFLOPs: Double precision add/subtract FLOPs
        0x8 - SpMultAddFLOPs: Single precision multiply-add FLOPs Multiply-add counts as 2 FLOPs.
        0x4 - SpDivFLOPs: Single-precision divide/square root FLOPs
        0x2 - SpMultFLOPs: Single-precision multiply FLOPs
        0x1 - SpAddSubFLOPs: Single-precision add/subtract FLOPs
        
PMCx002
Possible unitmasks are: 
        0x4 - DivSqrROps: Divide and square root Ops
        0x2 - MulOps: Multiply Ops
        0x1 - AddSubOps: Add/subtract Ops
"""


"""
/opt/hlrs/performance/uprof/3.2.228/bin/AMDuProfCLI
WARNING: For non-root users with perf_event_paranoid value 2, kernel profiling is disabled.

Profile started ...

CPCLI>>> CoreId     Event      Count-Value
CPCLI>>>   0        0x3       395553358
CPCLI>>>   0        0x3       356578847
CPCLI>>>   0        0x2       0
CPCLI>>>   1        0x3       397455586
CPCLI>>>   1        0x3       360643415
CPCLI>>>   1        0x2       0
CPCLI>>>   2        0x3       0
"""

content_started = False
no = 0
with open(filename,"r") as f:
  for line in f:
    print("line: [{}]".format(line))
    line = line.strip()
    print(line)

    if "CPCLI" in line:
      content_started = True

    if content_started:
      items = line.split()       
      print("no: {}, items: {}".format(no, items))
      if no == 0:
        nOps8 += (int)(items[3])
      elif no == 1:
        nOps4 += (int)(items[3])
      elif no == 2:
        nOps1 += (int)(items[3])
  
      no += 1
      if no == 3:
        no = 0

nSeconds = 1.0

nFLOPS = (nOps1 + 4*nOps4 + 8*nOps8)/nSeconds*1e-9
print("{} Gflops".format(nFLOPS))

