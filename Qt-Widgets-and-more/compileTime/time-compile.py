#!/usr/bin/env python3
#
# Usage: The idea is that this script can be edited by hand for the project you work on
#   There's no 'one fits all' solution for this
#
# You might need to adapt the following vars for your project:
#   - ITERATIONS
#   - PCH_FILENAME
#   - EXTRA_CMAKE_ARGS
#
# Note: The actual tests which are being run can be controlled by toggling (uncomment/comment)
# the functions at the end of of this file.


import glob
import multiprocessing
import os
import os.path
import shutil
import re
import subprocess
import sys
import time

# BEGIN: Constants

ROOT=os.getcwd()
BUILDROOT=os.path.join(ROOT, "build")
ITERATIONS=1
FORREAL=True
CCACHE_PATH="/usr/lib/ccache"

PCH_FILENAME="ruqola_pch.h"
EXTRA_CMAKE_ARGS=["-DUSE_PRECOMPILED_HEADERS=OFF"]

# END: Constants

CURRENT_TIMINGFILE=None

def runCommand(cmd):
    print(f"Executing: {' '.join(cmd)}")
    if FORREAL:
        process = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, universal_newlines=True)
        stdout, stderr = process.communicate()
        if process.returncode != 0:
            print(f"Error: Process returned {process.returncode}!")
            print("stdout:\n\n")
            print(stdout)
            print("stderr:\n\n")
            print(stderr)

    return process.returncode == 0

def nukeBuildDir():
    if FORREAL:
        if os.path.exists(BUILDROOT):
            shutil.rmtree(BUILDROOT)
        os.mkdir(BUILDROOT)

def clearCCache():
    return runCommand(["/usr/bin/ccache", "-C"])

def runCMake(clang, ninja, define=None):
    command=["cmake"]

    if clang:
        command = command + ["-DCMAKE_C_COMPILER=clang", "-DCMAKE_CXX_COMPILER=clang++"]
    else:
        command = command + ["-DCMAKE_C_COMPILER=gcc", "-DCMAKE_CXX_COMPILER=g++"]
    if ninja:
        command = command + ["-G", "Ninja"]

    if define:
        command = command + ["-DCMAKE_CXX_FLAGS=-D" + define]

    command = command + EXTRA_CMAKE_ARGS + [".."]
    return runCommand(command)

def compile(ninja):
    os.environ["MAKEFLAGS"] = f"-j{multiprocessing.cpu_count()}"
    command = ["make", "-j", f"{multiprocessing.cpu_count()}"]
    if ninja:
        command = ["ninja"]
    return runCommand(command)

def setOutputFile(filename):
    global CURRENT_TIMINGFILE
    CURRENT_TIMINGFILE=os.path.join(ROOT, filename)
    writeHeader()

def writeHeader():
    with open(CURRENT_TIMINGFILE, "w") as f:
        f.write("compiler,build system,ccache on,stage,time\n")

def addOutputLine(clang,ninja,step,time):
    with open(CURRENT_TIMINGFILE, "a+") as f:
        ccacheon = "ccache" in os.environ["PATH"]
        f.write("%s,%s,%s,%s,%s\n" % ("clang" if clang else "gcc", "ninja"  if ninja else "make", "yes" if ccacheon else "no", step, int(round(time))))

def makeClean(ninja):
    return runCommand(["ninja" if ninja else "make", "clean"])

def timeAndWrite(clang,ninja,step):
    start=time.time()
    success = compile(ninja)
    end = time.time()
    addOutputLine(clang, ninja, step, (end-start) if success else -1)

def setOrUnsetCCacheInPath(doInclude):
    path = os.environ["PATH"].split(":")
    path = filter(lambda item: "ccache" not in item, path)
    if doInclude:
        path = [CCACHE_PATH] + path
    os.environ["PATH"] = ":".join(path)


def oneGoWithCompilterAndBuildSystem(clang,ninja):
    clearCCache()
    nukeBuildDir()
    os.makedirs(BUILDROOT, exist_ok=True)
    os.chdir(BUILDROOT)

    runCMake(clang=clang, ninja=ninja)
    timeAndWrite(clang, ninja, "full build")

    # rebuild after make clean
    clearCCache()
    makeClean(ninja)
    timeAndWrite(clang, ninja, "clean build")


