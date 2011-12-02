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
  newName = newName + "/_net_" + piecesOfPieces[0] + "-test.c"

  newF = open(newName, 'w')
  oldF = open(f,'r')
  
  #rewrite the -nettest file into the -test file
  newF.write("#include \"ct/netTestRunner.h\"")
  includes = []
  defines = []
  declarations = []
  macros = []
  connections = []
  functionNames = []

  for line in oldF:
    #ignore comments
    isComment = line.find("//")
    if isComment==-1:
      
      isInclude = line.find("#include")
      if isInclude!=-1:
	includes.append(line)
      
      #keep macro defintions, which are connections
      isConnection = line.find("#define NETTEST")
      if isConnection!=-1:
	macros.append(line)
	#[0] = #define [1] = NETTEST* [2]="nettest*"
	
      elif line.find("#define")!=-1:
	#keep any defines
	defines.append(line)
      
      isFunction = line.find("int nettest")
      if isFunction!=-1:
	#forward declare the nettest functions
	hasBracket = line.find("{");
	if hasBracket==-1:
	  declare = line + ";"
	  declarations.append(declare)
	else:
	  splitLine = line.split('{')
	  declare = splitLine[0]
	  declare = declare.strip()
	  declare = declare + ";"
	  declarations.append(declare) 
	
	#get the function name
	getNameRA = line.split("(")
	getName = getNameRA[0]
	getNameRA = getName.split(" ")
	getName = getNameRA[1]
	getName = getName.strip()
	functionNames.append(getName)
  
  #if the function name has a macro definition, make the connection
  for name in functionNames:
    for line in macros:
      dividedDefine = line.split(" ")
      m = dividedDefine[2]
      m = m.strip()
      m = m.strip("\"")
      if(m==name):
	con = "{\"" + name +"\", " + name + "," + dividedDefine[1] + "},"
	connections.append(con)
  
  #write to the new file
  newF.write("\n")
  for iThing in includes:
    newF.write(iThing)
  newF.write("\n")
  for thing in defines:
    newF.write(thing)
  newF.write("\n")
  for mThing in macros:
    newF.write(mThing)
  newF.write("\n")
  for dThing in declarations:
    newF.write(dThing)
  
  newF.write("\n")
  newF.write("\n")
  newF.write("static NetConnection connections[] = {\n")
  #and now we write connections
  for thing in connections:
    line = "\t"+thing+"\n"
    newF.write(line)
  newF.write("\t{NULL, NULL, NULL}\n")
  newF.write("};\n\n")
  
  #write the function
  for thing in functionNames:
    line = "void cttest_"+thing+"(void) {\n"
    newF.write(line)
    newF.write("\trunSocketTests(connections);\n}");
    newF.write("\n\n")
  
  newF.close()
  oldF.close()

#f in files loop end
  
