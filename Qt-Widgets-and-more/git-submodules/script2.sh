#! /bin/bash

. shared.sh

##########
title "First of all get a clean working directory"
run "rm -rf $ROOT"
run "mkdir $ROOT"
run "cd $ROOT"

##########
title 'Set up kdalgorithms and make an initial commit there'
run 'git init --bare kdalgorithms.git'
run 'git clone kdalgorithms.git kdalgorithms-Jesper'
run 'cd kdalgorithms-Jesper'
run 'echo "We can now sort things" > README'
run 'git add README'
run 'git commit -m"We can now sort things"'
run 'git push'

##########
title 'Kirsi creates the MyApplication repository'
run 'cd ..'
run 'git init --bare MyApplication.git'
run 'git clone MyApplication.git MyApplication-Kirsi'
run 'cd MyApplication-Kirsi'
run 'git submodule add ../kdalgorithms.git'
comment 'Security issue on Ubuntu: https://bugs.launchpad.net/ubuntu/+source/git/+bug/1993586'
run 'git config --global protocol.file.allow always'
run 'git submodule add ../kdalgorithms.git'
run 'git commit -m"Version 1: MyApplication with sorting"'
run 'git push'

##########
title 'Jesper is back making some changes to kdalgorithms'
run 'cd ../kdalgorithms-Jesper'
run 'echo "Now it can brew coffee too" >> README'
run 'git add README'
run 'git commit -m"Now it can brew coffee too"'
run 'git push'

##########
title "Kirsi wants coffee so she pulls the new version"
run 'cd ../MyApplication-Kirsi'
run 'git pull'
run 'cd kdalgorithms'
run 'git pull'
run 'git log'
run 'cd ..'
run 'git status'
run 'git add kdalgorithms'
run 'git commit -m"Version 2: MyApplication now with coffee"'

##########
title "Before she manage to push, Nuno comes around start working too"
run 'cd ..'
run 'git clone MyApplication.git MyApplication-Nuno'
run 'cd MyApplication-Nuno'
run 'ls kdalgorithms'
run 'git submodule update --recursive --init'
run 'git log'

##########
title "Now it is Kirsi's turn, she will push her changes"
run 'cd ../MyApplication-Kirsi'
run 'git push'

##########
title "Nuno hears about this and want those changes right away!"
run 'cd ../MyApplication-Nuno'
run 'git pull'
run 'git log'
run 'git status'

run 'git diff'
run 'git diff --submodule'
run 'git config --global diff.submodule log'
run 'git diff'

##########
title "Nuno realizes that he need to pull to get the changes from Kirsi"
comment "From the documentation of git submodule:"
comment "Update the registered submodules to match what the superproject expects by cloning missing submodules,"
comment "fetching missing commits in submodules and updating the working tree of the submodules."
run 'git submodule update --recursive --init'
run 'git status'

##########
title "Jesper isn't done yet making changes to kdalgorithms"
run 'cd ../kdalgorithms-Jesper'
run 'echo "Everyone need welding under water" >> README'
run 'git add README'
run 'git commit -m"Everyone need welding under water"'
run 'git push'

##########
title "Kirsi want those changes and have learned about --recurse-submodules"
run 'cd ../MyApplication-Kirsi'
run 'git pull --recurse-submodules'
run 'git status'
run 'git show'

##########
title "We still need to manually point to the new SHA"
run 'cd kdalgorithms'
run 'git pull'
run 'cd ..'
run 'git status'
run 'git add kdalgorithms'
run 'git commit -m"Version 3: Now MyApplication can also weld under water"'
run 'git push'

##########
title "Nuno wants it too now, and also tries using --recurse-submodules"
run 'cd ..'
run 'cp -a MyApplication-Nuno MyApplication-Kevin'
comment "You know how some developers just steal other people's code :-)"

run 'cd MyApplication-Nuno'
run 'git pull --recurse-submodules'
run 'git status'
run 'git show'

##########
title "Kevin of course knows a setting to avoid providing the switch"
run 'git config --global submodule.recurse true'
run 'cd ../MyApplication-Kevin'
run 'git pull'
run 'git status'
run 'git show'

##########
title "Finally, a very common problem - switching branches with sub-modules"
run 'git config --unset --global submodule.recurse'
run 'git log kdalgorithms'
run 'git switch -d HEAD~'
comment 'Remember: this was using a different SHA of the submodule'
run 'git status'
run 'git log kdalgorithms'
run 'cd kdalgorithms'
run 'git log'
run 'cd ..'

comment "Remember the cure:"
comment "From the documentation of git submodule:"
comment "Update the registered submodules to match what the superproject expects by cloning missing submodules,"
comment "fetching missing commits in submodules and updating the working tree of the submodules."

run 'git submodule update --recursive --init'
run 'git status'

##########
title "Go back to master"
run 'git switch master'
run 'git submodule update --recursive --init'
run 'git status'
run 'git log kdalgorithms'
run 'cd kdalgorithms'
run 'git log'
run 'cd ..'

##########
title "Now with the setting for recusing sub-modules"
run 'git config --global submodule.recurse true'
run 'git config --global push.recurseSubmodules no'
run 'git switch -d HEAD~'
run 'git status'
run 'git log kdalgorithms'
run 'cd kdalgorithms'
run 'git log'

run "echo 'game over, player 1'"
