#!/usr/bin/env python
# -*- coding: utf-8 -*-

import math
import sys
import numpy as np

def number_of_processes(p,x,y,z,ax,ay,az,debug=False):
  """
  determine the number of processes that will be used for a domain decomposition parameterized by (x,y,z,ax,ay,z)
  """
  #print p,x,y,z,ax,ay,az

  NumberGlobalXElements = x
  NumberGlobalYElements = y
  NumberGlobalZElements = z

  NumberOfElementsFE = NumberGlobalXElements*NumberGlobalYElements*NumberGlobalZElements

  NumberOfElementsInAtomX = ax
  NumberOfElementsInAtomY = ay
  NumberOfElementsInAtomZ = az

  NumberOfDomains = p
   
  if debug:
    print "input: x,y,z={},{},{}, ax,ay,az={},{},{}, NumberOfDomains={}".format(NumberGlobalXElements, NumberGlobalYElements, NumberGlobalZElements, NumberOfElementsInAtomX, NumberOfElementsInAtomY, NumberOfElementsInAtomZ, NumberOfDomains)
    print "nElements: {}, n elments per domain: {}".format(NumberOfElementsFE, float(NumberOfElementsFE)/NumberOfDomains)

  # An atom is a cuboid of NumberOfElementsInAtomX x NumberOfElementsInAtomY x NumberOfElementsInAtomZ 3D finite elasticity elements that will not be distributed to multiple processes.
  # So this is an undividable unit for domain decomposition.
  # Determine how many atoms are possible in each direction, fractions at the end count as full atom
  nAtomsX = NumberGlobalXElements / NumberOfElementsInAtomX + np.sign(NumberGlobalXElements % NumberOfElementsInAtomX)
  nAtomsY = NumberGlobalYElements / NumberOfElementsInAtomY + np.sign(NumberGlobalYElements % NumberOfElementsInAtomY)
  nAtomsZ = NumberGlobalZElements / NumberOfElementsInAtomZ + np.sign(NumberGlobalZElements % NumberOfElementsInAtomZ)
  nAtoms = nAtomsX*nAtomsY*nAtomsZ

  if debug:
    print "nAtoms: {},{},{}={}".format(nAtomsX,nAtomsY,nAtomsZ,nAtoms)

  # subdomain = all the atoms that belong to one process
  # determine number of subdomains in each direction, such that domains are equally sized

  # nSubdomainsXFloat = NumberGlobalXElements / OptimalSideLength
  # nSubdomainsYFloat = NumberGlobalYElements / OptimalSideLength
  # nSubdomainsZFloat = NumberGlobalZElements / OptimalSideLength
  # nSubdomains = nSubdomainsXFloat * nSubdomainsYFloat * nSubdomainsZFloat 
  #         = NumberGlobalXElements * NumberGlobalYElements * NumberGlobalZElements / (OptimalSideLength)**3
  #         = NumberOfElementsFE / OptimalSideLength**3
  # => OptimalSideLength = (NumberOfElementsFE / nSubdomains)**(1./3)

  OptimalSideLength = (float(NumberOfElementsFE) / NumberOfDomains)**(1./3)

  # if number of atoms is limited in z direction, begin with partioning in z direction
  if float(NumberGlobalZElements) / OptimalSideLength > nAtomsZ:
    nSubdomainsZFloat = min(float(NumberGlobalZElements) / OptimalSideLength, nAtomsZ)
    if debug:
      print "nAtomsZ={}, OptimalSideLength={}, z={}, z/Opt={}, nSubdomainsZFloat={}".format(nAtomsZ, OptimalSideLength, NumberGlobalZElements, float(NumberGlobalZElements) / OptimalSideLength, nSubdomainsZFloat)

    OptimalSideLength = (nSubdomainsZFloat * NumberGlobalXElements * NumberGlobalYElements / NumberOfDomains)**(1./2)
    if debug:
      print "new OptimalSideLength={}".format(OptimalSideLength)
      
    nSubdomainsYFloat = min(float(NumberGlobalYElements) / OptimalSideLength, nAtomsY)
    if debug:
      print "nAtomsY={}, OptimalSideLength={}, y={}, y/Opt={}, nSubdomainsyFloat={}".format(nAtomsY, OptimalSideLength, NumberGlobalYElements, float(NumberGlobalYElements) / OptimalSideLength, nSubdomainsYFloat)

    nSubdomainsXFloat = min(float(NumberOfDomains) / (nSubdomainsZFloat * nSubdomainsYFloat), nAtomsX)
    if debug:
      print "nAtomsX={}, nSubdomainsXFloat={}, final: {}".format(nAtomsX, float(NumberOfDomains) / (nSubdomainsZFloat * nSubdomainsYFloat), nSubdomainsXFloat)

  # begin partioning in  x direction
  else:
    nSubdomainsXFloat = min(float(NumberGlobalXElements) / OptimalSideLength, nAtomsX)
    # now if nAtomX is smaller than the optimal nSubdomainsXFloat, we must take nAtomX instead
    # nSubdomainsXFloat is given
    # nSubdomainsYFloat = NumberGlobalYElements / OptimalSideLength
    # nSubdomainsZFloat = NumberGlobalZElements / OptimalSideLength
    # nSubdomains = nSubdomainsXFloat * nSubdomainsYFloat * nSubdomainsZFloat 
    #         = nSubdomainsXFloat * NumberGlobalYElements * NumberGlobalZElements / (OptimalSideLength)**2
    # => OptimalSideLength = (nSubdomainsXFloat * NumberGlobalYElements * NumberGlobalZElements / nSubdomains)**(1./2)
    # 

    if debug:
      print "nAtomsX={}, OptimalSideLength={}, x={}, x/Opt={}, nSubdomainsXFloat={}".format(nAtomsX, OptimalSideLength, NumberGlobalXElements, float(NumberGlobalXElements) / OptimalSideLength, nSubdomainsXFloat)

    OptimalSideLength = (nSubdomainsXFloat * NumberGlobalYElements * NumberGlobalZElements / NumberOfDomains)**(1./2)
    if debug:
      print "new OptimalSideLength={}".format(OptimalSideLength)

    if abs(OptimalSideLength) < 1e-8:
      #print "warning: OptimalSideLength is zero! p,x,y,z,ax,ay,az=",p,x,y,z,ax,ay,az
      return 0
      
    nSubdomainsYFloat = min(float(NumberGlobalYElements) / OptimalSideLength, nAtomsY)
    if debug:
      print "nAtomsY={}, OptimalSideLength={}, y={}, y/Opt={}, nSubdomainsyFloat={}".format(nAtomsY, OptimalSideLength, NumberGlobalYElements, float(NumberGlobalYElements) / OptimalSideLength, nSubdomainsYFloat)

    # now if nAtomY is smaller than the optimal nSubdomainsYFloat, take nAtomsY
    # nSubdomainsXFloat and nSubdomainsYFloat are given
    # nSubdomainsZFloat = NumberGlobalZElements / OptimalSideLength
    # nSubdomains = nSubdomainsXFloat * nSubdomainsYFloat * nSubdomainsZFloat
    #         = nSubdomainsXFloat * nSubdomainsYFloat * NumberGlobalZElements / OptimalSideLength
    # => OptimalSideLength = nSubdomainsXFloat * nSubdomainsYFloat * NumberGlobalZElements / nSubdomains
    # nSubdomainsZFloat = NumberGlobalZElements / (nSubdomainsXFloat * nSubdomainsYFloat * NumberGlobalZElements / nSubdomains)
    #               = (NumberGlobalZElements * nSubdomains) / (nSubdomainsXFloat * nSubdomainsYFloat * NumberGlobalZElements)
    #               = nSubdomains / (nSubdomainsXFloat * nSubdomainsYFloat)
    #
     
    nSubdomainsZFloat = min(float(NumberOfDomains) / (nSubdomainsXFloat * nSubdomainsYFloat), nAtomsZ)

    if debug:
      print "nAtomsZ={}, nSubdomainsZFloat={}, final: {}".format(nAtomsZ, float(NumberOfDomains) / (nSubdomainsXFloat * nSubdomainsYFloat), nSubdomainsZFloat)
    
    
  if debug:
    print "nSubdomainsFloat={},{},{}={}".format(nSubdomainsXFloat,nSubdomainsYFloat,nSubdomainsZFloat,nSubdomainsXFloat*nSubdomainsYFloat*nSubdomainsZFloat)

  nSubdomainsX = max(1, int(np.ceil(nSubdomainsXFloat)))    # try to round up to use the maximum number of processes possible, if value gets to high, it will be decreased anyway
  nSubdomainsY = max(1, int(np.ceil(nSubdomainsYFloat)))
  nSubdomainsZ = max(1, int(np.ceil(nSubdomainsZFloat)))

  if debug:
    print "nSubdomains: {},{},{}={} ".format(nSubdomainsX, nSubdomainsY, nSubdomainsZ, nSubdomainsX*nSubdomainsY*nSubdomainsZ)

  # adjust number of subdomains such that total number is <= number of domains (ideally '=')
  while (nSubdomainsX*nSubdomainsY*nSubdomainsZ > NumberOfDomains):
    diffX = nSubdomainsX - nSubdomainsXFloat
    diffY = nSubdomainsY - nSubdomainsYFloat
    diffZ = nSubdomainsZ - nSubdomainsZFloat
    
    if diffX >= diffY and diffX >= diffZ:
      if nSubdomainsX != 1:
        nSubdomainsX -= 1
      elif diffY >= diffZ:
        if nSubdomainsY != 1:
          nSubdomainsY -= 1
        else:
          nSubdomainsZ -= 1
      else:
        if nSubdomainsZ != 1:
          nSubdomainsZ -= 1
        else:
          nSubdomainsY -= 1
          
    elif diffY >= diffZ:    # diffY >= diffZ, diffY > diffX
      if nSubdomainsY != 1:
        nSubdomainsY -= 1
      else:
        if diffX >= diffZ:
          if nSubdomainsX != 1:
            nSubdomainsX -= 1
          else:
            nSubdomainsZ -= 1
        else:
          if nSubdomainsZ != 1:
            nSubdomainsZ -= 1
          else:
            nSubdomainsX -= 1
        
    else:       # diffZ > diffY, diffZ >= diffX
      if nSubdomainsZ != 1:
        nSubdomainsZ -= 1
      else:
        if diffX >= diffY:
          if nSubdomainsX != 1:
            nSubdomainsX -= 1
          else:
            nSubdomainsY -= 1
        else:
          if nSubdomainsY != 1:
            nSubdomainsY -= 1
          else:
            nSubdomainsX -= 1
    
    if debug:  
      print "diff:{},{},{}, nSubdomains: {},{},{}={} ".format(diffX,diffY,diffZ, nSubdomainsX, nSubdomainsY, nSubdomainsZ, nSubdomainsX*nSubdomainsY*nSubdomainsZ)
    
  if debug:
    print "nSubdomains: {},{},{}={} ".format(nSubdomainsX, nSubdomainsY, nSubdomainsZ, nSubdomainsX*nSubdomainsY*nSubdomainsZ)

  # determine shape of subdomain, i.e. nAtomsPerSubdomain
  # nAtomsPerSubdomainX * nSubdomainsX = nAtomsX  =>  nAtomsPerSubdomainX = nAtomsX / nSubdomainsX

  nAtomsPerSubdomainX = int(np.ceil(float(nAtomsX) / nSubdomainsX))
  nAtomsPerSubdomainY = int(np.ceil(float(nAtomsY) / nSubdomainsY))
  nAtomsPerSubdomainZ = int(np.ceil(float(nAtomsZ) / nSubdomainsZ))
  nAtomsPerSubdomain = nAtomsPerSubdomainX*nAtomsPerSubdomainY*nAtomsPerSubdomainZ

  # decrease number of subdomains to exclude now empty subdomains
  nEmptySubdomainsX = int(float(nAtomsPerSubdomainX*nSubdomainsX - nAtomsX) / nAtomsPerSubdomainX)
  nEmptySubdomainsY = int(float(nAtomsPerSubdomainY*nSubdomainsY - nAtomsY) / nAtomsPerSubdomainY)
  nEmptySubdomainsZ = int(float(nAtomsPerSubdomainZ*nSubdomainsZ - nAtomsZ) / nAtomsPerSubdomainZ)

  nEmptySubdomains = nSubdomainsX*nSubdomainsY*nSubdomainsZ - (nSubdomainsX-nEmptySubdomainsX)*(nSubdomainsY-nEmptySubdomainsY)*(nSubdomainsZ-nEmptySubdomainsZ)

  if debug:
    print "nEmptySubdomains:{},{},{}, total:{}".format(nEmptySubdomainsX,nEmptySubdomainsY,nEmptySubdomainsZ, nEmptySubdomains)

  nSubdomainsX -= nEmptySubdomainsX
  nSubdomainsY -= nEmptySubdomainsY
  nSubdomainsZ -= nEmptySubdomainsZ
  nSubdomains = nSubdomainsX*nSubdomainsY*nSubdomainsZ

  nUnusedSubdomains = NumberOfDomains - nSubdomains 

  return nSubdomains

if __name__ == "__main__":
  p = int(sys.argv[1])
  x = int(sys.argv[2])
  y = int(sys.argv[3])
  z = int(sys.argv[4])
  ax = int(sys.argv[5])
  ay = int(sys.argv[6])
  az = int(sys.argv[7])
  print "p=",p,",x=",x,",y=",y,",z=",z,",ax=",ax,",ay=",ay,",az=",az
  
  used_number_of_processes = number_of_processes(p,x,y,z,ax,ay,az,True)
  print "used_number_of_processes: ", used_number_of_processes
  