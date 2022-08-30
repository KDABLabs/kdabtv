#!/usr/bin/env python3

import re, subprocess, time, os, sys, argparse

def configFile(name):
    if args.configDir:
        return args.configDir[0] + "/" + name
    else:
        return name

def export():
    IN=open(configFile(".clang-tidy.checks"), "r")
    OUT=open(".clang-tidy", "w")
    OUT.write("# This is a generated file do not edit but instead edit .clang-tidy.checks and .clang-tidy.settings\n\n")

    OUT.write("Checks: '")

    for line in IN.readlines():
        index = line.find("#")
        if index != -1:
            line=line[:index]
        line = line.rstrip()
        if line != "":
            OUT.write(line + ",")

    OUT.write("'\n\n")

    if os.path.exists(configFile(".clang-tidy.settings")):
        IN=open(configFile(".clang-tidy.settings"), "r")
        OUT.write(IN.read())

def fetchChecks():
    result = []
    regexp = re.compile("^b\"'([^']*)'.*")
    proc = subprocess.Popen( ["clang-tidy", "--explain-config"], stdout=subprocess.PIPE)
    for line in proc.stdout:
        match = regexp.match(str(line))
        if not match:
            print("Warning unable to parse line: %s" % line)
        else:
            result.append(match.group(1))
    return result


### This isn't used right now, but will be included in the file in QWAM (once this has passed review, and then deleted from here)
def timeRules():
    rules = fetchChecks()
    result = {}
    ruleNo=0
    for rule in rules:
        print("%s/%s - %s" % (ruleNo, len(rules), rule))
        ruleNo = ruleNo+1

        total = 0
        iterations=5
        for iteration in range(iterations):
            start = time.time()
            os.system("clang-tidy -config=\"{Checks: '%s'}\" -p ../build-KDABViewer-Qt_6_3_0-Debug ./TimeSheetReview/TimeSheetReviewWidget.cpp" % rule)
            end = time.time()
            print(end-start)
            total = total + end-start
        result[rule] = total / iterations
    print(result)


def printChecks():
    print("Enabled checks:")
    checks = fetchChecks()
    for check in checks:
        print(check)
    print ("Total: %s" % len(checks))


################################ MAIN #################################
if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        formatter_class=argparse.RawDescriptionHelpFormatter,
        description = """
    Script to generate .clang-tidy from .clang-tidy.checks and .clang-tidy.settings

    This script solves three problems if you split your 'checks' line across multiple lines
    1) You are not allowed to add commented in the string, as that will comment out the rest of the string
    Example:
    Checks: '*,   # I want everything
      -android-*, # Except the android checks
    '

    This gets converted to:
    Checks: '*,  # I want everything -android-*, # Except the android checks'

    2) When splitting the check across multiple lines, it is easy to forget a command at the end of a line:
    Checks: '*
      -android-*
    '

    Translates into: Checks: "* -android-*", while it should have said Checks: "*, -android-*"

    3) While clang-tidy itself understand the checks split over multiple lines,
       Qt Creator doesn't, so you can't simply choose 'Use .clang-tidy file' in Qt Creator

    This script solves all three issues, by specifying the checks in a separate file '.clang-tidy.checks"
    which is then converted to the .clang-tidy file.
    In addition you can specify settings in '.clang-tidy.settings'

    == Example of .clang-tidy.checks file: ==
    # I Want all checks
    *
    -android-* # except the android checks

    Comments are allowed, and checks are /NOT/ separated by comma, but instead one check per line.
    """)
    parser.add_argument("--list-checks", dest="listChecks", action='store_true', help="print the checks active")
    parser.add_argument("--config-dir", dest="configDir", nargs=1, help="Directory containing .clang-tidy.checks and .clang-tidy.settings")
    parser.add_argument("--print-cmake-snippet", dest="printCMakeSnippet", action='store_true', help="print a piece of code you can add to CMake")
    args = parser.parse_args()

    if args.printCMakeSnippet:
        configDir = "${CMAKE_CURRENT_SOURCE_DIR}" + ("/" + args.configDir[0] if args.configDir else "")
        print("""
        Insert this to your CMakeLists.txt file to get .clang-tidy automatically generated:
        find_package(Python3 COMPONENTS Interpreter REQUIRED)
        add_custom_command(
           OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy
           COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/scripts/updateClangTidy.py %s
           DEPENDS %s/.clang-tidy.checks %s/.clang-tidy.settings
           WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )

        add_custom_target(clang_tidy_generator ALL DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy)

        This code assumes that this script is in the scripts subdirectory, if that isn't the case then adjust the above code

        """ % ("--config-dir " + args.configDir[0] if args.configDir else "", configDir, configDir))
        sys.exit(0)

    if not os.path.exists(configFile(".clang-tidy.checks")):
        print("*** Error: Failed to find the file %s ***\n\n" % configFile(".clang-tidy.checks"))
        parser.print_help()
        sys.exit(-1)


    export()
    if args.listChecks:
        printChecks()

