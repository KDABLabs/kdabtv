#! env python
import subprocess, re, sys,os, os.path, shutil, time, glob

ITERATIONS=10
TIMINGFILE="/home/blackie/timing.csv"

def runCommand(cmd):
    print(" ".join(cmd))
    process = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    res = process.communicate()[0]
    #print(res)

def writeHeader():
    FILE = open(TIMINGFILE, "w")
    FILE.write("using cache,hot cache,time\n")

def addOutputLine(cacheEnabled, hotCache,time):
    FILE = open(TIMINGFILE, "a+")
    FILE.write("%s,%s,%s\n" % ("yes" if cacheEnabled else "no", "yes"  if cacheEnabled and hotCache else ("no" if cacheEnabled else "-"), time))

def timeAndWrite(cacheEnabled, hotCache):
    start=time.time()
    runCommand(["gdb", "-n", "-x", "go.gdb", "/home/blackie/KDAB/build-KDABViewer-Desktop_Qt_5_15_2_GCC_64bit-Debug/bin/KDABViewer"])
    end = time.time()
    addOutputLine(cacheEnabled, hotCache, end-start)

def writeSettings(cacheEnabled):
    FILE=open("go.gdb", "w")
    FILE.write("set index-cache %s\n" % ("on" if cacheEnabled else "off"))
    FILE.write("run\n")
    FILE.write("quit\n")
    
def nukeCache():
    shutil.rmtree("/home/blackie/.cache/gdb")
    
# ---------------------------- Test funcitons

def go():
    writeHeader()
    
    writeSettings(0)
    for i in range(ITERATIONS):
        timeAndWrite(0, 0)
    
    writeSettings(1)
    for i in range(ITERATIONS):
        nukeCache()
        timeAndWrite(1, 0)

    for i in range(ITERATIONS):
        timeAndWrite(1, 1)
        
go()    