def compileAndBuildSystemTest():
    setOutputFile("compilerAndBuild.csv")
    setOrUnsetCCacheInPath(0)
    for round in range(ITERATIONS):
        print("compileAndBuildSystemTest------> Round %d of %d" % (round+1, ITERATIONS))
        for ninja in [0, 1]:
            for clang in [0,1]:
                oneGoWithCompilterAndBuildSystem(clang=clang,ninja=ninja)


def ccacheTest():
    setOutputFile("ccache.csv")

    for useccache in [0,1]:
        setOrUnsetCCacheInPath(useccache)
        for round in range(ITERATIONS):
            print("ccacheTest------> Round %d of %d (using CCache=%s)" % (useccache*ITERATIONS + round+1, ITERATIONS*2,"yes" if useccache else "no"))
            oneGoWithCompilterAndBuildSystem(clang=1, ninja=1)


def runPCHMutation(headers):
    for index in range(len(headers)+1):
        subList = headers[:index]
        if FORREAL:
            with open(os.path.join(ROOT, PCH_FILENAME), "w") as f:
                for x in subList:
                    f.write("#include <%s>\n" % x)

        print(f"pchTest------> Using headers in PCH: {subList}")

        nukeBuildDir()
        os.makedirs(BUILDROOT, exist_ok=True)
        os.chdir(BUILDROOT)
        runCMake(clang=1,ninja=1)
        compile(ninja=1)
        for round in range(ITERATIONS):
            print("pchTest------> Round %d of %d" % (index*ITERATIONS + round+1, ITERATIONS*len(headers)+1))
            clearCCache()
            makeClean(ninja=1)
            timeAndWrite(clang=1, ninja=1, step="/" + "/".join(subList))

def pchTest():
    setOutputFile("PCH.csv")
    setOrUnsetCCacheInPath(0)

    runPCHMutation(["QtCore", "QtGui", "QtWidgets"]) # "chrono", "cmath", "optional", "mutex", "array", "vector", "numeric", "algorithm"
    #runPCHMutation(["QtCore", "QtGui", "QtWidgets"])


# -------- pchMostUsedTest
REGEXP = re.compile("^#include *<(Q.*/)?([a-zA-Z_]+)>")

def countIncludes(filename, map):
    with open(filename) as fp:
        for line in fp.readlines():
            match = REGEXP.match(line)
            if match:
                str = match.group(2)
                if str in map:
                    map[str]= map[str]+1
                else:
                    map[str] = 1

def findSystemIncludes():
    map = {}
    for filename in glob.glob(ROOT + "/**/*.cpp", recursive=1)+ glob.glob(ROOT + "/**/*.h",recursive=1) :
        if "3rdparty" in filename or "prefix" in filename or "external" in filename:
            continue
        countIncludes(filename, map)
    list = sorted(map.items(), key=lambda x: x[1])
    list.reverse()
    with open("Most-Used-Includes.csv", "w") as f:
        for key,count in list:
            f.write(f"{key}, {count}\n")
    return [key for (key,count) in list]

def pchMostUsedTest():
    setOutputFile("PCH-most-used.csv")
    setOrUnsetCCacheInPath(0)

    nukeBuildDir()
    os.chdir(BUILDROOT)

    # We need to build it all first, so we get all the ui_* files into existance
    runCMake(clang=1,ninja=1)
    compile(ninja=1)
    list = findSystemIncludes()

    steps=len(list)
    for stage in range(steps):
        with open(os.path.join(ROOT, PCH_FILENAME), "w") as f:
            for i in range(stage):
                f.write("#include<%s>\n" % list[i])

        runCMake(clang=1,ninja=1)
        compile(ninja=1)
        for round in range(ITERATIONS):
            print("pchMostUsedTest------> Round %d of %d" % (stage*ITERATIONS + round+1, ITERATIONS*steps))
            makeClean(ninja=1)
            timeAndWrite(clang=1, ninja=1, step="%d" % stage)


# USAGE: Toggle (uncomment/comment) your test scenarios as wanted:

#findSystemIncludes()
#compileAndBuildSystemTest()
#ccacheTest()
#pchTest()
#pchMostUsedTest()
