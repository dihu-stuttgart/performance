#!/usr/bin/python

file1 = open("log_fixed_gmres2.csv")
file2 = open("log_fixed_gmres3.csv",'w')

for i,line in enumerate(file1):
  nSemicolons = line.count(';')
  print nSemicolons
  if nSemicolons == 83 or i == 0 or line[0] == '#':
    file2.write(line)
    
file1.close()
file2.close()
