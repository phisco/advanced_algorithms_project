#!/usr/bin/env bash
if [ $# != 6 ]
then
    echo "help: generate_graph.sh root_dir_graphs_files min_nodes step max_nodes step_edges
    max_edges"
    exit 1
fi
g++ -O2 -lboost_graph -lboost_timer generate_graph.cpp -o generate_graph.out
mkdir -p $1
for nodes in `seq $2 $3 $4 `
do
    max=`echo "$nodes * ($nodes - 1)" | bc -l`
    if [ $max -ne 0 ]
    then
        for e in `seq 0 $5 $(python -c "print(min($6,$max))")`
        do
            p=`echo "$e / $max" | bc -l | awk '{printf "%f", $0}'`
            echo $nodes $p $e
            ./generate_graph.out $nodes $p > tmp
            edges=`tail tmp | awk '{print $2}' | grep "e[0-9]\+" | grep -o "[0-9]\+" | tail -n 1`
            if [ -z $edges ]
            then
                edges=0
            else
                edges=`expr $edges + 1`
            fi
            mv tmp $1/$nodes\_$p\_$edges.xml
        done;
    fi
done
