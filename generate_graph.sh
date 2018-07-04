#!/usr/bin/env bash
if [ $# != 5 ]
then
    echo "help: generate_graph.sh root_dir_graphs_files min_nodes step max_nodes percentage_of_edges"
    exit 1
fi
mkdir -p $1
for i in `seq $2 $3 $4 `
do
    echo $i
    ./cmake-build-debug/generate_graph $i $5 > $1/$i\_$5.xml
done
