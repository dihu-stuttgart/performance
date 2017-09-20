#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import subprocess
import datetime
import time
import os
import exnode_reader

def compute_error(reference_folder, folder):
  # compute errors
  error = 0
  vm_reference = exnode_reader.parse_file(reference_folder+"/MainTime_M_2_10.part0.exnode", [["Vm",1]])
  vm_measurement = exnode_reader.parse_file(folder+"/MainTime_M_2_10.part0.exnode", [["Vm",1]])
  error = np.linalg.norm(vm_measurement - vm_reference) / len(vm_measurement)
   
  # set parameters for plotting
  plt.rcParams.update({'font.size': 16})
  plt.rcParams['lines.linewidth'] = 3
  plt.rcParams['lines.markersize'] = 8

  # create plot with Vm
  plt.figure(0)
  xlist = range(len(vm_measurement))
  plt.subplot(211)
  plt.plot(xlist, vm_measurement, 'o-', label=folder)
  plt.plot(xlist, vm_reference, 'o-', label=reference_folder)
  plt.legend(loc='best')
  plt.title('Vm')
  #plt.xlabel('Node no.')
  plt.ylabel('Vm')

  # create plot with error
  plt.subplot(212)
  plt.plot(xlist, vm_reference-vm_measurement, 'o-')
  plt.figtext(0.7,0.3,"L2 error:".format(error))
  plt.figtext(0.7,0.25,"{:0.5}".format(error))
  plt.legend(loc='best')
  plt.xlabel('Node no.')
  plt.ylabel('error')
  filename = folder+'/vis.png'
  plt.savefig(filename)
  print "save figure to {}".format(filename)
  #plt.show()
  return error
