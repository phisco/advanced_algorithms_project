#!/usr/bin/env bash
if [ $# !=  1 ]
      then
              echo "help: time_test.sh root_dir"
              exit 1
fi
g++ -O2 -lboost_graph -lboost_timer test_from_stdin.cpp -o test_from_stdin.out
for g in `ls $1 | sort -n`
do 
    echo "$g" "`du -h $1/$g | awk '{print $1}'`";
    ./test_from_stdin.out < $1/$g;
done

