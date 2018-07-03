if [ $# != 4 ]
then
    echo "help: generate_graph.sh root_dir min step max"
    exit 1
fi
mkdir $1
for i in `seq $2 $3 $4 ` 
do
    echo $i
    ./cmake-build-debug/generate_graph $i 0.002 > $1/$i.xml
done
