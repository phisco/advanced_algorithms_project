#!/usr/bin/env bash
if [ $# !=  1 ]
      then
              echo "help: test_tc.sh root_dir"
              exit 1
fi
mkdir -p ./tc_results
if [ -e "./tc_results/trans_closure_result.txt" ]
        then
            rm ./tc_results/trans_closure_result.txt;
fi

for g in `ls $1 | sort -n`
do

    echo "$g" >> ./tc_results/trans_closure_result.txt;
    #cat $1/$g | ./cmake-build-debug/transitive_closure > ./tc_results/tc\_$g\_results.txt;
    cat $1/$g | ./cmake-build-debug/transitive_closure | uniq >> ./tc_results/trans_closure_result.txt;
    echo "----------------------------------------------------------------------------" >> ./tc_results/trans_closure_result.txt;
done

python ./trans_closure_show_results.py