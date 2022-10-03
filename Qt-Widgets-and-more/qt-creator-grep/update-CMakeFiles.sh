#! /bin/bash

for file in `find -name CMakeLists.txt`; do
  echo $file
  perl -p -i -e 's/([^\s]*)\.cpp/$1.cpp $1.h/g' $file
done
