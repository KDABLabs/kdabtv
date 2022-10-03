#! /bin/bash
dirs=`find -name CMakeLists.txt -print0 |xargs -0 dirname`

base=`pwd`
for dir in $dirs; do
  cd $dir
  echo "===============$dir======================="
  files=`find -name \*.h | cut -c '3-'`
  headers=`grep --only-matching '[^ ]*\.h' CMakeLists.txt`
  echo "$files" | grep --invert-match "$headers"
  cd $base
done
