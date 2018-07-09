if [ $# != 5 ]
then
    echo "help: generate_graph.sh root_dir_graphs_files min_nodes step max_nodes prob"
    exit 1
fi
mkdir -p $1
for nodes in `seq $2 $3 $4 `
do
        ../cmake-build-debug/generate_graph $nodes $p > tmp
done
