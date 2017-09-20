#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib
#matplotlib.use('Agg')
import subprocess
import datetime
import time
import os
import exnode_reader

# compute errors
error = 0
reference_folder = "0_5_200"
folder = "0_10_200"
vm_reference = exnode_reader.parse_file(reference_folder+"/MainTime_M_2_10.part0.exnode", [["Vm",1]])
vm_measurement = exnode_reader.parse_file(folder+"/MainTime_M_2_10.part0.exnode", [["Vm",1]])
error = np.linalg.norm(vm_measurement - vm_reference) / len(vm_measurement)
 
plt.figure(0)
xlist = range(len(vm_measurement))
plt.subplots(211)
plt.plot(xlist, vm_measurement, label=folder)
plt.plot(xlist, vm_reference, label=reference_folder)
plt.legend(loc='best')
plt.title('Vm')
plt.xlabel('Node no.')
plt.ylabel('Vm')

plt.subplots(212)
plt.plot(xlist, vm_reference-vm_measurement)
plt.legend(loc='best')
plt.xlabel('Node no.')
plt.ylabel('error')
plt.savefig('vis.png')
plt.show()
