# -*- coding: utf-8 -*-
#! /usr/bin/python

import glob
import sys

#get the directory to search for -nettest.c files
path = sys.path[0]

pieces = []
pieces = path.split('/')

l = len(pieces)

newpath = ""
for i in range(1,l-1):
  newpath = newpath + "/" + pieces[i]

#search for -nettest.c files in the directory
search = newpath + "/" + "*-nettest.c"
files = glob.glob(search)

#for each -nettest.c file:
for f in files:
  #make a new file with the name *-test.c
  newName = f
  newPieces = newName.split('/')
  l = len(newPieces)
  newName = ""
  for i in range(1,l-1):
    newName = newName +  "/" + newPieces[i]
  piecesOfPieces = newPieces[l-1].split('-')
  newName = newName + "/" + piecesOfPieces[0] + "-test.c"

  newF = open(newName, 'w')
  oldF = open(f,'r')
  
  #rewrite the -nettest file into the -test file
  for line in oldF:
    isNettest = line.find("nettest")
    if isNettest==-1:
      newF.write(line)
    else:
      splitLine = line.split('nettest')
      newLine = splitLine[0] + "cttest" + splitLine[1]
      newF.write(newLine)
    
  newF.close()
  oldF.close()
  