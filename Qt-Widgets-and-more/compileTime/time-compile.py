import subprocess, re, sys,os, os.path, shutil, time, glob

ROOT="/home/blackie/dump/KDABViewer"
BUILDROOT=ROOT+"/build"
ITERATIONS=5
FOREAL=1
CCACHE="/usr/lib/ccache"

def runCommand(cmd):
    print(" ".join(cmd))
    if FOREAL:
        process = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        res = process.communicate()[0]
        #print(res)

def nukeBuildDir():
    if FOREAL:
        shutil.rmtree(BUILDROOT)
        os.mkdir(BUILDROOT)

def clearCCache():
    runCommand(["/usr/bin/ccache", "-C"])

def runCMake(clang, ninja, define=None):
    command=["cmake"]

    if clang:
        command = command + ["-DCMAKE_CXX_COMPILER=clang++"]
    if ninja:
        command = command + ["-G", "Ninja"]

    if define:
        command = command + ["-DCMAKE_CXX_FLAGS=-D" + define]

    command = command + [".."]
    runCommand(command)

def compile(ninja):
    os.environ["MAKEFLAGS"]="-j 16"
    command = ["make", "-j", "16"]
    if ninja:
        command = ["ninja"]
    runCommand(command)

def setOutputFile(filename):
    global TIMINGFILE
    TIMINGFILE="/home/blackie/profiling/"+filename
    writeHeader()


def writeHeader():
    FILE = open(TIMINGFILE, "w")
    FILE.write("compiler,build system,cclang on,stage,time\n")

def addOutputLine(clang,ninja,step,time):
    FILE = open(TIMINGFILE, "a+")
    ccacheon = "ccache" in os.environ["PATH"]
    FILE.write("%s,%s,%s,%s,%s\n" % ("clang" if clang else "gcc", "ninja"  if ninja else "make", "yes" if ccacheon else "no", step, int(round(time))))

def makeClean(ninja):
    runCommand(["ninja" if ninja else "make", "clean"])

def timeAndWrite(clang,ninja,step):
    start=time.time()
    compile(ninja)
    end = time.time()
    addOutputLine(clang,ninja, step, end-start)

def setOrUnsetCCacheInPath(doInclude):
    path = os.environ["PATH"].split(":")
    path = filter(lambda item: "ccache" not in item, path)
    if doInclude:
        path = [CCACHE] + path
    os.environ["PATH"] = ":".join(path)


# ---------------------------- Test funcitons

def oneGoWithCompilterAndBuildSystem(clang,ninja):
    clearCCache()
    nukeBuildDir()

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
        if FOREAL:
            FILE = open(ROOT + "/KDABViewer_pch.h","w")
            for x in subList:
                FILE.write("#include <%s>\n" % x)
            FILE.close()

        nukeBuildDir()
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

    runPCHMutation(["QtWidgets", "QtGui", "QtCore", "KDChart", "memory", "functional"]) # "chrono", "cmath", "optional", "mutex", "array", "vector", "numeric", "algorithm"
    runPCHMutation(["QtCore", "QtGui", "QtWidgets"])



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
        if "3rdparty" in filename or "prefix" in filename or "xternal" in filename:
            continue
        countIncludes(filename, map)
    list = sorted(map.items(), key=lambda x: x[1])
    list.reverse()
    print(list)
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
        with open(ROOT + "/KDABViewer_pch.h","w") as FILE:
            for i in range(stage):
                FILE.write("#include<%s>\n" % list[i])

        runCMake(clang=1,ninja=1)
        compile(ninja=1)
        for round in range(ITERATIONS):
            print("pchMostUsedTest------> Round %d of %d" % (stage*ITERATIONS + round+1, ITERATIONS*steps))
            makeClean(ninja=1)
            timeAndWrite(clang=1, ninja=1, step="%d" % stage)


#compileAndBuildSystemTest()
#ccacheTest()
#pchTest()
#pchMostUsedTest()
