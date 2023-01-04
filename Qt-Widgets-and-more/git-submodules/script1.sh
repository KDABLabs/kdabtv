#! /bin/bash

. shared.sh

##########
title "First of all get a clean working directory"
run "rm -rf $ROOT"
run "mkdir $ROOT"
run "cd $ROOT"
run "git init --bare MyApplication.git"

##########
title "Clone into MyApplication and build"
run "git clone MyApplication.git MyApplication"
run "cd MyApplication"
run "cp $SRCDIR/step1/main.cpp ."

cat main.cpp

run "cmake-project -q none"
comment "Script available in https://github.com/KDAB/KDToolBox"
cat CMakeLists.txt

run "echo build > .gitignore"
run "git add main.cpp CMakeLists.txt .gitignore"
run "git commit -m 'Basic Setup'"

run "mkdir build"
run "cd build"
run 'cmake ..'
run "make"
run "./MyApplication"


##########
title "So it compiled, let's add the sub-module"
run "cd .."
run "git submodule add https://github.com/KDAB/KDAlgorithms.git"
run "ls KDAlgorithms"

run "git status"
run "git config --global status.submodulesummary 1"
run "git status"
run "cat .gitmodules"

run "cp $SRCDIR/step2/main.cpp ."
cat main.cpp

run "cp $SRCDIR/step2/CMakeLists.txt ."
cat CMakeLists.txt

run "cd build"
run "cmake .."
run "make"
run "./MyApplication"

##########
title "Commit our stuff and push it"
run "cd .."
run "git add main.cpp CMakeLists.txt"
run "git commit -m'Now with submodules'"
run "git push"


##########
title "Now lets try a clean checkout"
run "cd .."
run "rm -rf MyApplication"
run "git clone MyApplication.git MyApplication"
run "cd MyApplication"
run "mkdir build"
run "cd build"

run 'cmake ..'

run "cd .."
run "ls -l KDAlgorithms"
run "git submodule update --recursive --init"
run "ls -l KDAlgorithms"

run "cd build"
run 'cmake ..'
run "make"
run "./MyApplication"

##########
title "A solution is CheckSubmoduleExists"
run "cd ../.."
run "rm -rf MyApplication"
run "git clone MyApplication.git MyApplication"
run "cd MyApplication"

run "mkdir cmake"
run "cp $SRCDIR/step3/CheckSubmoduleExists.cmake cmake/"
cat cmake/CheckSubmoduleExists.cmake

run "cp $SRCDIR/step3/CMakeLists.txt ."
cat CMakeLists.txt

run "mkdir build"
run "cd build"
run 'cmake ..'

##########
title "An alternative is to use --recurse-submodules option"
run "cd ../.."
run "rm -rf MyApplication"
run "git clone --recurse-submodules -j8 MyApplication.git MyApplication"
comment "Time for an alias?"
comment 'git config --global alias.cln "clone --recurse-submodules -j8"'
comment "But if you forget to use that, maybe keep this as a backup...."
comment 'git config --global alias.fix-submodules "submodule update --recursive --init"'

run "cd MyApplication"
run "mkdir build"
run "cd build"
run 'cmake ..'
run "make"
run "./MyApplication"

run 'echo "Game Over, Player 1"'

